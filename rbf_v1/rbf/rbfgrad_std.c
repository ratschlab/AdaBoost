/* Gradient routine for rbf networks _without_ sample and label weightings
 * it supports only special form of rbf networks:
 *   h^{[q](i)}=exp(norm(x^{(i)}-\mu^{[q]})^2/\sigma^{[q]}^2) ;
 */ 

#include <math.h>
#include "mex.h"
#include <assert.h>
#include "matrix.h"

#ifndef MATLAB4
#define mexFuncConst const
#define Matrix mxArray
#else
#define mexFuncConst 
#define mxCreateDoubleMatrix mxCreateFull
#define mxREAL 0
#endif


void 
rbfgrad_std(double *X, double *Y, double *O, double *mu, double *sigma, 
	    double *w, double *H, double *Inp,
	    unsigned int a, unsigned int b, unsigned int m, 
	    unsigned int l, double *C_mu, double *C_sigma)
{
  double *dif_oy=(double *)calloc(b*l, sizeof(double)) ;
  double *H_h2_sigma=(double *)calloc(l, sizeof(double)) ;
  double *h_q__sigma_q=(double *)calloc(l, sizeof(double)) ;
  double *h_q__mu_q=(double *)calloc(l, sizeof(double)) ; 

  register unsigned int i, j, q, s ;
  for (j=0; j<b; j++)
    for (i=0; i<l; i++)
	 dif_oy[j+i*b]=(O[j+i*b]-Y[j+i*b])/l ;
         /* now we have dif_oy(j,i)= ...
            (f_j^{(i)}-{\hat y}_j^{(i)})/l */

  /* loop for the centers*/
  for (q=0; q<m; q++)
  {
    double C__sigma_q ;

    /* compute as much as we can before entering a new for-level */
    for (i=0; i<l; i++)
    {
      H_h2_sigma[i]= 2*H[i+q*l] / (sigma[q]*sigma[q]) ;
      h_q__sigma_q[i]= 2*Inp[i+q*l]*H[i+q*l]/sigma[q] ;
    } ;

    /* gradient for \mu(:,q) */
    /*************************/
  
    /* loop for the input dimensions */
    for (s=0; s<a; s++)
    {
      double C__mu_q_s ;
	
      /* compute as much as we can before entering a new for-level */
      for (i=0; i<l; i++)
	h_q__mu_q[i]= (X[s+i*a]-mu[s+q*a])*H_h2_sigma[i] ;
        /* now we have h_q__mu_q(i)= ...
             2*(x_s^{(i)}-\mu_s^{[q]})*h^{[q](i)}/h^2_sigma(sigma^{[q]}) ;*/

      /* sum them up ... loop for the output dimension */
      C__mu_q_s=0 ;
      for (j=0; j<b; j++)
      {
	/* sum them up ... loop for the patterns */
	double sum=0 ;
	for (i=0; i<l; i++)
	  sum = sum + dif_oy[j+i*b] * h_q__mu_q[i] ;
          /* now we have sum*w(j,q)= ...
	     \sum_{i=1}^l 1/l*(f_j^{(i)}-{\hat y}_j^{(i)}) * ...
                          \frac{\partial}{\partial \mu_s^{[q]}} f_j^{(i)} */

	C__mu_q_s= C__mu_q_s + sum*w[q+j*m] ; 
      } ;
    
      C_mu[s+q*a]=2*C__mu_q_s ;
      /* now we have C_mu(s,q)= 2 * \sum_{j=1}^b \sum_{i=1}^l ...
	 1/l*(f_j^{(i)}-{\hat y}_j^{(i)}) * ...
	 \frac{\partial}{\partial \mu_s^{[q]}} f_j^{(i)} */
    } ;
  
    /* gradient for \sigma(q) */
    /**************************/
    
    /* sum them up ... loop for the output dimension */
    C__sigma_q=0 ;
    for (j=0; j<b; j++)
    {
      /* sum them up ... loop for the patterns */
      double sum=0 ;
      for (i=0; i<l; i++)
	sum = sum + dif_oy[j+i*b] * h_q__sigma_q[i] ;
        /* now we have sum*w(j,q)= ...
           \sum_{i=1}^l 1/l*(f_j^{(i)}-{\hat y}_j^{(i)}) * ...
                        \frac{\partial}{\partial \sigma^{[q]}} f_j^{(i)} */
    
      C__sigma_q= C__sigma_q + sum*w[q+j*m] ; 
    } 
  
    C_sigma[q]=2*C__sigma_q ;
    /* now we have C_sigma(q)= 2 * \sum_{j=1}^b \sum_{i=1}^l ...
       1/l*(f_j^{(i)}-{\hat y}_j^{(i)}) * ...
       \frac{\partial}{\partial \sigma^{[q]}} f_j^{(i)} */
  } ;
  free(dif_oy) ;
  free(H_h2_sigma) ;
  free(h_q__sigma_q) ;
  free(h_q__mu_q) ;
} 


void
mexFunction(
    int nlhs,
    Matrix *plhs[],
    int nrhs,
    mexFuncConst Matrix *prhs[])
{
  double *X, *Y, *O, *mu, *sigma, *w, *H, *Inp ;
  unsigned int a, b, m, l; 
  double *C_mu=NULL, *C_sigma=NULL ;

  if ((nrhs!=8) || (nlhs!=2))
  {
    mexErrMsgTxt("[C_mu, C_sigma]=cen_wid_grad_std(X, Y, O, mu, sigma, w, H, Inp)") ;
    return ;
  } ;

  X=mxGetPr(prhs[0]) ; assert(X!=0) ; 
  /*  printf("(%i,%i)\n", mxGetM(prhs[0]), mxGetN(prhs[0])) ;*/
  Y=mxGetPr(prhs[1]) ; assert(Y!=0) ;
  /*  printf("(%i,%i)\n", mxGetM(prhs[1]), mxGetN(prhs[1])) ;*/
  O=mxGetPr(prhs[2]) ; assert(O!=0) ;
  /*  printf("(%i,%i)\n", mxGetM(prhs[2]), mxGetN(prhs[2])) ;*/
  mu=mxGetPr(prhs[3]) ; assert(mu!=0) ;
  /*printf("(%i,%i)\n", mxGetM(prhs[3]), mxGetN(prhs[3])) ;*/
  sigma=mxGetPr(prhs[4]) ; assert(sigma!=0) ;
  /*printf("(%i,%i)\n", mxGetM(prhs[4]), mxGetN(prhs[4])) ;*/
  w=mxGetPr(prhs[5]) ; assert(w!=0) ;
  /*printf("(%i,%i)\n", mxGetM(prhs[5]), mxGetN(prhs[5])) ;*/
  H=mxGetPr(prhs[6]) ; assert(H!=0) ;
  /*printf("(%i,%i)\n", mxGetM(prhs[6]), mxGetN(prhs[6])) ;*/
  Inp=mxGetPr(prhs[7]) ; assert(Inp!=0) ;
  /*printf("(%i,%i)\n", mxGetM(prhs[7]), mxGetN(prhs[7])) ;*/

  a=mxGetM(prhs[0]) ;
  b=mxGetM(prhs[1]) ;
  l=mxGetN(prhs[0]) ;
  m=mxGetM(prhs[5]) ;
  /*printf("%i, %i, %i, %i", a,b,l,m) ;*/
  if ((mxGetN(prhs[1])!=l))
  {
    mexErrMsgTxt("Dimension error (arg 2).");
    return ;
  } ;
  if ((mxGetN(prhs[2])!=l) | (mxGetM(prhs[2])!=b))
  {
    mexErrMsgTxt("Dimension error (arg 3).");
    return ;
  } ;
  if ((mxGetM(prhs[3])!=a) | (mxGetN(prhs[3])!=m))
  {
    mexErrMsgTxt("Dimension error (arg 4).");
    return ;
  } ;
  if ((mxGetM(prhs[4])!=1) | (mxGetN(prhs[4])!=m))
  {
    mexErrMsgTxt("Dimension error (arg 5).");
    return ;
  } ;
  if (mxGetN(prhs[5])!=b)
  {
    mexErrMsgTxt("Dimension error (arg 6).");
    return ;
  } ;
  if ((mxGetM(prhs[6])!=l) | (mxGetN(prhs[6])!=m))
  {
    mexErrMsgTxt("Dimension error (arg 7).");
    return ;
  } ;
  if ((mxGetM(prhs[7])!=l) | (mxGetN(prhs[4])!=m))
  {
    mexErrMsgTxt("Dimension error (arg 8).");
    return ;
  } ;

  plhs[0]=(mxArray*)mxCreateDoubleMatrix(a, m, mxREAL) ; 
  C_mu = mxGetPr(plhs[0]);
  plhs[1]=(mxArray*)mxCreateDoubleMatrix(1, m, mxREAL) ; 
  C_sigma = mxGetPr(plhs[1]);
    
  rbfgrad_std(X, Y, O, mu, sigma, w, H, Inp,
	      a, b, m, l, C_mu, C_sigma) ;
} 



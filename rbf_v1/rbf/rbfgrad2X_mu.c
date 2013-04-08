/* Gradient routine the patterns of a rbf network
 * it supports 
 *   h^{[q](i)}=exp(norm(x_i}-\mu_q)^2/\sigma_q^2)) ;
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


#define P(i_,s_,q_) Pijk[s_+i_*a+q_*a*l]

void 
rbfgrad2X_mu(double *X, double *mu, double *sigma, 
	  double *H, double *distr, unsigned int a, 
	  unsigned int m, unsigned int l, 
	  double *C_X)
{
  register unsigned int i, q, k, s ;
  double* Pijk=calloc(a*l*m,sizeof(double)) ;

  /* loop for the centers*/
  for (q=0; q<m; q++)
    {
      register double _2_sq=2/(sigma[q]*sigma[q]) ;

      /* loop for the patterns */
      for (i=0; i<l; i++)
	{
	  register double _2gq_sq=_2_sq*H[i+q*l] ;

	  /* loop for the input dimension */
	  for (s=0; s<a; s++)
	    {
	      register double muqs=mu[s+q*a] ;
	      register double diff=X[s+i*a]-muqs ;

	      P(i,s,q)=  _2gq_sq*(_2_sq*diff*diff-1) ;
	      /* now we have (d^2g_q(x_i)/dx^2)^2=...
		 sqr(2*w_q*g_q(x)/sigma_q*(-1+2/sigma_q^2*(x-mu_q).^2)) */
	    } ;
	} ;
    } ;

  /* loop for the centers*/
  for (q=0; q<m; q++)
    /* loop for the centers*/
    for (k=0; k<=q; k++)
      {
	register double sum=0.0 ;
	/* loop for the patterns */
	for (i=0; i<l; i++)
	  /* loop for the input dimension */
	  for (s=0; s<a; s++)
	      sum+=distr[i]*P(i,s,q)*P(i,s,k) ;
	C_X[k+q*m]=sum ;
	C_X[q+k*m]=sum ;
      } ;
  free(Pijk) ;
} 


void
mexFunction(
    int nlhs,
    Matrix *plhs[],
    int nrhs,
    mexFuncConst Matrix *prhs[])
{
  double *X, *mu, *sigma, *H, *distr ;
  unsigned int a, b, m, l; 
  double *C_X=NULL ;

  if ((nrhs!=5) || (nlhs!=1))
  {
    mexErrMsgTxt("C_X=rbfgrad2X_mu(X, mu, sigma, H)") ;
    return ;
  } ;

  X=mxGetPr(prhs[0]) ; assert(X!=0) ; 
  mu=mxGetPr(prhs[1]) ; assert(mu!=0) ;
  sigma=mxGetPr(prhs[2]) ; assert(sigma!=0) ;
  H=mxGetPr(prhs[3]) ; assert(H!=0) ;
  distr=mxGetPr(prhs[4]) ; assert(distr!=0) ;
 
  a=mxGetM(prhs[0]) ;
  l=mxGetN(prhs[0]) ;
  m=mxGetN(prhs[1]) ;

  if ((mxGetM(prhs[1])!=a) | (mxGetN(prhs[1])!=m))
  {
    fprintf(stderr, "a=%i!=%i; b=%i!=%i \n", a, mxGetM(prhs[1]), m, mxGetN(prhs[1])) ;
    mexErrMsgTxt("Dimension error (arg 2).");
    return ;
  } ;
  if ((mxGetM(prhs[2])!=1) | (mxGetN(prhs[2])!=m))
  {
    mexErrMsgTxt("Dimension error (arg 3).");
    return ;
  } ;
  if ((mxGetM(prhs[3])!=l) | (mxGetN(prhs[3])!=m))
  {
    mexErrMsgTxt("Dimension error (arg 4).");
    return ;
  } ;
  if ((mxGetM(prhs[4])!=1) | (mxGetN(prhs[4])!=l))
  {
    mexErrMsgTxt("Dimension error (arg 5).");
    return ;
  } ;

  plhs[0]=(mxArray*)mxCreateDoubleMatrix(m, m, mxREAL) ; 
  C_X = mxGetPr(plhs[0]);
    
  rbfgrad2X_mu(X, mu, sigma, H, distr, a, m, l, C_X) ;
} 







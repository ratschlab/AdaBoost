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
rbfgrad2X_muw(double *X, double *mu, double *sigma, 
	  double *H, double *distr, double *w, unsigned int a, 
	  unsigned int m, unsigned int l, 
	  double *C_dX)
{
  register unsigned int i, q, k, s ;
  *C_dX=0.0 ;

  /* loop for the patterns */
  for (i=0; i<l; i++)
    {
      register double C_dX_i=0 ;
      
      /* loop for the input dimension */
      for (s=0; s<a; s++)
	{
	  register double C_dX_is=0 ;

	  /* loop for the centers*/
	  for (q=0; q<m; q++)
	    {
	      register double _2_sq=2/(sigma[q]*sigma[q]) ;
	      register double _2gq_sq=_2_sq*H[i+q*l] ;
	      register double muqs=mu[s+q*a] ;
	      register double diff=X[s+i*a]-muqs ;

	      C_dX_is += w[q]*_2gq_sq*(_2_sq*diff*diff-1) ;

	      /* now we have (d^2g_q(x_i)/dx^2)^2=...
		 sqr(2*w_q*g_q(x)/sigma_q*(-1+2/sigma_q^2*(x-mu_q).^2)) */
	    } ;
	  C_dX_i += C_dX_is * C_dX_is ;
	} ;
      *C_dX += C_dX_i * distr[i] ;
    } ;
} 


void
mexFunction(
    int nlhs,
    Matrix *plhs[],
    int nrhs,
    mexFuncConst Matrix *prhs[])
{
  double *X, *mu, *sigma, *H, *distr, *w ;
  unsigned int a, b, m, l; 
  double *C_X=NULL ;

  if ((nrhs!=6) || (nlhs!=1))
  {
    mexErrMsgTxt("C_X=rbfgrad2X_mu(X, mu, sigma, H, distr, w)") ;
    return ;
  } ;

  X=mxGetPr(prhs[0]) ; assert(X!=0) ; 
  mu=mxGetPr(prhs[1]) ; assert(mu!=0) ;
  sigma=mxGetPr(prhs[2]) ; assert(sigma!=0) ;
  H=mxGetPr(prhs[3]) ; assert(H!=0) ;
  distr=mxGetPr(prhs[4]) ; assert(distr!=0) ;
  w=mxGetPr(prhs[5]) ; assert(w!=0) ;
 
  a=mxGetM(prhs[0]) ;
  l=mxGetN(prhs[0]) ;
  m=mxGetN(prhs[1]) ;

  if ((mxGetM(prhs[1])!=a) | (mxGetN(prhs[1])!=m))
  {
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
  if ((mxGetM(prhs[5])!=m) | (mxGetN(prhs[5])!=1))
  {
    mexErrMsgTxt("Dimension error (arg 6).");
    return ;
  } ;

  plhs[0]=(mxArray*)mxCreateDoubleMatrix(1, 1, mxREAL) ; 
  C_X = mxGetPr(plhs[0]);
    
  rbfgrad2X_muw(X, mu, sigma, H, distr, w, a, m, l, C_X) ;
} 







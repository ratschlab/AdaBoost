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


void 
rbfgrad2X(double *X, double *mu, double *sigma, 
	  double *w, double *H, unsigned int a, 
	  unsigned int m, unsigned int l, 
	  double *C_X)
{
  register unsigned int i, j, q, s ;

  /* loop for the patterns */
  for (i=0; i<l; i++)
    {
      /* clear space for the derivatives */
      for (s=0; s<a; s++)
	  C_X[s+i*a]=0.0 ;

      /* loop for the centers*/
      for (q=0; q<m; q++)
	{
	  register double _2_sq=2/(sigma[q]*sigma[q]) ;
	  register double _2gq_sq=_2_sq*H[i+q*l] ;

	  for (s=0; s<a; s++)
	    {
	      register double muqs=mu[s+q*a] ;
	      register double diff=X[s+i*a]-muqs ;
	      C_X[s+i*a]+= w[q]*_2gq_sq*(-1+_2_sq*diff*diff) ;
	      /* now we have w_q*d^2g_q(x_i)/dx^2=...
		 2*w_q*g_q(x)/sigma_q*(-1+2/sigma_q^2*(x-mu_q).^2) */
	    } ;
	} ;
    } ;
} 


void
mexFunction(
    int nlhs,
    Matrix *plhs[],
    int nrhs,
    mexFuncConst Matrix *prhs[])
{
  double *X, *mu, *sigma, *w, *H ;
  unsigned int a, b, m, l; 
  double *C_X=NULL ;

  if ((nrhs!=5) || (nlhs!=1))
  {
    mexErrMsgTxt("[C_X]=rbfgrad2X(X, mu, sigma, w, H)") ;
    return ;
  } ;

  X=mxGetPr(prhs[0]) ; assert(X!=0) ; 
  mu=mxGetPr(prhs[1]) ; assert(mu!=0) ;
  sigma=mxGetPr(prhs[2]) ; assert(sigma!=0) ;
  w=mxGetPr(prhs[3]) ; assert(w!=0) ;
  H=mxGetPr(prhs[4]) ; assert(H!=0) ;
 
  a=mxGetM(prhs[0]) ;
  b=mxGetN(prhs[3]) ; 
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
  if ((mxGetM(prhs[3])!=m) | (mxGetN(prhs[3])!=1))
  {
    mexErrMsgTxt("Dimension error (arg 4).");
    return ;
  } ;
  if ((mxGetM(prhs[4])!=l) | (mxGetN(prhs[4])!=m))
  {
    mexErrMsgTxt("Dimension error (arg 5).");
    return ;
  } ;

  plhs[0]=(mxArray*)mxCreateDoubleMatrix(a, l, mxREAL) ; 
  C_X = mxGetPr(plhs[0]);
    
  rbfgrad2X(X, mu, sigma, w, H, a, m, l, C_X) ;
} 

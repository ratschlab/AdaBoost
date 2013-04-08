/*
 * Author: Sebastian Mika, GMD First
 * $Id: syevx.c,v 1.1 1999/09/08 05:30:01 raetsch_cvs Exp $
 */

#include "mex.h"
#include "symeigx.h"

#define A prhs[0]
#define L prhs[1]
#define V plhs[0]
#define D plhs[1]

void mexFunction(
		 int     nlhs,	  /* number of expected outputs */
		 mxArray *plhs[], /* matrix pointer array returning outputs */
		 int	 nrhs,	  /* number of inputs */
		 const mxArray  *prhs[]  /* matrix pointer array for inputs */
		 ) {
  double *a=NULL, *d=NULL, *v=NULL, *ac=NULL, 
         *dc=NULL, *vc=NULL;
  int    na, ma;
  int    l;
  int    flag;

  if ((nrhs != 2) || (nlhs != 2)) {
    mexErrMsgTxt("Usage: [v, d] = syevx(a,l)");
    return;
  }

  /* sanity checks for right hand side and variable initialization */
  if (!mxIsNumeric(A) 
      || mxIsComplex(A) 
      || !mxIsDouble(A) 
      || mxIsSparse(A) ) {
    mexErrMsgTxt("sygvx: Matrix A must be real and square.");
    return;
  }

  ma = mxGetM(A);
  na = mxGetN(A);

  if ((ma == 0) || (na == 0) || (ma !=na)) {
    mexErrMsgTxt("sygvx: Matrix A must be square and not empty.");
    return;
  }

  a = mxGetPr(A);
  l = (int) mxGetScalar(L);
  
  if ((l > na) || (l < 1)){
    mexErrMsgTxt("sygvx: l bigger than dimension or smaller than 1.");
    return;
  }
  /* 
   * We add some more memory as some blas/lapack routines like to write
   * behind actual array...
   */
  ac = (double *) malloc(sizeof(double) * (na * na + 10));
  
  dc = (double *) malloc(sizeof(double) * (l + 10));
  vc = (double *) malloc(sizeof(double) * (l * na + 10));

  
  memcpy(ac, a, na*na*sizeof(double));

  symeigx(ac, na, dc, vc, l, &flag);

  free(ac);

  if (flag > 0)
    {
      D  = (mxArray *) mxCreateDoubleMatrix(l, 1,  mxREAL);
      V  = (mxArray *) mxCreateDoubleMatrix(na, l, mxREAL);
      d = mxGetPr(D);
      v = mxGetPr(V);
      
      memcpy(d, dc, l*sizeof(double));
      memcpy(v, vc, l*na*sizeof(double));      
    }
  else 
    {
      D  = (mxArray *) mxCreateDoubleMatrix(0, 0,  mxREAL);
      V  = (mxArray *) mxCreateDoubleMatrix(0, 0, mxREAL);
    }
  
  free(dc);
  free(vc);
}




/*
 * File:        design_rbf_c.c
 * Purpose:     matlab interface and fast rbf dot product
 *
 * Author:      Gunnar R"atsch, Alex J. Smola
 * Created:     10/30/97
 * Updated:     11/01/97
 *
 * z = design_rbf(X, C, R)
 * fast ordering is assumed (each column is a vector)
 * (this is FORTRAN, hence we have _row_ ordering as we use C)
 * 
 * Copyright (c) 1997  GMD Berlin - All rights reserved
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
 * The copyright notice above does not evidence any
 * actual or intended publication of this work.
 *
 * modified code from Mathworks and Rob Vanderbei
 *
 * compile with
 Matlab 4 LINUX
  cc -O3 -W -m486 -c clustknb_new.c -o clustknb_new.lx.o
  cmex4 -DMATLAB4 clustknb_new_c.c clustknb_new.lx.o ../utils/sqdist.lx.o -o clustknb_new_c4
 Matlab 5 LINUX
  cc -O3 -W -m486 -c clustknb_new.c -o clustknb_new.lx.o
  cmex5 clustknb_new_c.c clustknb_new.lx.o ../utils/sqdist.lx.o -output clustknb_new_c5
 Matlab 4 SUN
  cc -c -fast -DMULTI_CPU -xreduction -xO5 -xautopar -xtarget=ultra1/2200 -xloopinfo -lpthread -lthread clustknb_new.c -o clustknb_new.sun.o
  cmex4 -L/home/solaris/opt/SUNWspro/SC4.0/lib -lmtsk -DMATLAB4 clustknb_new_c.c clustknb_new.sun.o ../utils/sqdist.sun.o -lpthread -lthread -o clustknb_new_c4
 Matlab 5 SUN
  cc -c -fast -DMULTI_CPU -xO5 -xautopar -xtarget=ultra1/2200 -xloopinfo -lpthread -lthread clustknb_new.c -o clustknb_new.sun.o
  cmex5 -L/home/solaris/opt/SUNWspro/SC4.0/lib -lmtsk clustknb_new_c.c clustknb_new.sun.o ../utils/sqdist.sun.o -output clustknb_new_c5 
echo Matlab 4 
  cmex4 -O -DMATLAB4 clustknb_new_c.c clustknb_new.c ../utils/sqdist_.c -o clustknb_new_c4
echo Matlab 5 
  cmex5 -O clustknb_new_c.c clustknb_new.c ../utils/sqdist_.c -output clustknb_new_c5 
 *
 */

#include "mex.h"
#include <math.h>
#include <stdio.h>
#include "clustknb_new.h"

#ifndef MATLAB4
#define mexFuncConst const
#else
#define mxArray Matrix 
#define mexFuncConst 
#define mxCreateDoubleMatrix mxCreateFull
#define mxREAL 0
#endif

void mexFunction(
    int		nlhs,		/* number of expected outputs */
    mxArray	*plhs[],	/* matrix pointer array returning outputs */
    int		nrhs,		/* number of inputs */
    mexFuncConst mxArray *prhs[]	/* matrix pointer array for inputs */
)
{
    double *X=NULL, *C=NULL, *R=NULL ;
    double *mus_start=NULL ;
    unsigned int disp=1 ;
    unsigned int use_mus = 0, k = 0 ;
    unsigned int XSize=0, XDim=0 ;

    if ((nrhs > 3) || (nrhs < 2)) {
      mexErrMsgTxt("Usage: [C, R] = clustknb_new(X, k [, disp[, mus_start]])");
      return;
    }
    /* sanity checks for right hand side and variable initialization */
    switch (nrhs) {
    case 4:
      if (mxGetM(prhs[3]) != 0 || mxGetN(prhs[3]) != 0) {
	if (!mxIsNumeric(prhs[3]) 
	    || mxIsComplex(prhs[3]) 
	    || !mxIsDouble(prhs[3]) 
	    || mxIsSparse(prhs[3]) ) {
	  mexErrMsgTxt("Third argument (mus_start) must be "
		       "a matrix.");
	  return;
	}
	k = mxGetN(prhs[3]);
	XDim = mxGetM(prhs[3]);
	mus_start = mxGetPr(prhs[3]);
        use_mus=1;
      }
    case 3:
      if (mxGetM(prhs[2]) != 0 || mxGetN(prhs[2]) != 0) {
	if (!mxIsNumeric(prhs[2]) 
	    || mxIsComplex(prhs[2]) 
	    || !mxIsDouble(prhs[2]) 
	    || !(mxGetM(prhs[2])==1 && mxGetN(prhs[2])==1)
	    || floor(*mxGetPr(prhs[2]))!= ceil(*mxGetPr(prhs[2]))) {
	  mexErrMsgTxt("Third argument (disp) must be "
		       "a integer scalar.");
	  return;
	}
	disp = (unsigned int) *mxGetPr(prhs[2]);
      }
    case 2:
      if (mxGetM(prhs[1]) != 0 || mxGetN(prhs[1]) != 0) {
	if (!mxIsNumeric(prhs[1]) 
	    || mxIsComplex(prhs[1]) 
	    || !mxIsDouble(prhs[1]) 
	    || !(mxGetM(prhs[1])==1 && mxGetN(prhs[1])==1)
	    || floor(*mxGetPr(prhs[1]))!= ceil(*mxGetPr(prhs[1]))) {
	  mexErrMsgTxt("Second argument (k) must be "
		       "a integer scalar.");
	  return;
	}
        if (k!=0 && k!= *mxGetPr(prhs[1]))
	{
	  mexErrMsgTxt("Third argument (mus_start) does not "
		       "match to the second (k).");
	  return;
	} ;
	k = (unsigned int) *mxGetPr(prhs[1]);
      }
    case 1:
      if (mxGetM(prhs[0]) != 0 || mxGetN(prhs[0]) != 0) {
	if (!mxIsNumeric(prhs[0]) 
	    || mxIsComplex(prhs[0]) 
	    || !mxIsDouble(prhs[0]) 
	    || mxIsSparse(prhs[0]) ) {
	  mexErrMsgTxt("First argument (X) must be "
		       "a matrix.");
	  return;
	}
	if (XDim != 0 && XDim != mxGetM(prhs[0])) {
	  mexErrMsgTxt("Dimension error (arg 1 and later).");
	  return;
	}
	XDim = mxGetM(prhs[0]);
	XSize = mxGetN(prhs[0]);

	X = mxGetPr(prhs[0]);
      }
      break;
    }

    if (nlhs < 2 || nlhs > 2) {
      mexErrMsgTxt("Usage: [C, R] = clustknb_new(X, k [, mus_start])");
      return;
    }

    plhs[0]=(mxArray*)mxCreateDoubleMatrix(XDim, k, mxREAL) ; 
    C = mxGetPr(plhs[0]);
    plhs[1]=(mxArray*)mxCreateDoubleMatrix(1, k, mxREAL) ; 
    R = mxGetPr(plhs[1]);
    
    clustknb_new(X, k, use_mus, mus_start, C, R, XSize, XDim, disp);
}





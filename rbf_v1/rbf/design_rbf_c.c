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
echo Matlab 4
  cmex4 -O -DMATLAB4 design_rbf_c.c design_rbf.c -o design_rbf_c4
echo Matlab 5
  cmex5 -O design_rbf_c.c design_rbf.c -output design_rbf_c5
 *
 */

#include "mex.h"
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include "design_rbf.h"

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
    double *X=NULL, *C=NULL, *H=NULL, *Inp=NULL;
    double *sigma=NULL ;
    unsigned int n1=0, n2=0, m=0;

    if ((nrhs > 3) || (nrhs < 2)) {
      mexErrMsgTxt("Usage1: z = design_rbf(X, C, R)");
      return;
    }
    /* sanity checks for right hand side and variable initialization */
    switch (nrhs) {
    case 3:
      if (mxGetM(prhs[2]) != 0 || mxGetN(prhs[2]) != 0) {
	if (!mxIsNumeric(prhs[2]) 
	    || mxIsComplex(prhs[2]) 
	    || !mxIsDouble(prhs[2]) 
	    || mxIsSparse(prhs[2]) ) {
	  mexErrMsgTxt("Third argument (R) must be "
		       "a vector.");
	  return;
	}
	n2 = mxGetN(prhs[2]);
	if (n2==1) n2 = mxGetM(prhs[2]); 
	sigma = mxGetPr(prhs[2]);
      }
    case 2:
      if (mxGetM(prhs[1]) != 0 || mxGetN(prhs[1]) != 0) {
	if (!mxIsNumeric(prhs[1]) 
	    || mxIsComplex(prhs[1]) 
	    || !mxIsDouble(prhs[1]) 
	    || mxIsSparse(prhs[1]) ) {
	  mexErrMsgTxt("Second argument (C) must be "
		       "a matrix.");
	  return;
	}
	if (m != 0 && m != mxGetM(prhs[1])) {
	  mexErrMsgTxt("Dimension error (arg 2 and later).");
	  return;
	}
	m = mxGetM(prhs[1]);
	if (n2!=mxGetN(prhs[1]))
	{
	  mexErrMsgTxt("Dimension error in R (arg 2 and later).");
	  return;
	}    
	n2 = mxGetN(prhs[1]);

	C = mxGetPr(prhs[1]);
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
	if (m != 0 && m != mxGetM(prhs[0])) {
	  mexErrMsgTxt("Dimension error (arg 1 and later).");
	  return;
	}
	m = mxGetM(prhs[0]);
	n1 = mxGetN(prhs[0]);

	X = mxGetPr(prhs[0]);
      }
      break;
    }

    if (nlhs < 1) {
      mexErrMsgTxt("Usage2: z = design_rbf(X, C, R)");
      return;
    }

    if (nlhs == 2) {
      plhs[1]=(mxArray*)mxCreateDoubleMatrix(n1, n2, mxREAL) ; 
      Inp = mxGetPr(plhs[1]);
    } 

    plhs[0]=(mxArray*)mxCreateDoubleMatrix(n1, n2, mxREAL) ; 
    H = mxGetPr(plhs[0]);
    
    design_rbf(X, C, H, Inp, sigma, n1, n2, m);
}





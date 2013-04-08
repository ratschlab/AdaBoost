/*
 * File:        ht_h_lambda_c.c
 * Purpose:     matlab interface 
 *
 * Author:      Alex J. Smola, Gunnar R"atsch
 * Created:     10/16/97
 * Updated:     10/27/97
 *
 * z = ht_h_lambda(x, y)
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
  cc -O4 -c ht_h_lambda_.c -o ht_h_lambda.lx.o
  cmex4 -DMATLAB4 ht_h_lambda_c.c ht_h_lambda.lx.o -o ht_h_lambda_c4
 Matlab 5 LINUX
  cc -O4 -c ht_h_lambda_.c -o ht_h_lambda.lx.o
  cmex5 ht_h_lambda_c.c ht_h_lambda.lx.o -output ht_h_lambda_c5
 Matlab 4 SUN
  cc -c -fast -DMULTI_CPU -xO5 -xautopar -xtarget=ultra1/2200 -xloopinfo -lpthread -lthread ht_h_lambda_.c -o ht_h_lambda.sun.o
  cmex4 -L/home/solaris/opt/SUNWspro/SC4.0/lib -lmtsk -lpthread -lthread -DMATLAB4 ht_h_lambda_c.c ht_h_lambda.sun.o -o ht_h_lambda_c4
 Matlab 5 SUN
  cc -c -fast -DMULTI_CPU -xO5 -xautopar -xtarget=ultra1/2200 -xloopinfo -lpthread -lthread ht_h_lambda_.c -o ht_h_lambda.sun.o
  cmex5 -L/home/solaris/opt/SUNWspro/SC4.0/lib -lmtsk ht_h_lambda_c.c ht_h_lambda.sun.o -output ht_h_lambda_c5 
 Matlab 4 SGI
  cc -c -O2 ht_h_lambda_.c -o ht_h_lambda.sgi.o
  cmex4 -DMATLAB4 ht_h_lambda_c.c ht_h_lambda.sgi.o -o ht_h_lambda_c4
 Matlab 5 SUN
  cc -c -O2 ht_h_lambda_.c -o ht_h_lambda.sgi.o
  cmex5 ht_h_lambda_c.c ht_h_lambda.sgi.o -output ht_h_lambda_c5 
 *
 */

#include "mex.h"
#include <math.h>
#include <stdio.h>
#include "ht_h_lambda.h"

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
    double *x=NULL, *z=NULL;
    double lambda = 1;
    unsigned int n=0, m=0;
    mxArray *zM ;

    if ((nrhs > 2) || (nrhs < 2)) {
      mexErrMsgTxt("Usage: z = ht_h_lambda(x, lambda)");
      return;
    }
    /* sanity checks for right hand side and variable initialization */
    switch (nrhs) {
    case 2:
      if (mxGetM(prhs[1]) != 0 || mxGetN(prhs[1]) != 0) {
	if (!mxIsNumeric(prhs[1]) 
	    || mxIsComplex(prhs[1]) 
	    || !mxIsDouble(prhs[1]) 
	    || mxIsSparse(prhs[1]) 
	    || !(mxGetM(prhs[1])==1 && mxGetN(prhs[1])==1)) {
	  mexErrMsgTxt("Second argument (lambda) must be "
		       "a scalar.");
	  return;
	}
	lambda = *mxGetPr(prhs[1]);
      }
    case 1:
      if (mxGetM(prhs[0]) != 0 || mxGetN(prhs[0]) != 0) {
	if (!mxIsNumeric(prhs[0]) 
	    || mxIsComplex(prhs[0]) 
	    || !mxIsDouble(prhs[0]) 
	    || mxIsSparse(prhs[0]) ) {
	  mexErrMsgTxt("First argument (x) must be "
		       "a matrix.");
	  return;
	}
	m = mxGetM(prhs[0]);
	n = mxGetN(prhs[0]);

	x = mxGetPr(prhs[0]);
      }
      break;
    }

    if (nlhs != 1) {
      mexErrMsgTxt("Usage: z = ht_h_lambda(x, lambda)");
      return;
    }

    plhs[0]=(mxArray*)mxCreateDoubleMatrix(n, n, mxREAL) ; 
    z = mxGetPr(plhs[0]);
    
    ht_h_lambda(x, lambda, z, n, m);
}




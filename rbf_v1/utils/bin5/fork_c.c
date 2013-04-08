/*
 * File:        fork_c.c
 * Purpose:     ...
 *
 * Author:      Gunnar R"atsch, Alex J. Smola
 * Created:     10/30/97
 * Updated:     15/11/97
 *
 * z = fork()
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
  cmex4 -O -DMATLAB4 fork_c.c -o fork_c4
echo Matlab 5
  cmex5 -O fork_c.c  -output fork_c5
 *
 */

#include "mex.h"
#include <math.h>
#include <stdio.h>

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
    double *res=NULL ;

    if ((nlhs < 1) || (nrhs!=0)) {
      mexErrMsgTxt("Usage: z = fork()");
      return;
    }

    plhs[0]=(mxArray*)mxCreateDoubleMatrix(1, 1, mxREAL) ; 
    res = mxGetPr(plhs[0]);
    
    *res=fork() ;
}

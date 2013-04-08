/*
 * File:        matr_mult_At_b.c
 * Purpose:     performs a matrix multiplication
 *
 * Author:      Gunnar Raetsch
 * Created:     1/2/98
 * Updated:     
 *
 * 
 * Copyright (c) 1997  GMD Berlin - All rights reserved
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
 * The copyright notice above does not evidence any
 * actual or intended publication of this work.
 *
 * $Revision: 1.2 $  $Date: 2003/06/26 20:48:57 $
 */

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "mex.h"
#include <assert.h>
#include "matrix.h"
/*#include "matr_mult_At_b.h"*/

#include "../../../ATLAS/include/atlas_enum.h"
#include "../../../ATLAS/include/atlas_level3.h"

#ifndef MATLAB4
#define mexFuncConst const
#define Matrix mxArray
#else
#define mexFuncConst 
#define mxCreateDoubleMatrix mxCreateFull
#define mxREAL 0
#endif


#ifndef MATR_MULT_AT_B_NOMEX
void
mexFunction(
    int nlhs,
    Matrix *plhs[],
    int nrhs,
    mexFuncConst Matrix *prhs[])
{
  double *a, *b, *y ;
  unsigned int m, n, k; 

  if ((nrhs!=2) || (nlhs!=1))
  {
    mexErrMsgTxt("y=matr_mult_at_b(A, b)") ;
    return ;
  } ;

  assert(mxGetClassID(prhs[0]==mxDOUBLE_CLASS)) ;
  assert(mxGetClassID(prhs[1]==mxDOUBLE_CLASS)) ;
  a=(double*)mxGetData(prhs[0]) ; assert(a!=0) ; 
  b=(double*)mxGetData(prhs[1]) ; assert(b!=0) ;

  n=mxGetN(prhs[0]) ;
  m=mxGetM(prhs[0]) ;
  k=mxGetN(prhs[1]) ;

  if ((mxGetM(prhs[1])!=m))
  {
    mexErrMsgTxt("Dimension error (arg 2).");
    return ;
  } ;

  plhs[0]=mxCreateNumericMatrix(n, k, mxDOUBLE_CLASS, 0) ; 
  y = (double*)mxGetData(plhs[0]);
    
  /*matr_mult_At_b(a, m, n, k, b, y) ;*/

  ATL_dgemm(AtlasTrans, AtlasNoTrans,
	    n, k, m, 1.0,
	    a, m, b, m,
	    0, y, n);

} 

#endif

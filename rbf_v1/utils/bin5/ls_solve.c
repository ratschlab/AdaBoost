/*
 * File:        ls_solve.c
 * Purpose:     
 *
 * Author:      Gunnar Raetsch
 * Created:     01/02/98
 *
 * 
 * Copyright (c) 1997  GMD Berlin - All rights reserved
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
 * The copyright notice above does not evidence any
 * actual or intended publication of this work.
 *
 * $Revision: 1.1 $  $Date: 1999/09/08 05:30:25 $
 */

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "mex.h"
#include <assert.h>
#include "matrix.h"

#include "ls_solve.h"
#include "linsys_solve.h"
#include "matr_mult_At_b.h"
#include "ht_h_lambda.h"

#ifndef MATLAB4
#define mexFuncConst const
#define Matrix mxArray
#else
#define mexFuncConst 
#define mxCreateDoubleMatrix mxCreateFull
#define mxREAL 0
#endif

/*****************************************************************
  the least squares solver 
 *****************************************************************/

void ls_solve(double a[], int m, int n, int k, double b[], double lambda, 
	      double x[], double f[])
{
  double *z=calloc(n*n, sizeof(double)) ;
  double *y=calloc(n*k, sizeof(double)) ;
  double suc, g ;
  unsigned int i ;

  ht_h_lambda(a, lambda*m, z, n, m) ;
  matr_mult_At_b(a, m, n, k, b, y) ;

  linsys_solve(z, n, k, y, x, 0, &suc) ;
  g=lambda*m + 1e-20 ;
  *f=0 ;
  while (suc>0)
  {
    for (i=0; i<n; i++)
      z[i*(n+1)]+=+g ;
    *f+=g ;
    linsys_solve(z, n, k, y, x, 0, &suc) ;
    g*=2 ;
  } ;
  if (*f!=0) *f+=*f/((double)m)+lambda ;

  free(y) ;
  free(z) ;
}


#ifndef LS_SOLVE_NOMEX
void
mexFunction(
    int nlhs,
    Matrix *plhs[],
    int nrhs,
    mexFuncConst Matrix *prhs[])
{
  double *a, *b, *x, lambda, *f ;
  unsigned int m, n, k; 

  if ((nrhs!=3) || (nlhs!=2))
  {
    mexErrMsgTxt("[x,f]=ls_solve(A, b, lambda)") ;
    return ;
  } ;

  a=mxGetPr(prhs[0]) ; assert(a!=0) ; 
  b=mxGetPr(prhs[1]) ; assert(b!=0) ;
  lambda=*mxGetPr(prhs[2]) ; 

  n=mxGetN(prhs[0]) ;
  m=mxGetM(prhs[0]) ;
  k=mxGetN(prhs[1]) ;

  if ((mxGetM(prhs[1])!=m))
  {
    mexErrMsgTxt("Dimension error (arg 2).");
    return ;
  } ;
  if ((mxGetM(prhs[2])!=1) | (mxGetN(prhs[2])!=1))
  {
    mexErrMsgTxt("Dimension error (arg 3).");
    return ;
  } ;

  plhs[0]=(mxArray*)mxCreateDoubleMatrix(n, k, mxREAL) ; 
  x = mxGetPr(plhs[0]);
  plhs[1]=(mxArray*)mxCreateDoubleMatrix(1, 1, mxREAL) ; 
  f = mxGetPr(plhs[1]);
    
  ls_solve(a, m, n, k, b, lambda, x, f) ;
} 

#endif

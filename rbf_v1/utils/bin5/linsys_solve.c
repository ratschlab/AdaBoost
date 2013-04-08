/*
 * File:        linsys_solve.c
 * Purpose:     solves linear programming problem
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
 * $Revision: 1.1 $  $Date: 1999/09/08 05:30:25 $
 */

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "linsys_solve.h"

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

/*****************************************************************
   taken from numerical recipes and modified to accept pointers
   moreover numerical recipes code seems to be buggy (at least the
   printed one

   cholesky solver and backsubstitution
   leaves upper right triangle intact (rows first order)
   ***************************************************************/

void choldc(double a[], int n, double p[], double f[])
{
  void nrerror(char error_text[]);
  int i, j, k;
  double sum;
  *f=0 ;
  for (i = 0; i < n; i++){
    for (j = i; j < n; j++) {
      sum=a[n*i + j];
      for (k=i-1; k>=0; k--) sum -= a[n*i + k]*a[n*j + k];
      if (i == j) {
	if (sum <= 0.0)
	{
	  *f=1 ;
	  return ;
	}
	/*	  mexErrMsgTxt("choldc failed, matrix not positive definite");*/
	p[i]=sqrt(sum);
      } else a[n*j + i] = sum/p[i];
    }
  }
}

void cholsb(double a[], int n, double p[], double b[], double x[])
{
  int i, k;
  double sum;

  for (i=0; i<n; i++) {
    sum=b[i];
    for (k=i-1; k>=0; k--) sum -= a[n*i + k]*x[k];
    x[i]=sum/p[i];
  }

  for (i=n-1; i>=0; i--) {
    sum=x[i];
    for (k=i+1; k<n; k++) sum -= a[n*k + i]*x[k];
    x[i]=sum/p[i];
  }
}

/*****************************************************************
  the linear system solver 
 *****************************************************************/

void linsys_solve(double a[], int n, int k, double b[], double x[], int flag, double f[])
{
  unsigned int i,j ;
  double *p=calloc(n, sizeof(double)) ;

  choldc(a, n, p, f) ;
  if (*f>0) /* check result */
  {
    free(p) ; /* matrix is not positiv definite */
    return ;
  } ;

  for (i=0; i<k; i++)
    cholsb(a, n, p, &b[i*n], &x[i*n]) ;
  
  if (flag)
    for (i=0; i<n; i++)
      for (j=i+1; j<n; j++)
	a[j*n+i]=a[j+i*n] ;

  free(p) ;
}


#ifndef LINSYS_SOLVE_NOMEX
void
mexFunction(
    int nlhs,
    Matrix *plhs[],
    int nrhs,
    mexFuncConst Matrix *prhs[])
{
  double *a, *b, *x, *f ;
  unsigned int m, n, k; 

  if ((nrhs!=2) || (nlhs!=1))
  {
    mexErrMsgTxt("x=linsys_solve(A, b)") ;
    return ;
  } ;

  a=mxGetPr(prhs[0]) ; assert(a!=0) ; 
  b=mxGetPr(prhs[1]) ; assert(b!=0) ;

  n=mxGetN(prhs[0]) ;
  m=mxGetM(prhs[0]) ;
  k=mxGetN(prhs[1]) ;

  /*printf("%i, %i, %i, %i", a,b,l,m) ;*/
  if (m!=n)
  {
    mexErrMsgTxt("Dimension error (arg 1).");
    return ;
  } ;
  if ((mxGetM(prhs[1])!=m))
  {
    mexErrMsgTxt("Dimension error (arg 2).");
    return ;
  } ;
  plhs[0]=(mxArray*)mxCreateDoubleMatrix(m, k, mxREAL) ; 
  x = mxGetPr(plhs[0]);
  plhs[1]=(mxArray*)mxCreateDoubleMatrix(1, 1, mxREAL) ; 
  f = mxGetPr(plhs[1]);
    
  linsys_solve(a, n, k, b, x, 1, f) ;
} 

#endif


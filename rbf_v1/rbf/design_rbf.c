#include <math.h>
#include "lapack.h"
#include "design_rbf.h"

void rbf_dot(double * x, double * y, double *z, double *Inp, double *rbf_sigma,
	     int n1, int n2, int m)
{
  int i,j;

  double mul_2 = 2.0;
  double mul_0 = 0.0;
  const int increment = 1;
  const char no_transpose = 'N';
  const char	transpose = 'T';

  double *ptr, *ptr_stop;
  double *x_sqr, *y_sqr;

  x_sqr = calloc(n1, sizeof(double));
  for (i=0, ptr = x; i<n1; i++) {
    x_sqr[i] = F77NAME(ddot)(F77R(m), ptr, F77R(increment), ptr, F77R(increment));
    ptr += m;
  }

  y_sqr = calloc(n2, sizeof(double));
  for (i=0, ptr = y; i<n2; i++) {
    y_sqr[i] = F77NAME(ddot)(F77R(m), ptr, F77R(increment), ptr, F77R(increment));
    ptr += m;
  }

  F77NAME(dgemm)(F77R(transpose),F77R(no_transpose),F77R(n1),F77R(n2),
		 F77R(m),F77R(mul_2),x,F77R(m),y,F77R(m),F77R(mul_0),z,F77R(n1));
  
  if (Inp)
    for (j=0; j<n2; j++) 
      {
	double sqr_sigma_j=rbf_sigma[j]*rbf_sigma[j] ;
	for (i=0; i<n1; i++) {
	  double elem ;
	  elem=(z[j * n1 + i] - x_sqr[i] - y_sqr[j])/sqr_sigma_j ;
	  z[j * n1 + i] = exp(elem);
	  Inp[j * n1 + i] = -elem ;
	}
      } 
  else
    for (j=0; j<n2; j++) 
      {
	double sqr_sigma_j=rbf_sigma[j]*rbf_sigma[j] ;
	for (i=0; i<n1; i++) {
	  double elem ;
	  elem=(z[j * n1 + i] - x_sqr[i] - y_sqr[j])/sqr_sigma_j ;
	  z[j * n1 + i] = exp(elem);
	}
      } ;

  free(x_sqr);
  free(y_sqr);
}

void design_rbf(double * X, double * C, double *H, double *Inp, double *sigma,
	     unsigned int n1, unsigned int n2, unsigned int m)
{
  rbf_dot(X, C, H, Inp, sigma, n1, n2, m) ;
  return ;
}










#ifndef __LINSYS_SOLVE_H__
#define __LINSYS_SOLVE_H__

extern void choldc(double a[], int n, double p[], double f[]) ;
extern void cholsb(double a[], int n, double p[], double b[], double x[]) ;
extern void linsys_solve(double a[], int n, int k, double b[], double x[], int flag, double f[]) ;

#endif

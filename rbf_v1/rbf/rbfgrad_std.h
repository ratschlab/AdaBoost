#ifndef __RBFGRAD_STD_H__
#define __RBFGRAD_STD_H__

extern void 
rbfgrad_std(double *X, double *Y, double *O, double *mu, double *sigma, 
	    double *w, double *H, double *Inp,
	    unsigned int a, unsigned int b, unsigned int m, 
	    unsigned int l, double *C_mu, double *C_sigma) ;

#endif 

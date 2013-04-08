/*
 * Author:      Sebastian Mika, GMD First
 * $Id: symeigx.h,v 1.1 1999/09/08 05:30:01 raetsch_cvs Exp $
 */

#ifdef CBLAS
extern int    ilaenv_(const int *, const char *, const char *, const int *, 
		      const int *, const int *, const int *, long, long);
extern void   dsyevx_(const char *, const char *, const char *, const int *, 
		      double *, const int *, const double *, const double *, 
		      const int *, const int *, const double *, const int *, 
		      double *, double *, const int *, double *, int *, 
		      int *, int *, int *);
extern void   dpotrf_(const char *, const int *, double *, const int *, int *);
extern void   dsygst_(const int *, const char *, const int *, double *, 
		      const int *, double *, const int *, int *);
extern void   dtrsm_(const char *, const char *, const char *, const char *, 
		     const int *, const int *, const double *, double *, 
		     const int *, double *, const int *);
extern double dlamch_(char *cmach);

#define DPOTRF(a1,a2,a3,a4,a5)   dpotrf_(&a1,&a2,a3,&a4,a5)
#define DSYGST(a1,a2,a3,a4,a5,a6,a7,a8)  dsygst_(&a1,&a2,&a3,a4,&a5,a6,&a7,a8)
#define DTRSM(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11)       \
dtrsm_(&a1,&a2,&a3,&a4,&a5,&a6,&a7,a8,&a9,a10,&a11)
#define DLAMCH(a) dlamch_(&a)
#else
extern void   dsyevx(const char, const char, const char, const int, 
		     double *, const int, const double, const double, 
		     const int, const int, const double, const int*, double *, 
		     double *, const int, int *, int *);
extern void   dpotrf(const char, const int, double*, const int, int*);
extern void   dsygst(const int, const char, const int, double*, 
		     const int, double*, const int, int*);
extern void   dtrsm(const char, const char, const char, const char,
		    const int, const int, const double, double*, 
		    const int, double*, const int);
extern double dlamch(const char);

#define DPOTRF dpotrf
#define DSYGST dsygst
#define DTRSM  dtrsm
#define DLAMCH dlamch
#endif
     
extern void symeigx(double a[], 
	      int n,
	      double d[],
	      double v[],
	      int    l,
	      int    *fl);









#include "intel_blas.h"

#ifdef __cplusplus
extern "C" {
#endif
	
#ifndef MSWINDOWS
#define F77R(x) x
#define F77P(x) x
#define F77NAME(x) x
#else
#define F77R(x) & x
#define F77P(x) x*
#define F77NAME(x) x ## _
#endif

#ifdef UNIX
void dsyev(F77P(const char) jobz, F77P(const char) uplo, F77P(const int) N, double* DA, F77P(const int) LDA, 
           double* DV, int* info);
#else
void  F77NAME(dsyev)(F77P(char) jobz, F77P(const char) uplo, 
		    F77P(const int) N, double* DA, F77P(const int) LDA, 
		    double* DV, double* DWork, F77P(const int) LDWork,
		    int* info);
#endif // UNIX

/*DGEEV( JOBVL, JOBVR, N, A, LDA, WR, WI, VL, LDVL, VR,
	     LDVR, WORK, LWORK, INFO ) */
void F77NAME(dgeev)(F77P(const char) jobz, F77P(const char) uplo, F77P(const int) N, 
		    double *DA, F77P(const int) LDA, double DWR[], 
		    double DWI[], double DVL[], F77P(const int) LDVL, double DVR[], 
		    F77P(const int) LDVR, double DWORK[], int* LDWORK, int* INFO);

/*DGEEVX( BALANC, JOBVL, JOBVR, SENSE, N, A, LDA, WR, WI,
          VL, LDVL, VR, LDVR, ILO, IHI, SCALE, ABNRM,
          RCONDE, RCONDV, WORK, LWORK, IWORK, INFO ) */
void F77NAME(dgeevx)(F77P(const char) BALANC, F77P(const char) JOBVL, F77P(const char) JOBVR, 
		     F77P(const char) SENSE, F77P(const int) N, double *DA, F77P(const int) LDA, 
		     double *DWR, double *DWI, double *DVL, F77P(const int) LDVL, 
		     double *DVR, F77P(const int) LDVR, int* ILO, int* IHI, double* DSCALE, 
		     double* DABNRM, double* DRCONE, double* DRCONV, double* DWORK, 
		     F77P(const int) LDWORK, int* IWORK2, int* INFO);

void F77NAME(dcopy)(F77P(const int) N, const double *DX, F77P(const int) INCX, 
		    double *DY, F77P(const int) INCY) ;

void F77NAME(dgemm)(F77P(const char)TRANSA, F77P(const char)TRANSB, F77P(const int) M, 
		    F77P(const int) N, F77P(const int) K, 
                    F77P(const double) DALPHA, const double* DA, F77P(const int) LDA, 
		    const double* DB, F77P(const int) LDB, 
                    F77P(const double) DBETA, double* DC, F77P(const int) LDC) ;

void F77NAME(dtrans)(F77P(const char) PLACE, double* DSCALE, double* DSOURCE, 
		     F77P(const int) M, F77P(const int) N, double* DDEST) ;

double F77NAME(ddot)(F77P(const int)N, double* DX, F77P(const int)INCX, 
		     double* DY, F77P(const int)INCY) ;

void F77NAME(dgesv)(F77P(const int) N, F77P(const int) NRHS, double* DA, 
		    F77P(const int) LDA, int* IPIVOT, double* DB, F77P(const int) LDB, 
		    int* INFO) ;

double F77NAME(dnrm2)(F77P(const int) N, const double *DX, F77P(const int) INCX) ;

void F77NAME(daxpy)(F77P(const int) N, F77P(const double) DALPHA, double* DX, 
		    F77P(const int) INCX, double* DY, F77P(const int) INCY) ;

/*DGESVD( JOBU, JOBVT, M, N, A, LDA, S, U, LDU, VT, LDVT, WORK, LWORK, INFO ) */
void F77NAME(dgesvd)(F77P(const char) JOBU, F77P(const char) JOBVT, F77P(const int) M, 
		     F77P(const int) N, double* DA, F77P(const int) LDA, double* DSING, 
		     double* DU, F77P(const int) LDU, double* DVT, F77P(const int) LDVT, 
		     double* DWORK, F77P(const int) LDWORK, int* INFO) ;

int F77NAME(idamax)(F77P(const int) N, double *DX, F77P(const int) INCX) ;

double F77NAME(dasum)(F77P(const int) N, const double *DX, F77P(const int) INCX) ;

/*DGEMV(TRANSA, M, N, DALPHA, DA, LDA, DX, INCX, DBETA, DY, INCY) */
void F77NAME(dgemv)(F77P(const char) TRANSA, F77P(const int)M, F77P(const int)N,  
                    F77P(const double) DALPHA, const double* DA, F77P(const int) LDA, 
		    const double* DX, F77P(const int) INCX, F77P(const double) DBETA, 
		    double* DY, F77P(const int) INCY) ;

void F77NAME(dscal)(F77P(const int) n, F77P(const double) da, double* dx, F77P(const int) incx) ;

#ifdef __cplusplus
}
#endif


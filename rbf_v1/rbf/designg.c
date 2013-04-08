static char mc_version[] = "MATLAB Compiler 1.0 infun";
/*
 *  MATLAB Compiler: 1.0
 *  Date: Oct 20, 1995
 *  Arguments: designg 
 */
#include <math.h>
#include "mex.h"
#include "mcc.h"

/* static array S0_ (1 x 26) text, line 21: 'rbfDesign: mismatched X, ...' */
static double S0__r_[] =
{
        114,   98,  102,   68,  101,  115,  105,  103,
        110,   58,   32,  109,  105,  115,  109,   97,
        116,   99,  104,  101,  100,   32,   88,   44,
         32,   67,
};
static Matrix S0_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 26, S0__r_, 0, -1, 0, {0} };
/* static array S1_ (1 x 19) text, line 31: 'DesignG: use Design' */
static double S1__r_[] =
{
         68,  101,  115,  105,  103,  110,   71,   58,
         32,  117,  115,  101,   32,   68,  101,  115,
        105,  103,  110,
};
static Matrix S1_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 19, S1__r_, 0, -1, 0, {0} };
/* static array S2_ (1 x 26) text, line 21: 'rbfDesign: mismatched X, ...' */
static double S2__r_[] =
{
        114,   98,  102,   68,  101,  115,  105,  103,
        110,   58,   32,  109,  105,  115,  109,   97,
        116,   99,  104,  101,  100,   32,   88,   44,
         32,   67,
};
static Matrix S2_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 26, S2__r_, 0, -1, 0, {0} };
/* static array S3_ (1 x 19) text, line 31: 'DesignG: use Design' */
static double S3__r_[] =
{
         68,  101,  115,  105,  103,  110,   71,   58,
         32,  117,  115,  101,   32,   68,  101,  115,
        105,  103,  110,
};
static Matrix S3_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 19, S3__r_, 0, -1, 0, {0} };

void
mexFunction(
    int nlhs_,
    Matrix *plhs_[],
    int nrhs_,
    Matrix *prhs_[]
)
{
   int ci_, i_, j_;
   unsigned flags_;
   Matrix *Mplhs_[32], *Mprhs_[32];
   for (ci_=i_=0; i_<nrhs_; ++i_)
   {
      if (prhs_[i_]->pi)
      {
         ci_ = 1;
         break;
      }
      if (prhs_[i_]->pr)
      {
         break;
      }
   }
   if (ci_)
   {
/***************** Compiler Assumptions ****************
 *
 *       C           	complex vector/matrix
 *       C0_         	complex scalar temporary
 *       CM0_        	complex vector/matrix temporary
 *       D           	complex vector/matrix
 *       H           	complex vector/matrix
 *       Inp         	complex vector/matrix
 *       R           	complex vector/matrix
 *       RM0_        	real vector/matrix temporary
 *       RM1_        	real vector/matrix temporary
 *       SCALING_TYPE	integer scalar
 *       X           	complex vector/matrix
 *       designg     	<function being defined>
 *       diagprod    	<function>
 *       dupcol      	<function>
 *       error       	<function>
 *       exp         	<function>
 *       h           	complex vector/matrix
 *       j           	integer scalar
 *       m           	integer scalar
 *       n           	integer scalar
 *       n1          	integer scalar
 *       p           	integer scalar
 *       rc          	integer scalar
 *       rr          	integer scalar
 *       s           	complex vector/matrix
 *       size        	<function>
 *       zeros       	<function>
 *******************************************************/
      Matrix H;
      Matrix Inp;
      Matrix X;
      Matrix C;
      Matrix R;
      int n;
      int p;
      int n1;
      int m;
      int rr;
      int rc;
      int SCALING_TYPE;
      int j;
      Matrix D;
      Matrix s;
      Matrix h;
      Matrix RM0_;
      Matrix RM1_;
      Matrix CM0_;
      double C0__r, C0__i;
      
      mccComplexInit(X);
      mccImport(&X, ((nrhs_>0) ? prhs_[0] : 0), 0, 0);
      mccComplexInit(C);
      mccImport(&C, ((nrhs_>1) ? prhs_[1] : 0), 0, 0);
      mccComplexInit(R);
      mccImport(&R, ((nrhs_>2) ? prhs_[2] : 0), 0, 0);
      mccComplexInit(H);
      mccComplexInit(Inp);
      mccComplexInit(D);
      mccComplexInit(s);
      mccComplexInit(h);
      mccRealInit(RM0_);
      mccRealInit(RM1_);
      mccComplexInit(CM0_);
      
      /* % [H, Inp] = Design(X, C, R) */
      
      /* % Gets the design matrix from the input data, centre positions */
      /* % and radii factors. */
      
      /* % Input */
      /* % X       Input training data (n-by-p) */
      /* % C       List of centres (n-by-m) */
      /* % R       Scale factors: scalar, n-vector, or n-by-n matrix */
      
      /* % Output */
      /* % H       Design matrix (p-by-m) */
      /* % Inp     p-by-m Matrix of the Norms ... (only for R=nvector) */
      
      
      /* % preliminary sizing */
      /* [n, p] = size(X); */
      if( X.flags & mccNOTSET )
      {
         mexErrMsgTxt( "variable X undefined, line 18" );
      }
      mccGetMatrixSize(&n,&p, &X);
      /* [n1, m] = size(C); */
      if( C.flags & mccNOTSET )
      {
         mexErrMsgTxt( "variable C undefined, line 19" );
      }
      mccGetMatrixSize(&n1,&m, &C);
      /* if n ~= n1 */
      if ((n != n1))
      {
         /* error('rbfDesign: mismatched X, C') */
         mccError(&S0_);
         /* end */
      }
      /* [rr, rc] = size(R) ; */
      if( R.flags & mccNOTSET )
      {
         mexErrMsgTxt( "variable R undefined, line 23" );
      }
      mccGetMatrixSize(&rr,&rc, &R);
      
      /* % determine scaling type */
      /* if rr == m & rc == 1 */
      if ((double)(!!(rr == m) && !!(rc == 1)))
      {
         /* SCALING_TYPE = 4;       % different radius for each centre */
         SCALING_TYPE = 4;
         /* elseif rr == 1 & rc == m */
      }
      else
      {
         if ((double)(!!(rr == 1) && !!(rc == m)))
         {
            /* SCALING_TYPE = 4;       % different radius for each centre */
            SCALING_TYPE = 4;
            /* else */
         }
         else
         {
            /* error('DesignG: use Design') */
            mccError(&S1_);
            /* end ; */
         }
      }
      
      /* % start constructing H */
      /* H = zeros(p, m); */
      mccZerosMN(&H, p, m);
      /* Inp = H ; */
      mccCopy(&Inp, &H);
      /* for j = 1:m */
      for (j = 1; j <= m; j = j + 1)
      {
         /* % get p difference vectors for this centre */
         /* D = X - dupcol( C(: , j) , p) ; */
         RM0_.dmode = mxNUMBER;
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_RM0_;
            int I_RM0_=1;
            double *p_C;
            int I_C=1, J_C;
            m_ = mcmCalcResultSize(m_, &n_, C.m, 1);
            mccAllocateMatrix(&RM0_, m_, n_);
            mccCheckMatrixSize(&C, m_, j);
            I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
            p_RM0_ = RM0_.pr;
            if (C.m == 1 && C.n == 1) { I_C = J_C = 0; }
            else { I_C=1; J_C=C.m-m_; }
            p_C = C.pr + 0 + C.m * (j-1);
            for (j_=0; j_<n_; ++j_, p_C += J_C)
            {
               for (i_=0; i_<m_; ++i_, p_RM0_+=I_RM0_, p_C+=I_C)
               {
                  *p_RM0_ = *p_C;
                  ;
               }
            }
         }
         RM0_.dmode = C.dmode;
         Mprhs_[0] = &RM0_;
         Mprhs_[1] = mccTempMatrix((double)(p), 0., mxNUMBER);
         Mplhs_[0] = &RM1_;
         mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "dupcol", 39);
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_D;
            int I_D=1;
            double *q_D;
            double *p_X;
            int I_X=1;
            double *q_X;
            double *p_RM1_;
            int I_RM1_=1;
            m_ = mcmCalcResultSize(m_, &n_, X.m, X.n);
            m_ = mcmCalcResultSize(m_, &n_, RM1_.m, RM1_.n);
            mccAllocateMatrix(&D, m_, n_);
            I_D = (D.m != 1 || D.n != 1);
            p_D = D.pr;
            q_D = D.pi;
            I_X = (X.m != 1 || X.n != 1);
            p_X = X.pr;
            q_X = X.pi;
            I_RM1_ = (RM1_.m != 1 || RM1_.n != 1);
            p_RM1_ = RM1_.pr;
            for (j_=0; j_<n_; ++j_)
            {
               for (i_=0; i_<m_; ++i_, p_D+=I_D, q_D+=I_D, p_X+=I_X, q_X+=I_X, p_RM1_+=I_RM1_)
               {
                  *p_D = (*p_X - *p_RM1_);
                  *q_D = (*q_X - 0.);
                  ;
               }
            }
         }
         D.dmode = mxNUMBER;
         
         /* % do metric calculation */
         /* s = diagprod(D',D) / R(j)^2; */
         mccConjTrans(&CM0_, &D);
         Mprhs_[0] = &CM0_;
         Mprhs_[1] = &D;
         Mplhs_[0] = &RM1_;
         mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "diagprod", 42);
         mcmPower(&C0__r, &C0__i, (mccGetRealVectorElement(&R, (int)j)), mccGetImagVectorElement(&R, (int)j), (double)2, 0.);
         mccRightDivide(&s, &RM1_, mccTempMatrix(C0__r, C0__i, mxNUMBER|mccCOMPLEX));
         /* Inp(:,j) = s ; */
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_Inp;
            int I_Inp=1, J_Inp;
            double *q_Inp;
            double *p_s;
            int I_s=1;
            double *q_s;
            m_ = mcmCalcResultSize(m_, &n_, s.m, s.n);
            mccGrowMatrix(&Inp, m_, j);
            if (Inp.m == 1 && Inp.n == 1) { I_Inp = J_Inp = 0; }
            else { I_Inp=1; J_Inp=Inp.m-m_; }
            p_Inp = Inp.pr + 0 + Inp.m * (j-1);
            q_Inp = Inp.pi + 0 + Inp.m * (j-1);
            I_s = (s.m != 1 || s.n != 1);
            p_s = s.pr;
            q_s = s.pi;
            for (j_=0; j_<n_; ++j_, p_Inp += J_Inp, q_Inp += J_Inp)
            {
               for (i_=0; i_<m_; ++i_, p_Inp+=I_Inp, q_Inp+=I_Inp, p_s+=I_s, q_s+=I_s)
               {
                  *p_Inp = *p_s;
                  *q_Inp = *q_s;
                  ;
               }
            }
         }
         Inp.dmode = mxNUMBER;
         
         /* h = exp(-s); */
         CM0_.dmode = mxNUMBER;
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_CM0_;
            int I_CM0_=1;
            double *q_CM0_;
            double *p_s;
            int I_s=1;
            double *q_s;
            m_ = mcmCalcResultSize(m_, &n_, s.m, s.n);
            mccAllocateMatrix(&CM0_, m_, n_);
            I_CM0_ = (CM0_.m != 1 || CM0_.n != 1);
            p_CM0_ = CM0_.pr;
            q_CM0_ = CM0_.pi;
            I_s = (s.m != 1 || s.n != 1);
            p_s = s.pr;
            q_s = s.pi;
            for (j_=0; j_<n_; ++j_)
            {
               for (i_=0; i_<m_; ++i_, p_CM0_+=I_CM0_, q_CM0_+=I_CM0_, p_s+=I_s, q_s+=I_s)
               {
                  *p_CM0_ = (-*p_s);
                  *q_CM0_ = (- *q_s);
                  ;
               }
            }
         }
         CM0_.dmode = mxNUMBER;
         Mprhs_[0] = &CM0_;
         Mplhs_[0] = &h;
         mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "exp", 45);
         
         /* % insert result in H */
         /* H(:, j) = h; */
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_H;
            int I_H=1, J_H;
            double *q_H;
            double *p_h;
            int I_h=1;
            double *q_h;
            m_ = mcmCalcResultSize(m_, &n_, h.m, h.n);
            mccGrowMatrix(&H, m_, j);
            if (H.m == 1 && H.n == 1) { I_H = J_H = 0; }
            else { I_H=1; J_H=H.m-m_; }
            p_H = H.pr + 0 + H.m * (j-1);
            q_H = H.pi + 0 + H.m * (j-1);
            I_h = (h.m != 1 || h.n != 1);
            p_h = h.pr;
            q_h = h.pi;
            for (j_=0; j_<n_; ++j_, p_H += J_H, q_H += J_H)
            {
               for (i_=0; i_<m_; ++i_, p_H+=I_H, q_H+=I_H, p_h+=I_h, q_h+=I_h)
               {
                  *p_H = *p_h;
                  *q_H = *q_h;
                  ;
               }
            }
         }
         H.dmode = mxNUMBER;
         /* end */
      }
      
      mccReturnFirstValue(&plhs_[0], &H);
      mccReturnValue(&plhs_[1], &Inp);
   }
   else
   {
/***************** Compiler Assumptions ****************
 *
 *       C           	real vector/matrix
 *       D           	real vector/matrix
 *       H           	real vector/matrix
 *       Inp         	real vector/matrix
 *       R           	real vector/matrix
 *       R0_         	real scalar temporary
 *       RM0_        	real vector/matrix temporary
 *       RM1_        	real vector/matrix temporary
 *       SCALING_TYPE	integer scalar
 *       X           	real vector/matrix
 *       designg     	<function being defined>
 *       diagprod    	<function>
 *       dupcol      	<function>
 *       error       	<function>
 *       exp         	<function>
 *       h           	real vector/matrix
 *       j           	integer scalar
 *       m           	integer scalar
 *       n           	integer scalar
 *       n1          	integer scalar
 *       p           	integer scalar
 *       rc          	integer scalar
 *       rr          	integer scalar
 *       s           	real vector/matrix
 *       size        	<function>
 *       zeros       	<function>
 *******************************************************/
      Matrix H;
      Matrix Inp;
      Matrix X;
      Matrix C;
      Matrix R;
      int n;
      int p;
      int n1;
      int m;
      int rr;
      int rc;
      int SCALING_TYPE;
      int j;
      Matrix D;
      Matrix s;
      Matrix h;
      Matrix RM0_;
      Matrix RM1_;
      double R0_;
      
      mccRealInit(X);
      mccImport(&X, ((nrhs_>0) ? prhs_[0] : 0), 0, 0);
      mccRealInit(C);
      mccImport(&C, ((nrhs_>1) ? prhs_[1] : 0), 0, 0);
      mccRealInit(R);
      mccImport(&R, ((nrhs_>2) ? prhs_[2] : 0), 0, 0);
      mccRealInit(H);
      mccRealInit(Inp);
      mccRealInit(D);
      mccRealInit(s);
      mccRealInit(h);
      mccRealInit(RM0_);
      mccRealInit(RM1_);
      
      /* % [H, Inp] = Design(X, C, R) */
      
      /* % Gets the design matrix from the input data, centre positions */
      /* % and radii factors. */
      
      /* % Input */
      /* % X       Input training data (n-by-p) */
      /* % C       List of centres (n-by-m) */
      /* % R       Scale factors: scalar, n-vector, or n-by-n matrix */
      
      /* % Output */
      /* % H       Design matrix (p-by-m) */
      /* % Inp     p-by-m Matrix of the Norms ... (only for R=nvector) */
      
      
      /* % preliminary sizing */
      /* [n, p] = size(X); */
      if( X.flags & mccNOTSET )
      {
         mexErrMsgTxt( "variable X undefined, line 18" );
      }
      mccGetMatrixSize(&n,&p, &X);
      /* [n1, m] = size(C); */
      if( C.flags & mccNOTSET )
      {
         mexErrMsgTxt( "variable C undefined, line 19" );
      }
      mccGetMatrixSize(&n1,&m, &C);
      /* if n ~= n1 */
      if ((n != n1))
      {
         /* error('rbfDesign: mismatched X, C') */
         mccError(&S2_);
         /* end */
      }
      /* [rr, rc] = size(R) ; */
      if( R.flags & mccNOTSET )
      {
         mexErrMsgTxt( "variable R undefined, line 23" );
      }
      mccGetMatrixSize(&rr,&rc, &R);
      
      /* % determine scaling type */
      /* if rr == m & rc == 1 */
      if ((double)(!!(rr == m) && !!(rc == 1)))
      {
         /* SCALING_TYPE = 4;       % different radius for each centre */
         SCALING_TYPE = 4;
         /* elseif rr == 1 & rc == m */
      }
      else
      {
         if ((double)(!!(rr == 1) && !!(rc == m)))
         {
            /* SCALING_TYPE = 4;       % different radius for each centre */
            SCALING_TYPE = 4;
            /* else */
         }
         else
         {
            /* error('DesignG: use Design') */
            mccError(&S3_);
            /* end ; */
         }
      }
      
      /* % start constructing H */
      /* H = zeros(p, m); */
      mccZerosMN(&H, p, m);
      /* Inp = H ; */
      mccCopy(&Inp, &H);
      /* for j = 1:m */
      for (j = 1; j <= m; j = j + 1)
      {
         /* % get p difference vectors for this centre */
         /* D = X - dupcol( C(: , j) , p) ; */
         RM0_.dmode = mxNUMBER;
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_RM0_;
            int I_RM0_=1;
            double *p_C;
            int I_C=1, J_C;
            m_ = mcmCalcResultSize(m_, &n_, C.m, 1);
            mccAllocateMatrix(&RM0_, m_, n_);
            mccCheckMatrixSize(&C, m_, j);
            I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
            p_RM0_ = RM0_.pr;
            if (C.m == 1 && C.n == 1) { I_C = J_C = 0; }
            else { I_C=1; J_C=C.m-m_; }
            p_C = C.pr + 0 + C.m * (j-1);
            for (j_=0; j_<n_; ++j_, p_C += J_C)
            {
               for (i_=0; i_<m_; ++i_, p_RM0_+=I_RM0_, p_C+=I_C)
               {
                  *p_RM0_ = *p_C;
                  ;
               }
            }
         }
         RM0_.dmode = C.dmode;
         Mprhs_[0] = &RM0_;
         Mprhs_[1] = mccTempMatrix((double)(p), 0., mxNUMBER);
         Mplhs_[0] = &RM1_;
         mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "dupcol", 39);
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_D;
            int I_D=1;
            double *p_X;
            int I_X=1;
            double *p_RM1_;
            int I_RM1_=1;
            m_ = mcmCalcResultSize(m_, &n_, X.m, X.n);
            m_ = mcmCalcResultSize(m_, &n_, RM1_.m, RM1_.n);
            mccAllocateMatrix(&D, m_, n_);
            I_D = (D.m != 1 || D.n != 1);
            p_D = D.pr;
            I_X = (X.m != 1 || X.n != 1);
            p_X = X.pr;
            I_RM1_ = (RM1_.m != 1 || RM1_.n != 1);
            p_RM1_ = RM1_.pr;
            for (j_=0; j_<n_; ++j_)
            {
               for (i_=0; i_<m_; ++i_, p_D+=I_D, p_X+=I_X, p_RM1_+=I_RM1_)
               {
                  *p_D = (*p_X - *p_RM1_);
                  ;
               }
            }
         }
         D.dmode = mxNUMBER;
         
         /* % do metric calculation */
         /* s = diagprod(D',D) / R(j)^2; */
         mccConjTrans(&RM1_, &D);
         Mprhs_[0] = &RM1_;
         Mprhs_[1] = &D;
         Mplhs_[0] = &RM0_;
         mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "diagprod", 42);
         R0_ = mcmRealPowerInt((mccGetRealVectorElement(&R, j)), 2);
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_s;
            int I_s=1;
            double *p_RM0_;
            int I_RM0_=1;
            m_ = mcmCalcResultSize(m_, &n_, RM0_.m, RM0_.n);
            mccAllocateMatrix(&s, m_, n_);
            I_s = (s.m != 1 || s.n != 1);
            p_s = s.pr;
            I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
            p_RM0_ = RM0_.pr;
            for (j_=0; j_<n_; ++j_)
            {
               for (i_=0; i_<m_; ++i_, p_s+=I_s, p_RM0_+=I_RM0_)
               {
                  *p_s = (*p_RM0_ / (double) R0_);
                  ;
               }
            }
         }
         s.dmode = mxNUMBER;
         /* Inp(:,j) = s ; */
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_Inp;
            int I_Inp=1, J_Inp;
            double *p_s;
            int I_s=1;
            m_ = mcmCalcResultSize(m_, &n_, s.m, s.n);
            mccGrowMatrix(&Inp, m_, j);
            if (Inp.m == 1 && Inp.n == 1) { I_Inp = J_Inp = 0; }
            else { I_Inp=1; J_Inp=Inp.m-m_; }
            p_Inp = Inp.pr + 0 + Inp.m * (j-1);
            I_s = (s.m != 1 || s.n != 1);
            p_s = s.pr;
            for (j_=0; j_<n_; ++j_, p_Inp += J_Inp)
            {
               for (i_=0; i_<m_; ++i_, p_Inp+=I_Inp, p_s+=I_s)
               {
                  *p_Inp = *p_s;
                  ;
               }
            }
         }
         Inp.dmode = mxNUMBER;
         
         /* h = exp(-s); */
         RM0_.dmode = mxNUMBER;
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_RM0_;
            int I_RM0_=1;
            double *p_s;
            int I_s=1;
            m_ = mcmCalcResultSize(m_, &n_, s.m, s.n);
            mccAllocateMatrix(&RM0_, m_, n_);
            I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
            p_RM0_ = RM0_.pr;
            I_s = (s.m != 1 || s.n != 1);
            p_s = s.pr;
            for (j_=0; j_<n_; ++j_)
            {
               for (i_=0; i_<m_; ++i_, p_RM0_+=I_RM0_, p_s+=I_s)
               {
                  *p_RM0_ = (-*p_s);
                  ;
               }
            }
         }
         RM0_.dmode = mxNUMBER;
         Mprhs_[0] = &RM0_;
         Mplhs_[0] = &h;
         mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "exp", 45);
         
         /* % insert result in H */
         /* H(:, j) = h; */
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_H;
            int I_H=1, J_H;
            double *p_h;
            int I_h=1;
            m_ = mcmCalcResultSize(m_, &n_, h.m, h.n);
            mccGrowMatrix(&H, m_, j);
            if (H.m == 1 && H.n == 1) { I_H = J_H = 0; }
            else { I_H=1; J_H=H.m-m_; }
            p_H = H.pr + 0 + H.m * (j-1);
            I_h = (h.m != 1 || h.n != 1);
            p_h = h.pr;
            for (j_=0; j_<n_; ++j_, p_H += J_H)
            {
               for (i_=0; i_<m_; ++i_, p_H+=I_H, p_h+=I_h)
               {
                  *p_H = *p_h;
                  ;
               }
            }
         }
         H.dmode = mxNUMBER;
         /* end */
      }
      
      mccReturnFirstValue(&plhs_[0], &H);
      mccReturnValue(&plhs_[1], &Inp);
   }
   return;
}
                  
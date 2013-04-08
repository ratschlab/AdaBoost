static char mc_version[] = "MATLAB Compiler 1.0 infun";
/*
 *  MATLAB Compiler: 1.0
 *  Date: Oct 20, 1995
 *  Arguments: sqdist 
 *  *** suppressing complex case: no complex arguments ***
 */
#include <math.h>
#include "mex.h"
#include "mcc.h"

/* static array S0_ (1 x 26) text, line 27: 'Matrix sizes do not match...' */
static double S0__r_[] =
{
         77,   97,  116,  114,  105,  120,   32,  115,
        105,  122,  101,  115,   32,  100,  111,   32,
        110,  111,  116,   32,  109,   97,  116,   99,
        104,   46,
};
static Matrix S0_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 26, S0__r_, 0, -1, 0, {0} };

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
/***************** Compiler Assumptions ****************
 *
 *       RM0_        	real vector/matrix temporary
 *       RM1_        	real vector/matrix temporary
 *       RM2_        	real vector/matrix temporary
 *       abs         	<function>
 *       error       	<function>
 *       i           	integer scalar
 *       ones        	<function>
 *       p           	real vector/matrix
 *       p_Size      	real vector/matrix
 *       q           	integer scalar
 *       r           	integer scalar
 *       r2          	integer scalar
 *       s           	integer scalar
 *       size        	<function>
 *       sqdist      	<function being defined>
 *       sum         	<function>
 *       tic         	<function>
 *       toc         	<function>
 *       toc1        	real scalar
 *       toc2        	real scalar
 *       w           	real vector/matrix
 *       w_Size      	real vector/matrix
 *       x           	real vector/matrix
 *       y           	real vector/matrix
 *       zeros       	<function>
 *******************************************************/
   Matrix y;
   Matrix w;
   Matrix p;
   double toc1;
   int s;
   int r;
   int r2;
   int q;
   Matrix w_Size;
   Matrix p_Size;
   int i;
   Matrix x;
   double toc2;
   Matrix RM0_;
   Matrix RM1_;
   Matrix RM2_;
   
   mccRealInit(w);
   mccImport(&w, ((nrhs_>0) ? prhs_[0] : 0), 0, 0);
   mccRealInit(p);
   mccImport(&p, ((nrhs_>1) ? prhs_[1] : 0), 0, 0);
   mccRealInit(y);
   mccRealInit(w_Size);
   mccRealInit(p_Size);
   mccRealInit(x);
   mccRealInit(RM0_);
   mccRealInit(RM1_);
   mccRealInit(RM2_);
   
   /* % SQDIST Squared distances between vectors. */
   
   /* % SQDIST(W,P) */
   /* % W - SxR matrix of rows vectors. */
   /* % P - RxQ matrix of column vectors. */
   /* % Returns SxQ matrix of squared vectors distances. */
   
   /* % EXAMPLE: w = [1 2 1]; */
   /* % p = [1; 2.1; 0.9]; */
   /* % n = dist(w,p) */
   
   /* % Modified by Gunnar Raetsch */
   
   /* % #realonly */
   /* % #inbounds */
   
   /* toc1=toc  */
   Mplhs_[0] = 0;
   mccCallMATLAB(1, Mplhs_, 0, Mprhs_, "toc", 18);
   toc1 = mccImportReal(0, Mplhs_[ 0 ], " (sqdist, line 18): toc1");
   mccPrint (mccTempMatrix(toc1, 0., mxNUMBER), "toc1");
   /* tic; */
   Mplhs_[0] = 0;
   mccCallMATLAB(0, Mplhs_, 0, Mprhs_, "tic", 19);
   
   /* [s,r] = size(w); */
   mccGetMatrixSize(&s,&r, &w);
   /* [r2,q] = size(p); */
   mccGetMatrixSize(&r2,&q, &p);
   
   /* if r ~= r2,  */
   if ((r != r2))
   {
      /* w_Size=[s,r] */
      mccCatenateColumns(&w_Size, mccTempMatrix((double)(s), 0., mxNUMBER), mccTempMatrix((double)(r), 0., mxNUMBER));
      mccPrint (&w_Size, "w_Size");
      /* p_Size=[r2,q] */
      mccCatenateColumns(&p_Size, mccTempMatrix((double)(r2), 0., mxNUMBER), mccTempMatrix((double)(q), 0., mxNUMBER));
      mccPrint (&p_Size, "p_Size");
      /* error('Matrix sizes do not match.'), */
      mccError(&S0_);
      /* end */
   }
   
   /* y = zeros(s,q); */
   mccZerosMN(&y, s, q);
   
   /* if r == 1 */
   if ((r == 1))
   {
      /* for i=1:s */
      for (i = 1; i <= s; i = i + 1)
      {
         /* x = w(i,:)'*ones(1,q); */
         RM0_.dmode = mxNUMBER;
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_RM0_;
            int I_RM0_=1;
            double *p_w;
            int I_w=1, J_w;
            m_ = mcmCalcResultSize(m_, &n_, 1, w.n);
            mccAllocateMatrix(&RM0_, m_, n_);
            I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
            p_RM0_ = RM0_.pr;
            if (w.m == 1 && w.n == 1) { I_w = J_w = 0; }
            else { I_w=1; J_w=w.m-m_; }
            p_w = w.pr + (i-1) + w.m * 0;
            for (j_=0; j_<n_; ++j_, p_w += J_w)
            {
               for (i_=0; i_<m_; ++i_, p_RM0_+=I_RM0_, p_w+=I_w)
               {
                  *p_RM0_ = *p_w;
                  ;
               }
            }
         }
         RM0_.dmode = mxNUMBER;
         mccConjTrans(&RM1_, &RM0_);
         mccOnesMN(&RM2_, 1, q);
         mccRealMatrixMultiply(&x, &RM1_, &RM2_);
         /* y(i,:) = abs(x-p)^2; */
         RM2_.dmode = mxNUMBER;
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_RM2_;
            int I_RM2_=1;
            double *p_x;
            int I_x=1;
            double *p_p;
            int I_p=1;
            m_ = mcmCalcResultSize(m_, &n_, x.m, x.n);
            m_ = mcmCalcResultSize(m_, &n_, p.m, p.n);
            mccAllocateMatrix(&RM2_, m_, n_);
            I_RM2_ = (RM2_.m != 1 || RM2_.n != 1);
            p_RM2_ = RM2_.pr;
            I_x = (x.m != 1 || x.n != 1);
            p_x = x.pr;
            I_p = (p.m != 1 || p.n != 1);
            p_p = p.pr;
            for (j_=0; j_<n_; ++j_)
            {
               for (i_=0; i_<m_; ++i_, p_RM2_+=I_RM2_, p_x+=I_x, p_p+=I_p)
               {
                  *p_RM2_ = (*p_x - *p_p);
                  ;
               }
            }
         }
         RM2_.dmode = mxNUMBER;
         mccAbs(&RM1_, &RM2_);
         mccPower(&RM0_, &RM1_, mccTempMatrix((double)(2), 0., mxNUMBER));
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_y;
            int I_y=1, J_y;
            double *p_RM0_;
            int I_RM0_=1;
            m_ = mcmCalcResultSize(m_, &n_, RM0_.m, RM0_.n);
            if (y.m == 1 && y.n == 1) { I_y = J_y = 0; }
            else { I_y=1; J_y=y.m-m_; }
            p_y = y.pr + (i-1) + y.m * 0;
            I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
            p_RM0_ = RM0_.pr;
            for (j_=0; j_<n_; ++j_, p_y += J_y)
            {
               for (i_=0; i_<m_; ++i_, p_y+=I_y, p_RM0_+=I_RM0_)
               {
                  *p_y = *p_RM0_;
                  ;
               }
            }
         }
         y.dmode = mxNUMBER;
         /* end */
      }
      /* else */
   }
   else
   {
      /* for i=1:s */
      for (i = 1; i <= s; i = i + 1)
      {
         /* x = w(i,:)'*ones(1,q); */
         RM0_.dmode = mxNUMBER;
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_RM0_;
            int I_RM0_=1;
            double *p_w;
            int I_w=1, J_w;
            m_ = mcmCalcResultSize(m_, &n_, 1, w.n);
            mccAllocateMatrix(&RM0_, m_, n_);
            I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
            p_RM0_ = RM0_.pr;
            if (w.m == 1 && w.n == 1) { I_w = J_w = 0; }
            else { I_w=1; J_w=w.m-m_; }
            p_w = w.pr + (i-1) + w.m * 0;
            for (j_=0; j_<n_; ++j_, p_w += J_w)
            {
               for (i_=0; i_<m_; ++i_, p_RM0_+=I_RM0_, p_w+=I_w)
               {
                  *p_RM0_ = *p_w;
                  ;
               }
            }
         }
         RM0_.dmode = mxNUMBER;
         mccConjTrans(&RM1_, &RM0_);
         mccOnesMN(&RM2_, 1, q);
         mccRealMatrixMultiply(&x, &RM1_, &RM2_);
         /* y(i,:) = sum((x-p).^ 2); */
         RM2_.dmode = mxNUMBER;
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_RM2_;
            int I_RM2_=1;
            double *p_x;
            int I_x=1;
            double *p_p;
            int I_p=1;
            m_ = mcmCalcResultSize(m_, &n_, x.m, x.n);
            m_ = mcmCalcResultSize(m_, &n_, p.m, p.n);
            mccAllocateMatrix(&RM2_, m_, n_);
            I_RM2_ = (RM2_.m != 1 || RM2_.n != 1);
            p_RM2_ = RM2_.pr;
            I_x = (x.m != 1 || x.n != 1);
            p_x = x.pr;
            I_p = (p.m != 1 || p.n != 1);
            p_p = p.pr;
            for (j_=0; j_<n_; ++j_)
            {
               for (i_=0; i_<m_; ++i_, p_RM2_+=I_RM2_, p_x+=I_x, p_p+=I_p)
               {
                  *p_RM2_ = mcmRealPowerInt((*p_x - *p_p), 2);
                  ;
               }
            }
         }
         RM2_.dmode = mxNUMBER;
         mccSum(&RM1_, &RM2_);
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_y;
            int I_y=1, J_y;
            double *p_RM1_;
            int I_RM1_=1;
            m_ = mcmCalcResultSize(m_, &n_, RM1_.m, RM1_.n);
            if (y.m == 1 && y.n == 1) { I_y = J_y = 0; }
            else { I_y=1; J_y=y.m-m_; }
            p_y = y.pr + (i-1) + y.m * 0;
            I_RM1_ = (RM1_.m != 1 || RM1_.n != 1);
            p_RM1_ = RM1_.pr;
            for (j_=0; j_<n_; ++j_, p_y += J_y)
            {
               for (i_=0; i_<m_; ++i_, p_y+=I_y, p_RM1_+=I_RM1_)
               {
                  *p_y = *p_RM1_;
                  ;
               }
            }
         }
         y.dmode = mxNUMBER;
         /* end */
      }
      /* end */
   }
   
   /* toc2=toc  */
   Mplhs_[0] = 0;
   mccCallMATLAB(1, Mplhs_, 0, Mprhs_, "toc", 44);
   toc2 = mccImportReal(0, Mplhs_[ 0 ], " (sqdist, line 44): toc2");
   mccPrint (mccTempMatrix(toc2, 0., mxNUMBER), "toc2");
   mccReturnFirstValue(&plhs_[0], &y);
   return;
}

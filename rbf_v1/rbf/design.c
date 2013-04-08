static char mc_version[] = "MATLAB Compiler 1.0 infun";
/*
 *  MATLAB Compiler: 1.0
 *  Date: Oct 20, 1995
 *  Arguments: -ir design 
 */
#include <math.h>
#include "mex.h"
#include "mcc.h"

/* static array S0_ (1 x 25) text, line 45: 'rbfDesign: illegal option...' */
static double S0__r_[] =
{
        114,   98,  102,   68,  101,  115,  105,  103,
        110,   58,   32,  105,  108,  108,  101,  103,
         97,  108,   32,  111,  112,  116,  105,  111,
        110,
};
static Matrix S0_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 25, S0__r_, 0, -1, 0, {0} };
/* static array S1_ (1 x 26) text, line 56: 'rbfDesign: mismatched X, ...' */
static double S1__r_[] =
{
        114,   98,  102,   68,  101,  115,  105,  103,
        110,   58,   32,  109,  105,  115,  109,   97,
        116,   99,  104,  101,  100,   32,   88,   44,
         32,   67,
};
static Matrix S1_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 26, S1__r_, 0, -1, 0, {0} };
/* static array S2_ (1 x 40) text, line 71: 'rbfDesign: mismatched C a...' */
static double S2__r_[] =
{
        114,   98,  102,   68,  101,  115,  105,  103,
        110,   58,   32,  109,  105,  115,  109,   97,
        116,   99,  104,  101,  100,   32,   67,   32,
         97,  110,  100,   32,  114,  111,  119,   32,
        118,  101,   99,  116,  111,  114,   32,   82,
};
static Matrix S2_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 40, S2__r_, 0, -1, 0, {0} };
/* static array S3_ (1 x 40) text, line 79: 'rbfDesign: mismatched C a...' */
static double S3__r_[] =
{
        114,   98,  102,   68,  101,  115,  105,  103,
        110,   58,   32,  109,  105,  115,  109,   97,
        116,   99,  104,  101,  100,   32,   67,   32,
         97,  110,  100,   32,  114,  111,  119,   32,
        118,  101,   99,  116,  111,  114,   32,   82,
};
static Matrix S3_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 40, S3__r_, 0, -1, 0, {0} };
/* static array S4_ (1 x 36) text, line 88: 'rbfDesign: mismatched C a...' */
static double S4__r_[] =
{
        114,   98,  102,   68,  101,  115,  105,  103,
        110,   58,   32,  109,  105,  115,  109,   97,
        116,   99,  104,  101,  100,   32,   67,   32,
         97,  110,  100,   32,  109,   97,  116,  114,
        105,  120,   32,   82,
};
static Matrix S4_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 36, S4__r_, 0, -1, 0, {0} };
/* static array S5_ (1 x 36) text, line 95: 'rbfDesign: mismatched C a...' */
static double S5__r_[] =
{
        114,   98,  102,   68,  101,  115,  105,  103,
        110,   58,   32,  109,  105,  115,  109,   97,
        116,   99,  104,  101,  100,   32,   67,   32,
         97,  110,  100,   32,  109,   97,  116,  114,
        105,  120,   32,   82,
};
static Matrix S5_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 36, S5__r_, 0, -1, 0, {0} };
/* static array S6_ (1 x 24) text, line 98: 'rbfDesign: wrong sized R' */
static double S6__r_[] =
{
        114,   98,  102,   68,  101,  115,  105,  103,
        110,   58,   32,  119,  114,  111,  110,  103,
         32,  115,  105,  122,  101,  100,   32,   82,
};
static Matrix S6_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 24, S6__r_, 0, -1, 0, {0} };

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
 *       C           	real vector/matrix
 *       D           	real vector/matrix
 *       DR          	real vector/matrix
 *       H           	real vector/matrix
 *       I0_         	integer scalar temporary
 *       IR          	real vector/matrix
 *       Inp         	real vector/matrix
 *       R           	real vector/matrix
 *       R0_         	real scalar temporary
 *       RM0_        	real vector/matrix temporary
 *       RM1_        	real vector/matrix temporary
 *       RM2_        	real vector/matrix temporary
 *       SCALING_TYPE	integer scalar
 *       X           	real vector/matrix
 *       bias        	integer scalar
 *       design      	<function being defined>
 *       diagProd    	<function>
 *       dupCol      	<function>
 *       error       	<function>
 *       exp         	<function>
 *       h           	real vector/matrix
 *       inv         	<function>
 *       j           	integer scalar
 *       m           	integer scalar
 *       n           	integer scalar
 *       n1          	integer scalar
 *       nargin      	<function>
 *       ones        	<function>
 *       option      	real vector/matrix
 *       options     	real vector/matrix
 *       p           	integer scalar
 *       rc          	integer scalar
 *       realsqrt    	<function>
 *       rr          	integer scalar
 *       s           	real vector/matrix
 *       size        	<function>
 *       type        	integer scalar
 *       zeros       	<function>
 *******************************************************/
   Matrix H;
   Matrix Inp;
   Matrix X;
   Matrix C;
   Matrix R;
   Matrix options;
   int type;
   int bias;
   Matrix option;
   int n;
   int p;
   int n1;
   int m;
   int rr;
   int rc;
   int SCALING_TYPE;
   Matrix IR;
   int j;
   Matrix D;
   Matrix s;
   Matrix DR;
   Matrix h;
   int I0_;
   Matrix RM0_;
   Matrix RM1_;
   Matrix RM2_;
   double R0_;
   
   mccRealInit(X);
   mccImport(&X, ((nrhs_>0) ? prhs_[0] : 0), 0, 0);
   mccRealInit(C);
   mccImport(&C, ((nrhs_>1) ? prhs_[1] : 0), 0, 0);
   mccRealInit(R);
   mccImportCopy(&R, ((nrhs_>2) ? prhs_[2] : 0), 0, 0);
   mccRealInit(options);
   mccImport(&options, ((nrhs_>3) ? prhs_[3] : 0), 0, 0);
   mccRealInit(H);
   mccRealInit(Inp);
   mccRealInit(option);
   mccRealInit(IR);
   mccRealInit(D);
   mccRealInit(s);
   mccRealInit(DR);
   mccRealInit(h);
   mccRealInit(RM0_);
   mccRealInit(RM1_);
   mccRealInit(RM2_);
   
   /* % [H, Inp] = Design(X, C, R, options) */
   
   /* % Gets the design matrix from the input data, centre positions */
   /* % and radii factors. */
   
   /* % Input */
   /* % X       Input training data (n-by-p) */
   /* % C       List of centres (n-by-m) */
   /* % R       Scale factors: scalar, n-vector, or n-by-n matrix */
   /* % opt     Specifying basis function type ('g' for Gaussian, */
   /* % 'c' for Cauchy) and whether bias unit is rquired */
   /* % (if yes then 'b'). */
   
   /* % Output */
   /* % H       Design matrix (p-by-m) */
   /* % Inp     p-by-m Matrix of the Norms ... (only for R=nvector) */
   
   /* % default function type */
   /* % 'g' = gaussian (0) */
   /* % 'c' = cauchy (1) */
   /* % 'm' = multiquadric (2) */
   /* % 'i' = inverse multiquadric (3) */
   /* type = 0; */
   type = 0;
   
   /* % default bias */
   /* bias = 0; */
   bias = 0;
   
   /* % process options */
   /* if nargin > 3 */
   if ((mccNargin() > 3))
   {
      
      /* for option = options */
      for (I0_ = 0; I0_ < options.n; ++I0_)
      {
         mccForCol(&option, &options, I0_);
         
         /* if option == 'g' */
         RM0_.dmode = mxNUMBER;
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_RM0_;
            int I_RM0_=1;
            double *p_option;
            int I_option=1;
            m_ = mcmCalcResultSize(m_, &n_, option.m, option.n);
            mccAllocateMatrix(&RM0_, m_, n_);
            I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
            p_RM0_ = RM0_.pr;
            I_option = (option.m != 1 || option.n != 1);
            p_option = option.pr;
            for (j_=0; j_<n_; ++j_)
            {
               for (i_=0; i_<m_; ++i_, p_RM0_+=I_RM0_, p_option+=I_option)
               {
                  *p_RM0_ = (*p_option == 'g');
                  ;
               }
            }
         }
         RM0_.dmode = mxNUMBER;
         if (mccIfCondition(&RM0_))
         {
            /* type = 0; */
            type = 0;
            /* elseif option == 'c' */
         }
         else
         {
            RM0_.dmode = mxNUMBER;
            {
               int m_=1, n_=1, cx_ = 0;
               double t_;
               double *p_RM0_;
               int I_RM0_=1;
               double *p_option;
               int I_option=1;
               m_ = mcmCalcResultSize(m_, &n_, option.m, option.n);
               mccAllocateMatrix(&RM0_, m_, n_);
               I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
               p_RM0_ = RM0_.pr;
               I_option = (option.m != 1 || option.n != 1);
               p_option = option.pr;
               for (j_=0; j_<n_; ++j_)
               {
                  for (i_=0; i_<m_; ++i_, p_RM0_+=I_RM0_, p_option+=I_option)
                  {
                     *p_RM0_ = (*p_option == 'c');
                     ;
                  }
               }
            }
            RM0_.dmode = mxNUMBER;
            if (mccIfCondition(&RM0_))
            {
               /* type = 1; */
               type = 1;
               /* elseif option == 'm' */
            }
            else
            {
               RM0_.dmode = mxNUMBER;
               {
                  int m_=1, n_=1, cx_ = 0;
                  double t_;
                  double *p_RM0_;
                  int I_RM0_=1;
                  double *p_option;
                  int I_option=1;
                  m_ = mcmCalcResultSize(m_, &n_, option.m, option.n);
                  mccAllocateMatrix(&RM0_, m_, n_);
                  I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
                  p_RM0_ = RM0_.pr;
                  I_option = (option.m != 1 || option.n != 1);
                  p_option = option.pr;
                  for (j_=0; j_<n_; ++j_)
                  {
                     for (i_=0; i_<m_; ++i_, p_RM0_+=I_RM0_, p_option+=I_option)
                     {
                        *p_RM0_ = (*p_option == 'm');
                        ;
                     }
                  }
               }
               RM0_.dmode = mxNUMBER;
               if (mccIfCondition(&RM0_))
               {
                  /* type = 2; */
                  type = 2;
                  /* elseif option == 'i' */
               }
               else
               {
                  RM0_.dmode = mxNUMBER;
                  {
                     int m_=1, n_=1, cx_ = 0;
                     double t_;
                     double *p_RM0_;
                     int I_RM0_=1;
                     double *p_option;
                     int I_option=1;
                     m_ = mcmCalcResultSize(m_, &n_, option.m, option.n);
                     mccAllocateMatrix(&RM0_, m_, n_);
                     I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
                     p_RM0_ = RM0_.pr;
                     I_option = (option.m != 1 || option.n != 1);
                     p_option = option.pr;
                     for (j_=0; j_<n_; ++j_)
                     {
                        for (i_=0; i_<m_; ++i_, p_RM0_+=I_RM0_, p_option+=I_option)
                        {
                           *p_RM0_ = (*p_option == 'i');
                           ;
                        }
                     }
                  }
                  RM0_.dmode = mxNUMBER;
                  if (mccIfCondition(&RM0_))
                  {
                     /* type = 3; */
                     type = 3;
                     /* elseif option == 'b' */
                  }
                  else
                  {
                     RM0_.dmode = mxNUMBER;
                     {
                        int m_=1, n_=1, cx_ = 0;
                        double t_;
                        double *p_RM0_;
                        int I_RM0_=1;
                        double *p_option;
                        int I_option=1;
                        m_ = mcmCalcResultSize(m_, &n_, option.m, option.n);
                        mccAllocateMatrix(&RM0_, m_, n_);
                        I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
                        p_RM0_ = RM0_.pr;
                        I_option = (option.m != 1 || option.n != 1);
                        p_option = option.pr;
                        for (j_=0; j_<n_; ++j_)
                        {
                           for (i_=0; i_<m_; ++i_, p_RM0_+=I_RM0_, p_option+=I_option)
                           {
                              *p_RM0_ = (*p_option == 'b');
                              ;
                           }
                        }
                     }
                     RM0_.dmode = mxNUMBER;
                     if (mccIfCondition(&RM0_))
                     {
                        /* bias = 1; */
                        bias = 1;
                        /* else */
                     }
                     else
                     {
                        /* error('rbfDesign: illegal option') */
                        mccError(&S0_);
                        /* end */
                     }
                  }
               }
            }
         }
         
         /* end */
      }
      
      /* end */
   }
   
   /* % preliminary sizing */
   /* [n, p] = size(X); */
   mccGetMatrixSize(&n,&p, &X);
   /* [n1, m] = size(C); */
   mccGetMatrixSize(&n1,&m, &C);
   /* if n ~= n1 */
   if ((n != n1))
   {
      /* error('rbfDesign: mismatched X, C') */
      mccError(&S1_);
      /* end */
   }
   /* [rr, rc] = size(R); */
   mccGetMatrixSize(&rr,&rc, &R);
   
   /* % determine scaling type */
   /* if rr == 1 & rc == 1 */
   if ((double)(!!(rr == 1) && !!(rc == 1)))
   {
      /* SCALING_TYPE = 1;       % same radius for each centre */
      SCALING_TYPE = 1;
      /* elseif rr == 1 */
   }
   else
   {
      if ((rr == 1))
      {
         /* if rc == n */
         if ((rc == n))
         {
            /* SCALING_TYPE = 2;       % same diagonal metric for each centre */
            SCALING_TYPE = 2;
            /* R = R'; */
            mccConjTrans(&R, &R);
            /* elseif rc == m */
         }
         else
         {
            if ((rc == m))
            {
               /* SCALING_TYPE = 4;       % different radius for each centre */
               SCALING_TYPE = 4;
               /* R = R'; */
               mccConjTrans(&R, &R);
               /* else */
            }
            else
            {
               /* error('rbfDesign: mismatched C and row vector R') */
               mccError(&S2_);
               /* end */
            }
         }
         /* elseif rc == 1 */
      }
      else
      {
         if ((rc == 1))
         {
            /* if rr == n */
            if ((rr == n))
            {
               /* SCALING_TYPE = 2;       % same diagonal metric for each centre */
               SCALING_TYPE = 2;
               /* elseif rr == m */
            }
            else
            {
               if ((rr == m))
               {
                  /* SCALING_TYPE = 4;       % different radius for each centre */
                  SCALING_TYPE = 4;
                  /* else */
               }
               else
               {
                  /* error('rbfDesign: mismatched C and row vector R') */
                  mccError(&S3_);
                  /* end */
               }
            }
            /* elseif rr == n */
         }
         else
         {
            if ((rr == n))
            {
               /* if rc == n */
               if ((rc == n))
               {
                  /* SCALING_TYPE = 3;       % same metric for each centre */
                  SCALING_TYPE = 3;
                  /* IR = inv(R); */
                  Mprhs_[0] = &R;
                  Mplhs_[0] = &IR;
                  mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "inv", 84);
                  /* elseif rc == m */
               }
               else
               {
                  if ((rc == m))
                  {
                     /* SCALING_TYPE = 5;       % different diagonal metric for each centre */
                     SCALING_TYPE = 5;
                     /* else */
                  }
                  else
                  {
                     /* error('rbfDesign: mismatched C and matrix R') */
                     mccError(&S4_);
                     /* end */
                  }
               }
               /* elseif rc == n */
            }
            else
            {
               if ((rc == n))
               {
                  /* if rr == m */
                  if ((rr == m))
                  {
                     /* SCALING_TYPE = 5;       % different diagonal metric for each centre */
                     SCALING_TYPE = 5;
                     /* R = R'; */
                     mccConjTrans(&R, &R);
                     /* else */
                  }
                  else
                  {
                     /* error('rbfDesign: mismatched C and matrix R') */
                     mccError(&S5_);
                     /* end */
                  }
                  /* else */
               }
               else
               {
                  /* error('rbfDesign: wrong sized R') */
                  mccError(&S6_);
                  /* end */
               }
            }
         }
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
      /* D = X - dupCol( C(: , j) , p) ; */
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
      mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "dupCol", 106);
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
      /* if SCALING_TYPE == 1            % same radius for each centre */
      if ((SCALING_TYPE == 1))
      {
         /* s = diagProd ( D' , D ) / R^2 ; */
         mccConjTrans(&RM1_, &D);
         Mprhs_[0] = &RM1_;
         Mprhs_[1] = &D;
         Mplhs_[0] = &RM0_;
         mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "diagProd", 110);
         mccPower(&RM2_, &R, mccTempMatrix((double)(2), 0., mxNUMBER));
         mccRealRightDivide(&s, &RM0_, &RM2_);
         /* elseif SCALING_TYPE == 2        % same diagonal metric for each centre */
      }
      else
      {
         if ((SCALING_TYPE == 2))
         {
            /* DR = D ./ dupCol(R, p); */
            Mprhs_[0] = &R;
            Mprhs_[1] = mccTempMatrix((double)(p), 0., mxNUMBER);
            Mplhs_[0] = &RM2_;
            mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "dupCol", 112);
            {
               int m_=1, n_=1, cx_ = 0;
               double t_;
               double *p_DR;
               int I_DR=1;
               double *p_D;
               int I_D=1;
               double *p_RM2_;
               int I_RM2_=1;
               m_ = mcmCalcResultSize(m_, &n_, D.m, D.n);
               m_ = mcmCalcResultSize(m_, &n_, RM2_.m, RM2_.n);
               mccAllocateMatrix(&DR, m_, n_);
               I_DR = (DR.m != 1 || DR.n != 1);
               p_DR = DR.pr;
               I_D = (D.m != 1 || D.n != 1);
               p_D = D.pr;
               I_RM2_ = (RM2_.m != 1 || RM2_.n != 1);
               p_RM2_ = RM2_.pr;
               for (j_=0; j_<n_; ++j_)
               {
                  for (i_=0; i_<m_; ++i_, p_DR+=I_DR, p_D+=I_D, p_RM2_+=I_RM2_)
                  {
                     *p_DR = (*p_D / (double) *p_RM2_);
                     ;
                  }
               }
            }
            DR.dmode = mxNUMBER;
            /* s = diagProd(DR',DR); */
            mccConjTrans(&RM2_, &DR);
            Mprhs_[0] = &RM2_;
            Mprhs_[1] = &DR;
            Mplhs_[0] = &s;
            mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "diagProd", 113);
            /* elseif SCALING_TYPE == 3        % same metric for each centre */
         }
         else
         {
            if ((SCALING_TYPE == 3))
            {
               /* DR = IR * D; */
               mccRealMatrixMultiply(&DR, &IR, &D);
               /* s = diagProd(DR',DR); */
               mccConjTrans(&RM2_, &DR);
               Mprhs_[0] = &RM2_;
               Mprhs_[1] = &DR;
               Mplhs_[0] = &s;
               mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "diagProd", 116);
               /* elseif SCALING_TYPE == 4        % different radius for each centre */
            }
            else
            {
               if ((SCALING_TYPE == 4))
               {
                  /* s = diagProd(D',D) / R(j)^2; */
                  mccConjTrans(&RM2_, &D);
                  Mprhs_[0] = &RM2_;
                  Mprhs_[1] = &D;
                  Mplhs_[0] = &RM0_;
                  mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "diagProd", 118);
                  R0_ = mcmRealPowerInt((R.pr[(j-1)]), 2);
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
                  /* else                            % different diagonal metric for each centre */
               }
               else
               {
                  /* DR = D ./ dupCol(R(:,j), p); */
                  RM0_.dmode = mxNUMBER;
                  {
                     int m_=1, n_=1, cx_ = 0;
                     double t_;
                     double *p_RM0_;
                     int I_RM0_=1;
                     double *p_R;
                     int I_R=1, J_R;
                     m_ = mcmCalcResultSize(m_, &n_, R.m, 1);
                     mccAllocateMatrix(&RM0_, m_, n_);
                     I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
                     p_RM0_ = RM0_.pr;
                     if (R.m == 1 && R.n == 1) { I_R = J_R = 0; }
                     else { I_R=1; J_R=R.m-m_; }
                     p_R = R.pr + 0 + R.m * (j-1);
                     for (j_=0; j_<n_; ++j_, p_R += J_R)
                     {
                        for (i_=0; i_<m_; ++i_, p_RM0_+=I_RM0_, p_R+=I_R)
                        {
                           *p_RM0_ = *p_R;
                           ;
                        }
                     }
                  }
                  RM0_.dmode = R.dmode;
                  Mprhs_[0] = &RM0_;
                  Mprhs_[1] = mccTempMatrix((double)(p), 0., mxNUMBER);
                  Mplhs_[0] = &RM2_;
                  mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "dupCol", 121);
                  {
                     int m_=1, n_=1, cx_ = 0;
                     double t_;
                     double *p_DR;
                     int I_DR=1;
                     double *p_D;
                     int I_D=1;
                     double *p_RM2_;
                     int I_RM2_=1;
                     m_ = mcmCalcResultSize(m_, &n_, D.m, D.n);
                     m_ = mcmCalcResultSize(m_, &n_, RM2_.m, RM2_.n);
                     mccAllocateMatrix(&DR, m_, n_);
                     I_DR = (DR.m != 1 || DR.n != 1);
                     p_DR = DR.pr;
                     I_D = (D.m != 1 || D.n != 1);
                     p_D = D.pr;
                     I_RM2_ = (RM2_.m != 1 || RM2_.n != 1);
                     p_RM2_ = RM2_.pr;
                     for (j_=0; j_<n_; ++j_)
                     {
                        for (i_=0; i_<m_; ++i_, p_DR+=I_DR, p_D+=I_D, p_RM2_+=I_RM2_)
                        {
                           *p_DR = (*p_D / (double) *p_RM2_);
                           ;
                        }
                     }
                  }
                  DR.dmode = mxNUMBER;
                  /* s = diagProd(DR',DR); */
                  mccConjTrans(&RM2_, &DR);
                  Mprhs_[0] = &RM2_;
                  Mprhs_[1] = &DR;
                  Mplhs_[0] = &s;
                  mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "diagProd", 122);
                  /* end */
               }
            }
         }
      }
      
      /* % apply basis function */
      /* if type == 0            % Gaussian (default) */
      if ((type == 0))
      {
         
         /* h = exp(-s); */
         RM2_.dmode = mxNUMBER;
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_RM2_;
            int I_RM2_=1;
            double *p_s;
            int I_s=1;
            m_ = mcmCalcResultSize(m_, &n_, s.m, s.n);
            mccAllocateMatrix(&RM2_, m_, n_);
            I_RM2_ = (RM2_.m != 1 || RM2_.n != 1);
            p_RM2_ = RM2_.pr;
            I_s = (s.m != 1 || s.n != 1);
            p_s = s.pr;
            for (j_=0; j_<n_; ++j_)
            {
               for (i_=0; i_<m_; ++i_, p_RM2_+=I_RM2_, p_s+=I_s)
               {
                  *p_RM2_ = (-*p_s);
                  ;
               }
            }
         }
         RM2_.dmode = mxNUMBER;
         Mprhs_[0] = &RM2_;
         Mplhs_[0] = &h;
         mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "exp", 128);
         
         /* elseif type == 1        % Cauchy */
      }
      else
      {
         if ((type == 1))
         {
            
            /* h = 1 ./ (s + 1); */
            {
               int m_=1, n_=1, cx_ = 0;
               double t_;
               double *p_h;
               int I_h=1;
               double *p_s;
               int I_s=1;
               m_ = mcmCalcResultSize(m_, &n_, s.m, s.n);
               mccAllocateMatrix(&h, m_, n_);
               I_h = (h.m != 1 || h.n != 1);
               p_h = h.pr;
               I_s = (s.m != 1 || s.n != 1);
               p_s = s.pr;
               for (j_=0; j_<n_; ++j_)
               {
                  for (i_=0; i_<m_; ++i_, p_h+=I_h, p_s+=I_s)
                  {
                     *p_h = (1 / (double) (*p_s + 1));
                     ;
                  }
               }
            }
            h.dmode = mxNUMBER;
            
            /* elseif type == 2        % multiquadric */
         }
         else
         {
            if ((type == 2))
            {
               
               /* h = sqrt(s + 1); */
               RM2_.dmode = mxNUMBER;
               {
                  int m_=1, n_=1, cx_ = 0;
                  double t_;
                  double *p_RM2_;
                  int I_RM2_=1;
                  double *p_s;
                  int I_s=1;
                  m_ = mcmCalcResultSize(m_, &n_, s.m, s.n);
                  mccAllocateMatrix(&RM2_, m_, n_);
                  I_RM2_ = (RM2_.m != 1 || RM2_.n != 1);
                  p_RM2_ = RM2_.pr;
                  I_s = (s.m != 1 || s.n != 1);
                  p_s = s.pr;
                  for (j_=0; j_<n_; ++j_)
                  {
                     for (i_=0; i_<m_; ++i_, p_RM2_+=I_RM2_, p_s+=I_s)
                     {
                        *p_RM2_ = (*p_s + 1);
                        ;
                     }
                  }
               }
               RM2_.dmode = mxNUMBER;
               Mprhs_[0] = &RM2_;
               Mplhs_[0] = &h;
               mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "realsqrt", 136);
               
               /* elseif type == 3        % inverse multiquadric */
            }
            else
            {
               if ((type == 3))
               {
                  
                  /* h = 1 ./ sqrt(s + 1); */
                  RM2_.dmode = mxNUMBER;
                  {
                     int m_=1, n_=1, cx_ = 0;
                     double t_;
                     double *p_RM2_;
                     int I_RM2_=1;
                     double *p_s;
                     int I_s=1;
                     m_ = mcmCalcResultSize(m_, &n_, s.m, s.n);
                     mccAllocateMatrix(&RM2_, m_, n_);
                     I_RM2_ = (RM2_.m != 1 || RM2_.n != 1);
                     p_RM2_ = RM2_.pr;
                     I_s = (s.m != 1 || s.n != 1);
                     p_s = s.pr;
                     for (j_=0; j_<n_; ++j_)
                     {
                        for (i_=0; i_<m_; ++i_, p_RM2_+=I_RM2_, p_s+=I_s)
                        {
                           *p_RM2_ = (*p_s + 1);
                           ;
                        }
                     }
                  }
                  RM2_.dmode = mxNUMBER;
                  mccSqrt(&RM0_, &RM2_);
                  {
                     int m_=1, n_=1, cx_ = 0;
                     double t_;
                     double *p_h;
                     int I_h=1;
                     double *p_RM0_;
                     int I_RM0_=1;
                     m_ = mcmCalcResultSize(m_, &n_, RM0_.m, RM0_.n);
                     mccAllocateMatrix(&h, m_, n_);
                     I_h = (h.m != 1 || h.n != 1);
                     p_h = h.pr;
                     I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
                     p_RM0_ = RM0_.pr;
                     for (j_=0; j_<n_; ++j_)
                     {
                        for (i_=0; i_<m_; ++i_, p_h+=I_h, p_RM0_+=I_RM0_)
                        {
                           *p_h = (1 / (double) *p_RM0_);
                           ;
                        }
                     }
                  }
                  h.dmode = mxNUMBER;
                  
                  /* end */
               }
            }
         }
      }
      
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
   
   /* % add bias unit */
   /* if bias */
   if ((double)bias)
   {
      
      /* H = [H ones(p, 1)]; */
      mccOnesMN(&RM0_, p, 1);
      mccCatenateColumns(&H, &H, &RM0_);
      
      /* end */
   }
   mccReturnFirstValue(&plhs_[0], &H);
   mccReturnValue(&plhs_[1], &Inp);
   return;
}
                         
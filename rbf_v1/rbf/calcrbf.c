static char mc_version[] = "MATLAB Compiler 1.0 infun";
/*
 *  MATLAB Compiler: 1.0
 *  Date: Oct 20, 1995
 *  Arguments: calcrbf 
 */
#include <math.h>
#include "mex.h"
#include "mcc.h"

/* static array S0_ (1 x 17) text, line 33: 'argument mismatch' */
static double S0__r_[] =
{
         97,  114,  103,  117,  109,  101,  110,  116,
         32,  109,  105,  115,  109,   97,  116,   99,
        104,
};
static Matrix S0_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 17, S0__r_, 0, -1, 0, {0} };
/* static array S1_ (1 x 17) text, line 33: 'argument mismatch' */
static double S1__r_[] =
{
         97,  114,  103,  117,  109,  101,  110,  116,
         32,  109,  105,  115,  109,   97,  116,   99,
        104,
};
static Matrix S1_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 17, S1__r_, 0, -1, 0, {0} };

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
 *       CM0_        	complex vector/matrix temporary
 *       H           	complex vector/matrix
 *       R           	complex vector/matrix
 *       XData       	complex vector/matrix
 *       calcrbf     	<function being defined>
 *       designg     	<function>
 *       error       	<function>
 *       nargin      	<function>
 *       w           	complex vector/matrix
 *       y           	complex vector/matrix
 *******************************************************/
      Matrix y;
      Matrix C;
      Matrix R;
      Matrix w;
      Matrix XData;
      Matrix H;
      Matrix CM0_;
      
      mccComplexInit(C);
      mccImport(&C, ((nrhs_>0) ? prhs_[0] : 0), 0, 0);
      mccComplexInit(R);
      mccImport(&R, ((nrhs_>1) ? prhs_[1] : 0), 0, 0);
      mccComplexInit(w);
      mccImport(&w, ((nrhs_>2) ? prhs_[2] : 0), 0, 0);
      mccComplexInit(XData);
      mccImport(&XData, ((nrhs_>3) ? prhs_[3] : 0), 0, 0);
      mccComplexInit(y);
      mccComplexInit(H);
      mccComplexInit(CM0_);
      
      /* % Berechnet die Ausgabe eines RBF-Netzes bei gegebenen  */
      /* % Zentren, Breiten der Basisfunktionen in der ersten Schicht und gegebenen */
      /* % Gewichten in der zweiten Schicht */
      
      /* % y=calcrbf(C, R, w, x) */
      
      /* % Input */
      
      /* % C : Matrix der Zentren der Basisfunktionen (Indim-by-m: [c_1 c_2 ... c_m])  */
      /* % R : Radius (passed to design) */
      /* % w : Gewichte der zweiten Schicht (Outdim-by-m) */
      /* % x : Eingabevektoren (Indim-by-p: [x_1 x_2 ... x_p]) */
      
      /* % y=calcrbf(H, w) */
      
      /* % Input */
      
      /* % H : Designmatrix */
      /* % w : Gewichte der zweiten Schicht (Outdim-by-m) */
      
      /* % Output */
      /* % y : Berechneter Output */
      
      /* if nargin==4 */
      if ((mccNargin() == 4))
      {
         /* H=designg(XData,C,R) ; */
         if( XData.flags & mccNOTSET )
         {
            mexErrMsgTxt( "variable XData undefined, line 26" );
         }
         if( C.flags & mccNOTSET )
         {
            mexErrMsgTxt( "variable C undefined, line 26" );
         }
         if( R.flags & mccNOTSET )
         {
            mexErrMsgTxt( "variable R undefined, line 26" );
         }
         Mprhs_[0] = &XData;
         Mprhs_[1] = &C;
         Mprhs_[2] = &R;
         Mplhs_[0] = &H;
         mccCallMATLAB(1, Mplhs_, 3, Mprhs_, "designg", 26);
         
         /* y=(H*w)' ; */
         if( w.flags & mccNOTSET )
         {
            mexErrMsgTxt( "variable w undefined, line 28" );
         }
         mccMultiply(&CM0_, &H, &w);
         mccConjTrans(&y, &CM0_);
         /* elseif nargin==2 */
      }
      else
      {
         if ((mccNargin() == 2))
         {
            
            /* y=(C*R)' ;  */
            if( C.flags & mccNOTSET )
            {
               mexErrMsgTxt( "variable C undefined, line 31" );
            }
            if( R.flags & mccNOTSET )
            {
               mexErrMsgTxt( "variable R undefined, line 31" );
            }
            mccMultiply(&CM0_, &C, &R);
            mccConjTrans(&y, &CM0_);
            /* else */
         }
         else
         {
            /* error('argument mismatch') ; */
            mccError(&S0_);
            /* end ; */
         }
      }
      
      
      
      
      
      mccReturnFirstValue(&plhs_[0], &y);
   }
   else
   {
/***************** Compiler Assumptions ****************
 *
 *       C           	real vector/matrix
 *       H           	real vector/matrix
 *       R           	real vector/matrix
 *       RM0_        	real vector/matrix temporary
 *       XData       	real vector/matrix
 *       calcrbf     	<function being defined>
 *       designg     	<function>
 *       error       	<function>
 *       nargin      	<function>
 *       w           	real vector/matrix
 *       y           	real vector/matrix
 *******************************************************/
      Matrix y;
      Matrix C;
      Matrix R;
      Matrix w;
      Matrix XData;
      Matrix H;
      Matrix RM0_;
      
      mccRealInit(C);
      mccImport(&C, ((nrhs_>0) ? prhs_[0] : 0), 0, 0);
      mccRealInit(R);
      mccImport(&R, ((nrhs_>1) ? prhs_[1] : 0), 0, 0);
      mccRealInit(w);
      mccImport(&w, ((nrhs_>2) ? prhs_[2] : 0), 0, 0);
      mccRealInit(XData);
      mccImport(&XData, ((nrhs_>3) ? prhs_[3] : 0), 0, 0);
      mccRealInit(y);
      mccRealInit(H);
      mccRealInit(RM0_);
      
      /* % Berechnet die Ausgabe eines RBF-Netzes bei gegebenen  */
      /* % Zentren, Breiten der Basisfunktionen in der ersten Schicht und gegebenen */
      /* % Gewichten in der zweiten Schicht */
      
      /* % y=calcrbf(C, R, w, x) */
      
      /* % Input */
      
      /* % C : Matrix der Zentren der Basisfunktionen (Indim-by-m: [c_1 c_2 ... c_m])  */
      /* % R : Radius (passed to design) */
      /* % w : Gewichte der zweiten Schicht (Outdim-by-m) */
      /* % x : Eingabevektoren (Indim-by-p: [x_1 x_2 ... x_p]) */
      
      /* % y=calcrbf(H, w) */
      
      /* % Input */
      
      /* % H : Designmatrix */
      /* % w : Gewichte der zweiten Schicht (Outdim-by-m) */
      
      /* % Output */
      /* % y : Berechneter Output */
      
      /* if nargin==4 */
      if ((mccNargin() == 4))
      {
         /* H=designg(XData,C,R) ; */
         if( XData.flags & mccNOTSET )
         {
            mexErrMsgTxt( "variable XData undefined, line 26" );
         }
         if( C.flags & mccNOTSET )
         {
            mexErrMsgTxt( "variable C undefined, line 26" );
         }
         if( R.flags & mccNOTSET )
         {
            mexErrMsgTxt( "variable R undefined, line 26" );
         }
         Mprhs_[0] = &XData;
         Mprhs_[1] = &C;
         Mprhs_[2] = &R;
         Mplhs_[0] = &H;
         mccCallMATLAB(1, Mplhs_, 3, Mprhs_, "designg", 26);
         
         /* y=(H*w)' ; */
         if( w.flags & mccNOTSET )
         {
            mexErrMsgTxt( "variable w undefined, line 28" );
         }
         mccRealMatrixMultiply(&RM0_, &H, &w);
         mccConjTrans(&y, &RM0_);
         /* elseif nargin==2 */
      }
      else
      {
         if ((mccNargin() == 2))
         {
            
            /* y=(C*R)' ;  */
            if( C.flags & mccNOTSET )
            {
               mexErrMsgTxt( "variable C undefined, line 31" );
            }
            if( R.flags & mccNOTSET )
            {
               mexErrMsgTxt( "variable R undefined, line 31" );
            }
            mccRealMatrixMultiply(&RM0_, &C, &R);
            mccConjTrans(&y, &RM0_);
            /* else */
         }
         else
         {
            /* error('argument mismatch') ; */
            mccError(&S1_);
            /* end ; */
         }
      }
      
      
      
      
      
      mccReturnFirstValue(&plhs_[0], &y);
   }
   return;
}

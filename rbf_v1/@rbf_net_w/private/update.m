function update(rn, C, R, dataset)
% rbf_net_lscr_w_fast.update(rn, C, R[, dataset])
%
% global RBFNET_CG_TEMP_DATA ;

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

global RBFNET_CG_TEMP_DATA ;
%fprintf(1, '.') ;

MAX_UPDATE_COUNTER = 100 ;

% check for some sleeping conditions ...
check_stop ;

if nargin>3,
  data_w_verify(rn, dataset) ;
end ;

if (~equal(C,RBFNET_CG_TEMP_DATA.C) | ...
    (RBFNET_CG_TEMP_DATA.UpdateCounter>MAX_UPDATE_COUNTER)),
  RBFNET_CG_TEMP_DATA.UpdateCounter=0 ;
  RBFNET_CG_TEMP_DATA.Inp=0 ;
  RBFNET_CG_TEMP_DATA.H=0 ;
else
  if equal(R,RBFNET_CG_TEMP_DATA.R),
    return ;
  end ;
end ;

if nargin<4,
  [RBFNET_CG_TEMP_DATA.H, RBFNET_CG_TEMP_DATA.Inp]= ...
      design_rbf(get_train(rn,1), C, R) ;

  [RBFNET_CG_TEMP_DATA.w,f]= ls_solve_w(RBFNET_CG_TEMP_DATA.H, ...
      get_train(rn,2)', get_distr(rn)', get_lambda(rn)) ;
else
  [RBFNET_CG_TEMP_DATA.H, RBFNET_CG_TEMP_DATA.Inp]= ...
      design_rbf(get_train(dataset,1), C, R) ;

  [RBFNET_CG_TEMP_DATA.w,f]= ls_solve_w(RBFNET_CG_TEMP_DATA.H, ...
      get_train(dataset,2)', get_distr(rn)', get_lambda(rn)) ;
end ;
if f>0,
%  disp('  In order to solve the linear system resulting from the ls-optimization')
  disp([' The regularization constant was increased to \lambda=' num2str(f)]) ;
end ;

RBFNET_CG_TEMP_DATA.train_out=(RBFNET_CG_TEMP_DATA.H*RBFNET_CG_TEMP_DATA.w)' ;
RBFNET_CG_TEMP_DATA.R=R ;
RBFNET_CG_TEMP_DATA.C=C ;

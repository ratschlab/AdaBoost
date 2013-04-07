function [rn,w]=calc_weigths(rn, dataset)
% [rn,w]=rbf_net_lsrc_w_fast.calc_weigths(rn, dataset)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

dataset=data_w(dataset) ;
  
[H, Inp]= design_rbf(get_train(dataset, 1), get_C(rn), get_R(rn)) ;

rn=set_idim(rn, get_idim(dataset)) ;
[w,f]=ls_solve_w(H, get_train(dataset,2)', ...
    get_sampl_weights(dataset)', get_lambda(rn)) ;
if f>0,
%  disp('  In order to solve the linear system resulting from the ls-optimization')
  disp([' The regularization constant was increased to \lambda=' num2str(f)]) ;
end ;
  
rn=set_w(rn, w) ;

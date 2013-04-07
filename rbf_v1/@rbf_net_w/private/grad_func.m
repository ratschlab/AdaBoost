function [gradient]=grad_func(rn, point)
% [gradient]=grad_func(rn, point)
%
% global RBFNET_CG_TEMP_DATA ;

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

global RBFNET_CG_TEMP_DATA ;

[C,R]=rbfp2m(point, get_num_cen(rn)) ;
update(rn, C, R) ;

R(find(R==0))=1e-100 ;
h1_sigma_sigma=ones(size(R)) ;
h2_sigma_sigma=R.^2 ;
dif_h2_h2=2./R ;
dif_h1_h1=zeros(size(R)) ;

[C_mu, C_sigma]=rbfgrad_w(get_train(rn, 1), get_train(rn,2), ...
    RBFNET_CG_TEMP_DATA.train_out, C, R, RBFNET_CG_TEMP_DATA.w, ...
    RBFNET_CG_TEMP_DATA.H, RBFNET_CG_TEMP_DATA.Inp, ...
    get_distr(rn), h1_sigma_sigma, h2_sigma_sigma, dif_h1_h1, dif_h2_h2) ;

gradient=rbfm2p(C_mu, C_sigma) ;
gradient=gradient(:) ;

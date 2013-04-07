function [err]=err_func(rn, point)
% [err]=rbf_net_ls.err_func(rn, point)
%
% global RBFNET_CG_TEMP_DATA

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

global RBFNET_CG_TEMP_DATA

[C,R]=rbfp2m(point, get_num_cen(rn)) ;
update(rn, C, R) ;

Distr=get_distr(rn) ;

err = mse_w(RBFNET_CG_TEMP_DATA.train_out, get_train(rn,2), Distr) + ...
        get_lambda(rn)*sum(Distr)* ...
            sum(sum(RBFNET_CG_TEMP_DATA.w .* RBFNET_CG_TEMP_DATA.w)) ;

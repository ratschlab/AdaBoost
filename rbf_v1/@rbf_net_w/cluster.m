function [rn]=cluster(rn, dataset)
% [rn]=cluster(rn, dataset)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

dataset=data_w(dataset) ;

[C, R]=clustknb_new_w(get_train(dataset), get_num_cen(rn), ...
    get_sampl_weights(dataset), 0) ;

rn=set_C(rn, C) ;
rn=set_R(rn, R) ;
function [rn, old_lambda]=set_lambda(rn, new_lambda) 
% [rn, old_lambda]=set_lambda(rn, new_lambda) 

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

old_lambda=rn.lambda ;
rn.lambda=new_lambda ;
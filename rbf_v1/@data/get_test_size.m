function [num_pat]=get_test_size(da)
% [num_pat]=get_test_size(da)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

num_pat=size(da.test_pat,2) ;
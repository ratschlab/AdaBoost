function [test_pat, test_targ]=get_test(da, order)
% [test_pat, test_labels]=get_test(da, order)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

if nargin==1,
	test_pat=da.test_pat ;
	test_targ=da.test_targ ;
else
	if order==2,
		test_pat=da.test_targ ;
	elseif order==1,
		test_pat=da.test_pat ;
	end ;
end ;

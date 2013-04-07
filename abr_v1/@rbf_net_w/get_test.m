function [test_pat, test_targ]=get_test(co, order)
% [test_pat, test_targ]=cg_optimizable.get_test(co, order)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

if nargin==1,
	[test_pat, test_targ]=get_test(co.param) ;
else
	if order==2,
		test_pat=get_test(co.param,2) ;
	elseif order==1,
		test_pat=get_test(co.param,1) ;
	end ;
end ;

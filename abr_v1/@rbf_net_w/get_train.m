function [train_pat, train_targ]=get_train(co, order)
% [train_pat, train_targ]=cg_optimizable.get_train(co, order)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

if nargin==1,
	[train_pat, train_targ]=get_train(co.param) ;
else
	if order==2,
		train_pat=get_train(co.param,2) ;
	elseif order==1,
		train_pat=get_train(co.param,1) ;
	end ;
end ;

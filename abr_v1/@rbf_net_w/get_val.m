function [val_pat, val_targ]=get_val(co, order)
% [val_pat, val_targ]=cg_optimizable.get_val(co, order)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

if nargin==1,
	[val_pat, val_targ]=get_val(co.param) ;
else
	if order==2,
		val_pat=get_val(co.param,2) ;
	elseif order==1,
		val_pat=get_val(co.param,1) ;
	end ;
end ;

function [val_pat, val_targ]=get_val(da, order)
% [val_pat, val_labels]=get_val(da, order)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

if nargin==1,
	val_pat=da.val_pat ;
	val_targ=da.val_targ ;
else
	if order==2,
		val_pat=da.val_targ ;
	elseif order==1,
		val_pat=da.val_pat ;
	end ;
end ;
	
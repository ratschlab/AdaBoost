function [train_pat, train_targ]=get_train(da, order)
% [train_pat, train_labels]=data.get_train(da, order)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

if nargin==1,
	train_pat=da.train_pat ;
	train_targ=da.train_targ ;
else
	if order==2,
		train_pat=da.train_targ ;
	elseif order==1,
		train_pat=da.train_pat ;
	end ;
end ;
	
function [da]=split_train(da, test_set, val_set)
% [da]=split_train(test_set, val_set)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

if ~consistent(da)
	error('data is not consistent') ;
end ;

if nargin<3,
	val_set=0 ;
end ;

if (size(da.test_pat,2)~=0) & (test_set~=0),
	error('it has already a test set') ;
end ;
if (size(da.val_pat,2)~=0) & (val_set~=0),
	error('it has already a validation set') ;
end ;

if test_set~=0,
	da.test_pat= da.train_pat(:, 1:test_set) ;
	da.test_targ=da.train_targ(:, 1:test_set) ;
	da.test_permutated=da.train_permutated ;
end ;
if val_set~=0,
	da.val_pat= da.train_pat(:, test_set+1:test_set+val_set) ;
	da.val_targ=da.train_targ(:, test_set+1:test_set+val_set) ;
	da.val_permutated=da.train_permutated ;
end ;

if (val_set~=0) | (test_set~=0)
	da.train_pat= da.train_pat(:, test_set+val_set+1:size(da.train_pat,2)) ;
	da.train_targ=da.train_targ(:, test_set+val_set+1:size(da.train_targ,2)) ;
end ;

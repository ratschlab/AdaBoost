function da=data(train_pat, train_targ, test_pat, test_targ, val_pat, val_targ, name)
% Constructor for the data class
%
% da=data(train_pat, train_targ, test_pat, test_targ, val_pat, val_targ)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

if nargin==1,
	if isa(train_pat, 'data')
		da=train_pat ;
		return ;
	end ;
	if isa(train_pat, 'char')
		if ~exist(train_pat)
			error('file not found.')
		end ;

		% patterns
		load(train_pat) ;
		if exist('train_patterns')
			da.train_pat=train_patterns ;
		elseif exist('XT')
			da.train_pat=XT ;
		elseif exist('patterns')
			da.train_pat=patterns ;
		else
			da.train_pat=[] ;
		end ;
		if exist('train_targets')
			da.train_targ=train_targets ;
		elseif exist('train_labels')
			da.train_targ=train_labels ;
		elseif exist('outputsT')
			da.train_targ=outputsT ;
		elseif exist('labels')
			da.train_targ=labels ;
		else
			da.train_targ=[] ;
		end ;
		if exist('test_patterns')
			da.test_pat=test_patterns ;
		elseif exist('XTE')
			da.test_pat=XTE ;
		else
			da.test_pat=[] ;
		end ;
		if exist('test_targets')
			da.test_targ=test_targets ;
		elseif exist('test_labels')
			da.test_targ=test_labels ;
		elseif exist('outputsTE')
			da.test_targ=outputsTE ;
		else
			da.test_targ=[] ;
		end ;
		if exist('val_patterns')
			da.val_pat=val_patterns ;
		elseif exist('XV')
			da.val_pat=XV ;
		else
			da.val_pat=[] ;
		end ;
		if exist('val_targets')
			da.val_targ=val_targets ;
		elseif exist('val_labels')
			da.val_targ=val_labels ;
		elseif exist('outputsV')
			da.val_targ=outputsV ;
		else
			da.val_targ=[] ;
		end ;
		
		% dataset name
		da.name = train_pat ;

		% standardization
		da.std_1=0 ;
		da.mean_0=0 ;
		da.m_train_pat=[] ;
		da.st_train_pat=[] ;
		if exist('m_XT')
			da.mean_0=1 ;
			da.m_train_pat=m_XT ;
		end ;
		if exist('st_XT') 
			da.std_1=1 ;
			da.st_train_pat=st_XT ;
		end ;

		% permutation
		da.train_permutated=0 ;
		da.test_permutated=0 ;
		da.val_permutated=0 ;
		da.train_permutated_idx=[] ;
		da.test_permutated_idx=[] ;
		da.val_permutated_idx=[] ;

		da.sname = 'none' ;

		da=class(da, 'data') ;
		return ;
	end ;	
end ;

% default values
if nargin==0,
	train_pat=[] ;
	train_targ=[] ;
end ;
if nargin<=2,
	test_pat=[] ;
	val_pat=[] ;
	test_targ=[] ;
	val_targ=[] ;
end ;
if nargin<=4,
	val_pat=[] ;
	val_targ=[] ;
end ;

% patterns
da.train_pat=train_pat ;
da.train_targ=train_targ ;
da.test_pat=test_pat ;
da.test_targ=test_targ ;
da.val_pat=val_pat ;
da.val_targ=val_targ ;

% dataset name
if nargin<7
	da.name = '' ;
else
	da.name = name ;
end ;

% standardization
da.std_1=0 ;
da.mean_0=0 ;
da.m_train_pat=[] ;
da.st_train_pat=[] ;

% permutation
da.train_permutated=0 ;
da.test_permutated=0 ;
da.val_permutated=0 ;
da.train_permutated_idx=[] ;
da.test_permutated_idx=[] ;
da.val_permutated_idx=[] ;

da.sname = 'none' ;

da=class(da, 'data') ;

%da=check_std(da) ;

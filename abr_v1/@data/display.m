function display(da)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

disp('data object') ;
if length(da.name)~=0,
	disp(sprintf('the name is: %s', da.name)) ;
end ;
disp(sprintf('the sname is : %s', da.sname)) ;
disp(sprintf('the nsname is: %s', get_nsname(da))) ;

disp(sprintf('  number of train patterns     : %i', size(da.train_pat,2))) ;
disp(sprintf('  number of test patterns      : %i', size(da.test_pat,2))) ;
disp(sprintf('  number of validation patterns: %i', size(da.val_pat,2))) ;
disp(sprintf('  input dimension      : %i', size(da.train_pat,1))) ;
disp(sprintf('  output dimension     : %i', size(da.train_targ,1))) ;

if ~consistent(da)
	disp(sprintf('  number of train targets     : %i', size(da.train_targ,2))) ;
	disp(sprintf('  number of test targets      : %i', size(da.test_targ,2))) ;
	disp(sprintf('  number of validation targets: %i', size(da.val_targ,2))) ;
end ;

if da.mean_0
	disp('training data has zero mean') ;
else
	disp('training data has not zero mean') ;
end ;
if da.std_1
	disp('training data has standard deviation one') ;
else
	disp('training data has not standard deviation one') ;
end ;

if da.train_permutated,
	disp('training data is permutated.') ;
end ;
if da.test_permutated,
	disp('test data is permutated.') ;
end ;
if da.val_permutated,
	disp('validation data is permutated.') ;
end ;

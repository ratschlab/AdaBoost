function [output_data]=get_output(lrn, in_data)
% [output_data]=learner.get_output(lrn, in_data)
% 
% parameter 	      	class
% -----------------------------
% lrn		- 	learner 
% in_data	-	data 
% output_data	-	data


%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Training Output
if get_train_size(in_data)>0,
	trOut= calc_output(lrn, get_train(in_data,1)) ;
else
	trOut=[] ;
end ;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Val Output
if get_val_size(in_data)>0,
	vOut=calc_output(lrn, get_val(in_data,1)) ;
else 
	vOut=[] ;
end 


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Test Output
if get_test_size(in_data)>0,
	tOut=calc_output(lrn, get_test(in_data,1)) ;
else	
	tOut=[] ;
end ;

output_data = data([], trOut, [], tOut, [], vOut) ;

function [trErrs, tstErrs, valErrs]=mse_mse(rn, data)
% [trErrs, tstErrs, valErrs]=learner.get_mse(rn, data)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

cls=size(get_train(data,2),1) ;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Training Error
if get_train_size(data)>0,
	trOut=calc_output(rn, get_train(data,1)) ;
	trErrs=mse(trOut, get_train(data,2)) ;
else
	trErrs=-1 ;
end ;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Val Error
if get_val_size(data)>0
	vOut=calc_output(rn, get_val(data,1)) ;
	valErrs=mse(vOut, get_val(data,2)) ;
else 
	valErrs=-1 ;
end 


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Test Error
if get_test_size(data)>0
	tOut=calc_output(rn, get_test(data,1)) ;
	tstErrs=mse(tOut, get_test(data,2)) ;
else	
	tstErrs=-1 ;
end ;



function [trErrs, tstErrs, valErrs]=get_class_errors(rn, data)
% [trErrs, tstErrs, valErrs]=learner.get_class_errors(rn, data)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

cls=size(get_train(data,2),1) ;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Training Error
if get_train_size(data)>0,
	trOut=calc_output(rn, get_train(data,1)) ;
	if cls>1,
		[temp, trOutL]=max(trOut) ;
		[temp, trainL]=max(get_train(data,2)) ;
		trErrs=sum(trOutL~=trainL)/get_train_size(data) ;
	else
		trErrs=sum(sign(trOut)~=get_train(data,2))/get_train_size(data) ;
	end ;
else
	trErrs=-1 ;
end ;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Val Error
if (get_val_size(data)>0) & (nargout>2),
	vOut=calc_output(rn, get_val(data,1)) ;
	if cls>1,
		[temp, vOutL]=max(vOut) ;
		[temp, valL]=max(get_val(data,2)) ;
		valErrs=sum(vOutL~=valL)/get_val_size(data) ;
	else
		valErrs=sum(sign(vOut)~=get_val(data,2))/get_val_size(data) ;
	end ;
else 
	valErrs=-1 ;
end 


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Test Error
if (get_test_size(data)>0) & (nargout>1),
	tOut=calc_output(rn, get_test(data,1)) ;
	if cls>1,
		[temp, tOutL]=max(tOut) ;
		[temp, testL]=max(get_test(data,2)) ;
		tstErrs=sum(tOutL~=testL)/get_test_size(data) ;
	else
		tstErrs=sum(sign(tOut)~=get_test(data,2))/get_test_size(data) ;
	end ;
else	
	tstErrs=-1 ;
end ;


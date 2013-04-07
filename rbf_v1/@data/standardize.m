function da=standardize(da) ;
% da=standardize(da) ;
%
% standardizes the train, validation and test patterns to mean=0 and std=1

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

if ~consistent(da)
	error('data is not consistent') ;
end ;

if (da.std_1==0) & (da.mean_0==0),

	da.st_train_pat= std(da.train_pat');
	da.m_train_pat=  mean(da.train_pat');

	for i=1:size(da.train_pat,1),
	  da.train_pat(i,:) = (da.train_pat(i,:) - da.m_train_pat(i))/da.st_train_pat(i);
	end

	for i=1:size(da.test_pat,1),
	 da.test_pat(i,:) = (da.test_pat(i,:) - da.m_train_pat(i))/da.st_train_pat(i);
	end

	for i=1:size(da.val_pat,1),
	 da.val_pat(i,:) = (da.val_pat(i,:) - da.m_train_pat(i))/da.st_train_pat(i);
	end
	da.name=['std=1 and mean=0 of ' da.name] ;

elseif (da.std_1==0),
	da.st_train_pat= std(da.train_pat');

	for i=1:size(da.train_pat,1),
	  da.train_pat(i,:) = da.train_pat(i,:)/da.st_train_pat(i);
	end

	for i=1:size(da.test_pat,1),
	 da.test_pat(i,:) = da.test_pat(i,:)/da.st_train_pat(i);
	end

	for i=1:size(da.val_pat,1),
	 da.val_pat(i,:) = da.val_pat(i,:)/da.st_train_pat(i);
	end
	da.name=['std=1 of ' da.name] ;

elseif (da.mean_0==0),
	da.m_train_pat=  mean(da.train_pat');

	for i=1:size(da.train_pat,1),
	  da.train_pat(i,:) = da.train_pat(i,:) - da.m_train_pat(i);
	end

	for i=1:size(da.test_pat,1),
	 da.test_pat(i,:) = da.test_pat(i,:) - da.m_train_pat(i);
	end

	for i=1:size(da.val_pat,1),
	 da.val_pat(i,:) = da.val_pat(i,:) - da.m_train_pat(i);
	end
	da.name=['mean=0 of ' da.name] ;

end ;

da.std_1=1 ;
da.mean_0=1 ;


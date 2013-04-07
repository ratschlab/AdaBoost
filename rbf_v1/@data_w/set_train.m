function da=set_train(da, train_pat, train_targ)
% da=set_train(da, train_pat, train_targ)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

da.data=set_train(da.data, train_pat, train_targ) ;

if get_train_size(da)~=length(da.sampl_weights)
  warning('inconsistence between data and weights. reinitialize weights.') ;
  if (get_train_size(da)>0),
    da.sampl_weights=1/get_train_size(da)*ones(1, get_train_size(da)) ;
  else
    da.sampl_weights=zeros(1, get_train_size(da)) ;
  end ;
end ;	


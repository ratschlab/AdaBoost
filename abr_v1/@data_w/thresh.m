function dataset=thresh(dataset) ;
% new_dataset=thresh(dataset) ;

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

l=get_train_size(dataset) ;
dataset.sampl_weights=dataset.sampl_weights/sum(dataset.sampl_weights) ;
idx=find( dataset.sampl_weights > (dataset.theta/l) ) ;
theta=dataset.theta/l ;
it=1 ;
while (it<10) & ...
      (length(idx)<min(get_min_patterns(dataset), get_train_size(dataset))),
   theta=theta/1.2 
   idx=find( dataset.sampl_weights > theta ) ;
   it=it+1 ;
end ;
[train_pat, train_targ]=get_train(dataset) ;
assert(size(train_targ,1)==1) ;
dataset=set_sampl_weights(dataset, dataset.sampl_weights(idx)) ;
dataset=set_train(dataset, train_pat(:, idx), train_targ(idx)) ;

%deb_output(sprintf('\n data fraction: %1.2f\n', get_train_size(dataset)/l)) ;

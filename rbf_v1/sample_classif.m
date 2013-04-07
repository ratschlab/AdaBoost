%   G. Raetsch 15.2.99
%
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%
% for terms of usage see COPYRIGHTS.TXT
%
% example for a classification task

num_train=50 ;
num_test=300 ;

X=randn(2,num_train+num_test) ;
Y=((X(1,:).^2+X(2,:).^2)<1)-((X(1,:).^2+X(2,:).^2)>=1) ;

% splitting: training and test data
idx=randperm(num_train+num_test) ;
XT=X(:,idx(1:num_train)) ;
YT=Y(1,idx(1:num_train)) ; 
XTE=X(:,idx(num_train+1:num_train+num_test)) ;
YTE=Y(1,idx(num_train+1:num_train+num_test)) ;

% create object 'data'
dataset=data(XT, YT, XTE, YTE) ;
dataset 

% create rbf net with 3 centers, regularization 1e-4, 
%                                input dimension = two
%                                output dimension = one
rn=rbf_net_w(3, 1e-4, 2, 1) ;

% set the number of iterations for the optimization
rn=set_max_iter(rn, 10) ;

% train rbf net -- the third parameter means, that the centers are
% initialized with k-means clustering (almost always very useful!)
rn=do_learn(rn, dataset, 1) ;

figure(1) ; clf ;

% plotting computed data for the training set
outT=sign(calc_output(rn, get_train(dataset,1))) ;
plot(XT(1,find(outT==1)), XT(2,find(outT==1)), 'r+') ;
hold on
plot(XT(1,find(outT==-1)), XT(2,find(outT==-1)), 'b+') ;

% plotting the difference to the original training labels
plot(XT(1,find(YT==1 & outT==-1)), XT(2,find(YT==1 & outT==-1)), 'ro') ;
plot(XT(1,find(YT==-1 & outT==1)), XT(2,find(YT==-1 & outT==1)), 'bo') ;

% compute classification error on training and test set
[trc,tec]=get_class_errors(rn, dataset) 








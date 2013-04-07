%   G. Raetsch 15.2.99
%
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%
% for terms of usage see COPYRIGHTS.TXT
%
% example for a regression task

num_train=150 ;
num_test=300 ;
noise=0.1 ;

X=3*rand(1,num_train+num_test) ;
Y=sin(X(1,:).^2).*cos(X(1,:).^2)-0.3*X(1,:) ;

% splitting: training and test data
idx=randperm(num_train+num_test) ;
XT=X(1,idx(1:num_train)) ;
YT=Y(1,idx(1:num_train)) + noise*randn(1,num_train) ;
XTE=X(1,idx(num_train+1:num_train+num_test)) ;
YTE=Y(1,idx(num_train+1:num_train+num_test)) ;

% sorting testdaten 
[XTE, idx]=sort(XTE) ;
YTE=YTE(1,idx);


% create object 'data'
dataset=data(XT, YT, XTE, YTE) ;
dataset 

% create rbf net with 12 centers, regularization 1e-4, 
%                                input and output dimension = one
rn=rbf_net_w(12, 1e-4, 1, 1) ;

% set the number of iterations for the optimization
rn=set_max_iter(rn, 5) ;

% train rbf net -- the third parameter means, that the centers are
% initialized with k-means clustering (almost always very useful!)
rn=do_learn(rn, dataset, 1) ;

figure(1) ; clf ;

% plotting computed data for the training set
outT=calc_output(rn, get_train(dataset,1)) ;
plot(get_train(dataset,1), outT, 'r*') ;
hold on 

% plotting original training labels
plot(get_train(dataset,1), get_train(dataset,2), 'b.') ;

% plotting computed data for test set
outTE=calc_output(rn, get_test(dataset,1)) ;
plot(get_test(dataset,1), outTE, 'r-') ;

% plotting original test labels
plot(get_test(dataset,1), get_test(dataset,2), 'g-') ;


% compute Mean Squared Error on training and test set
[trm,tem]=get_mse(rn, dataset) 





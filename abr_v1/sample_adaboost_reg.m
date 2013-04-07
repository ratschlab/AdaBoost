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

num_train=70 ;
num_test=1000 ;
lnoise=0.1 ;  % amount of label noise in the data

X=randn(2,num_train+num_test) ;
Y=((X(1,:).^2+X(2,:).^2)<1)-((X(1,:).^2+X(2,:).^2)>=1) ;

% splitting: training and test data
idx=randperm(num_train+num_test) ;
XT=X(:,idx(1:num_train)) ;
YT=Y(1,idx(1:num_train)) ; 
XTE=X(:,idx(num_train+1:num_train+num_test)) ;
YTE=Y(1,idx(num_train+1:num_train+num_test)) ;

% 'add' some label noise
YT(1:floor(lnoise*num_train))=-YT(1:floor(lnoise*num_train)) ;

% create object 'data'
dataset=data(XT, YT, XTE, YTE) ;
dataset 

% create a plain rbf net with 10 centers, regularization 1e-4, 
%                                input dimension = two
%                                output dimension = one
rn=rbf_net_w(10, 1e-4, 2, 1) ;
rn=set_max_iter(rn, 0) ;

% create an adaboost object which uses rn as base learner
% 200 iterations, 
% '1' is a parameter that is passed to rn while calling do_learn of rn
bb=adabooster(rn, 200, 1) ;

% use signum function to ensure h_t(x) |-> [-1,1]
bb=set_use_sign_output(bb,1) ;

% start learning
bb=do_learn(bb, dataset) ;

% compute training and test errors after each iteration
cles=get_class_errors_step(bb, dataset) ;

% create an adaboost-reg object which uses rn as base learner
% 200 iterations, phi=1/2, C=100,
% '1' is a parameter that is passed to rn while calling do_learn of rn
bb_reg=adabooster_regul(rn, 200, 1/2, 1000, 1) ;

% use signum function to ensure h_t(x) |-> [-1,1]
bb_reg=set_use_sign_output(bb_reg,1) ;

% start learning
bb_reg=do_learn(bb_reg, dataset) ;

% compute training and errors after each iteration
cles_reg=get_class_errors_step(bb_reg, dataset) ;

% make some plot
figure(1) ; clf ;
subplot(1,2,1) ;
plot(cles(1:2,:)')
subplot(1,2,2) ;
plot(cles_reg(1:2,:)')




function [C,R]=clustknb_new_w(XData, k, Weights, disp, mus) 
%[C,R,real_k,it]=clustknb_new(XData, k, Weights, mus=random_data_subset)
%
% 'online version' of the k-means-nearest-neighbourhood algorithm
% 
% [C,R,real_k,it]=clustknb_new(XData, k, Weights)
%
% Input
%		XData		: Input data 
%		k		: number of centres
%               Weights         : Sample Weights
%		mus		: [opt] initialization of the centers
%
% Output
%		C : Matrix with bf-centres (Indim-by-m: [c_1 c_2 ... c_m]) 
%		R : bf-width

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

error('compile clustknb_new_w.c') ;

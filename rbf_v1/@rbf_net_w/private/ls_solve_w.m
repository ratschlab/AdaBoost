function [x,f]=ls_solve_w(A, b, eta, lambda)
% [x,f]=ls_solve_w(A, b, eta, lambda)
% 
% solves a weighted Least Squares problem with regularization

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

error('compile ls_solve_w.c')
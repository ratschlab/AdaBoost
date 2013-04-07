function [H, Inp] = design_rbf(X, C, R)
% [H, Inp] = design_rbf(X, C, R)
%
% Gets the design matrix from the input data, centre positions
% and radii factors.
%
% Input
%       X       Input training data (n-by-p)
%       C       List of centres (n-by-m)
%       R       Scale factors: scalar, n-vector, or n-by-n matrix
%
% Output
%       H       Design matrix (p-by-m)
%       Inp     p-by-m Matrix of the Norms ... (only for R=nvector)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

error('compile design_rbf.c') ;


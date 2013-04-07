function [C_mu, C_sigma]=rbfgrad_w(X, Y, O, mu, sigma, w, H, Inp, eta, h1_sigma_sigma, h2_sigma_sigma, dif_h1_h1, dif_h2_h2)
% [C_mu, C_sigma]=cen_wid_gradient(X, Y, O, mu, sigma, w, H, Inp, ...
% eta, h1_sigma_sigma, h2_sigma_sigma, dif_h1_h1, dif_h2_h2)
% 
% computes the gradients for C and R of a rbf net

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

error('compile rbfgrad_w.c') ;
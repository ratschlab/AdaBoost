function y=calc_output(rn, XData, w, R, C)
% y=rbf_net_ls.calc_output(rn, XData[, w[, R[, C]]])
% 
% Berechnet die Ausgabe eines RBF-Netzes (LS) bei gegebenen 
% Zentren, Breiten der Basisfunktionen in der ersten Schicht und gegebenen
% Gewichten in der zweiten Schicht
%
% parameter            class
% rn                   rbf_net_ls        Eingabevektoren (Indim-by-p)
% XData                double matrix
% w                    double matrix
% R                    double vector
% C                    double matrix
% y                    double matrix     Ausgabevektoren (Outdim-by-p)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

if nargin==5,
	H=design_rbf(XData, C, R) ;
	y=(H*w)' ;
elseif nargin==4,
	H=design_rbf(XData, get_C(rn), R) ;
	y=(H*w)' ;
elseif nargin==3,
	H=design_rbf(XData, get_C(rn), get_R(rn)) ;
	y=(H*w)' ;
elseif nargin==2
	H=design_rbf(XData, get_C(rn), get_R(rn)) ;
	y=(H*get_w(rn))' ;
end ;
	





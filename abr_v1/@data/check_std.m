function [da, b]=check_std(da) ;
% [da, b]=check_std(da) ;
%
% checks for mean=0 and std=1 and sets the flags

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.
 
st_XT= std(da.train_pat') ;
m_XT=  mean(da.train_pat') ;

da.std_1=all( (abs(st_XT-1)<1e-8) ) ;
da.mean_0=all( (m_XT<1e-8) ) ;

b=da.std_1 & da.mean_0 ;

function mk_tempdata(rn)
% rbf_net_lscr.mk_tempdata(rn)
%
% global RBFNET_CG_TEMP_DATA ;

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

global RBFNET_CG_TEMP_DATA ;

RBFNET_CG_TEMP_DATA.H = 0 ;
RBFNET_CG_TEMP_DATA.Inp = 0 ;
RBFNET_CG_TEMP_DATA.w = 0 ;
RBFNET_CG_TEMP_DATA.train_out=0 ;

RBFNET_CG_TEMP_DATA.R = 0 ;
RBFNET_CG_TEMP_DATA.C = 0 ;
RBFNET_CG_TEMP_DATA.UpdateCounter = 0 ;

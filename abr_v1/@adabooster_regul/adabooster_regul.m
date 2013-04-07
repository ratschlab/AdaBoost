function bb=adabooster_regul(proto, boost_steps, phi, lambda, param1, param2)
% bob=adabooster_regul(proto, boost_steps, phi, lambda, param1, param2)
%
% Constructor for adabooster_regul class
%
% BASECLASS(ES) : adabooster

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

bb.phi=1/2 ;
bb.lambda=0 ;
bb.vi=0 ;

if nargin==0,
  bb=class(bb, 'adabooster_regul', adabooster) ;
elseif (nargin==1) & (isa(proto, 'adabooster_regul')),
  bb=proto ;
  return ;
elseif (nargin==1) & (isa(proto, 'struct')),
  bb=class(bb, 'adabooster_regul', adabooster) ;
  bb.adabooster=proto.adabooster ;
  bb.vi=proto.vi ;
  bb.phi=proto.phi ;
  bb.lambda=proto.lambda ;  
  return ;
elseif nargin==1,
  bb=class(bb, 'adabooster_regul', adabooster(proto)) ;
elseif nargin==2,
  bb=class(bb, 'adabooster_regul', adabooster(proto, boost_steps)) ;
elseif nargin==3,
  bb.phi=phi ;
  bb=class(bb, 'adabooster_regul', adabooster(proto, boost_steps)) ;
elseif nargin==4,
  bb.phi=phi ;
  bb.lambda=lambda ;
  bb=class(bb, 'adabooster_regul', adabooster(proto, boost_steps)) ;
elseif nargin==5, 
  bb.phi=phi ;
  bb.lambda=lambda ;
  bb=class(bb, 'adabooster_regul', adabooster(proto, boost_steps, param1)) ;
elseif nargin==6,
  bb.phi=phi ;
  bb.lambda=lambda ;
  bb=class(bb, 'adabooster_regul', adabooster(proto, boost_steps, param1, param2)) ;
end ;  
bb=set_use_sign_output(bb,1) ;


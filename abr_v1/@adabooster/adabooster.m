function bb=adabooster(proto, boost_steps, param1, param2)
% bob=booster_base(proto, boost_steps, param1, param2)
%
% Constructor for aqabooster class
%
% BASECLASS(ES) : booster_base

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

bb.use_sign_output=1 ;
bb.last_distr=[] ;
bb.last_output=[] ;
bb.fin_hyp=[] ;

if nargin==0,
  bb=class(bb, 'adabooster', booster_base) ;
elseif (nargin==1) & (isa(proto, 'adabooster')),
  bb=downcast(proto, 'adabooster') ;
  return ;
elseif nargin==1,
  bb=class(bb, 'adabooster', booster_base(proto)) ;
elseif nargin==2,
  bb=class(bb, 'adabooster', booster_base(proto, boost_steps)) ;
elseif nargin==3,
  bb=class(bb, 'adabooster', booster_base(proto, boost_steps, param1)) ;
elseif nargin==4,
  bb=class(bb, 'adabooster', booster_base(proto, boost_steps, param1, param2)) ;
end ;  

if get_odim(get_proto(bb))>1,
  error('this class supports only two classes and the output-dimension must be one') ;
end ;

function bob=booster_base(proto, boost_steps, param1, param2)
% bob=booster_base(proto, boost_steps)
%
% Constructor for booster_base class
%
% BASECLASS(ES) : learner

% Copyright (c) 1998  GMD Berlin - All rights reserved
% THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
% The copyright notice above does not evidence any
% actual or intended publication of this work.

if nargin==0,
  proto=learner ;
  boost_steps=10 ;
  %deb_output(sprintf('the number of boosting steps was set to %i.', boost_steps)) ;
  param2=[] ;
  param1=[] ;
  num_param=0 ;
elseif (nargin==1) & (isa(proto, 'booster_base')),
  bob=proto ;
  return ;
elseif nargin==1,
  boost_steps=10 ;
  deb_output(sprintf('the number of boosting steps was set to %i.', boost_steps)) ;
elseif nargin==2,
  param2=[] ;
  param1=[] ;
  num_param=0 ;
elseif nargin==3,
  param2=[] ;
  num_param=1 ;
else
  num_param=2 ;
end ;  

bob.proto=proto ;
bob.boost_steps=boost_steps ;
bob.boosted_learners=cell(1,boost_steps) ;
bob.vote_weights=zeros(1, boost_steps) ;
bob.num_param=num_param ;
bob.param1=param1 ;
bob.param2=param2 ;  

bob=class(bob, 'booster_base', learner(get_idim(proto), get_odim(proto))) ;


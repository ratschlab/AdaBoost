function daw=data_w(set, theta, sampl_weights)
% daw=data_w(set, theta, sampl_weights)
% 
% Constructor for the data_w class
%
% da=data(set)
% da=data(set, theta)
% da=data(set, theta, sampl_weights)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

if (nargin==1)
   if isa(set, 'data_w'),
      daw=set ;
      return ;
   end ;
elseif nargin==0,
   set=data ;   
end ;

if (nargin<3)
  if (get_train_size(set)>0),
    sampl_weights=1/get_train_size(set)*ones(1, get_train_size(set)) ;
  else
    sampl_weights=zeros(1, get_train_size(set)) ;
  end ;
end ;

if nargin<2,
  theta=0 ;
end ;

daw.sampl_weights=sampl_weights ;
daw.theta=theta ;
daw=class(daw, 'data_w', set) ;


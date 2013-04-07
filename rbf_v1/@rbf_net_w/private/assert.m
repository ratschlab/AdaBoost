function assert(Val, Text)
%
% checks a condition and aborts if it has been failed (Val==0)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

global debug_assert ;

%dbstack ;
if isempty(debug_assert),
  debug_assert=1 ;
elseif debug_assert==0,
  return ;
end ;

if ~Val,
	if nargin<2,
		rep=sprintf('assertion failed (%i)', Val) ;
	else
		rep=Text ;
	end ;
	dbstack ;
	error(rep) 
end ;

function da=set_test(da, test_pat, test_targ)
% da=set_test(da, test_pat, test_targ)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

if nargin==2,
  da.test_pat=test_pat ;
elseif nargin==3
  da.test_targ=test_targ ;
  da.test_pat=test_pat ;
end ;

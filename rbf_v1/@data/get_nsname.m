function sname=get_nsname(da) ;
% nsname=get_nsname(da) ;

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

trsize=size(da.train_pat,2) ;
valsize=size(da.val_pat,2) ;
testsize=size(da.test_pat,2) ;

if trsize>10000,
  trsize=trsize/1000 ;
  valsize=valsize/1000 ;
  testsize=testsize/1000 ;
  sname = sprintf('%s_tr%1.2f_v%1.2f_t%1.2f', da.sname, trsize, valsize, ...
      testsize) ;
else
  sname = sprintf('%s_tr%i_v%i_t%i', da.sname, trsize, valsize, testsize) ;
end ;


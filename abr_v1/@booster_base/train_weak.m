function wl=train_weak(bob, data)
% wl=booster_base.train_weak(bob, data)

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

wl=bob.proto ;

if bob.num_param==2,
  wl = do_learn(wl, data, bob.param1, bob.param2) ;
elseif bob.num_param==1,
  wl = do_learn(wl, data, bob.param1) ;
else
  wl = do_learn(wl, data) ;
end ;

function display(bob)
% adabooster_cg.display(bob)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

display(bob.adabooster) ;

disp('adabooster_regul object') ;
disp(sprintf(' phi: %1.3e', bob.phi)) ;
disp(sprintf(' lambda: %1.3e', bob.lambda)) ;

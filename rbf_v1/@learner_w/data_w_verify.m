function data_w_verify(ln, dataset)
% data_w_verify(ln, dataset)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

if ~isa(dataset, 'data_w'),
  error('this is not a "data_w"-dataset') ;
end ;
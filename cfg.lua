-- Configuration file name: "Test configuration file"
-- Generated on Fri Aug  2 16:21:44 2019
local cfg = {}

-- SECTIONS --
-- section x
cfg.x = {}
cfg.x.P = 2000.0
cfg.x.I = 11.0
cfg.x.D = 5.0
cfg.x.sat = 3000.0
cfg.x.m = 1.5
cfg.x.c = 0.01

-- section y
cfg.y = {}
cfg.y.P = 2000.0
cfg.y.I = 11.0
cfg.y.D = 5.0
cfg.y.sat = 3000.0
cfg.y.m = 1.1
cfg.y.c = 0.01

-- section z
cfg.z = {}
cfg.z.P = 2000.0
cfg.z.I = 11.0
cfg.z.D = 5.0
cfg.z.sat = 3000.0
cfg.z.m = 1.0
cfg.z.c = 0.01

-- END OF SECTIONS --
-- Now return the table, so that the file `cfg.lua' can be loaded as:
--   local config = require 'cfg'
return cfg

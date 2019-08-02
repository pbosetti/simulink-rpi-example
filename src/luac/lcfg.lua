--   _     ____ _____ ____ 
--  | |   / ___|  ___/ ___|
--  | |  | |   | |_ | |  _ 
--  | |__| |___|  _|| |_| |
--  |_____\____|_|   \____|
--  Lua ConFiG facility
-- All rights reserved (C) 2018 - Paolo Bosetti (paolo.bosetti@unitn.it)

-- local liluat = require("liluat")
LCFG = {}

LCFG.name = "Unnamed config"
LCFG.sections = {}

LCFG.template = [[
{{+function quote_if_string( value )
  if type(value) == "string" then
    return "\""..tostring(value).."\""
  else
    return value
  end
end}}
-- Configuration file name: "{{=name}}"
-- Generated on {{=os.date()}}
local cfg = {}

-- SECTIONS --
{{ for name, section in pairs(sections) do }}
-- section {{=name}}
cfg.{{=name}} = {}
  {{ for key, value in pairs(section) do }}
    {{if type(value) == "table" then}}
cfg.{{=name}}.{{=key}} = { {{for i,v in ipairs(value) do}}{{=quote_if_string(v)}}{{if i < #value then}},{{end}} {{end}}}
    {{else}}
cfg.{{+=name}}.{{=key}} = {{=quote_if_string(value)}}
    {{end}}
  {{end}}

{{end}}
-- END OF SECTIONS --
-- Now return the table, so that the file `cfg.lua' can be loaded as:
--   local config = require 'cfg'
return cfg
]]

function LCFG:string()
  local compiled_template = liluat.compile(self.template)
  return liluat.render(compiled_template, self)
end

function LCFG:write(filename)
  local code = self:string()
  if code:len() > 0 then
    local file = io.open(filename, "w")
    file:write(code)
    file:close()
  end
end

function LCFG:save()
  LCFG:write(self.filename)
end

function LCFG:load(filename)
  self.sections = dofile(filename)
  self.filename = filename
end

function LCFG:reload()
  LCFG:load(LCFG.filename)
end

function LCFG:get(path)
  local fields = {}
  local sep = "."
  path:gsub("([^"..sep.."]+)", function(c)
    table.insert(fields, c)
  end)
  assert(#fields == 2, "Malformed path (must be of type 'section.item', was " .. path ..")")
  assert(self.sections[fields[1]], "Non-existing section " .. fields[1])
  assert(self.sections[fields[1]][fields[2]], "Non-existing field " .. fields[1] .. "." .. fields[2])
  return self.sections[fields[1]][fields[2]]
end

function LCFG:set(path, value)
  local fields = {}
  local sep = "."
  path:gsub("([^"..sep.."]+)", function(c)
    table.insert(fields, c)
  end)
  assert(#fields == 2, "Malformed path (must be of type 'section.item', was " .. path ..")")
  if (self.sections[fields[1]] == nil) then
    self.sections[fields[1]] = {}
  end
  self.sections[fields[1]][fields[2]] = value
  return self
end

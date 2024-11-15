
---@class Set_globals
---@field define_code_raw string
---@field init_ignore string
---@field define_call_function string
---@field open_brackets string
---@field close_brackets string

---@class Response_render
---@field exist_error boolean
---@field error_message string|nil
---@field render_text string|nil

---@class CandangoEngine
---@field Get_text_by_file_content fun(path:string):string
---@field Render_text fun(text:string):Response_render


local info = debug.getinfo(1, "S")
local path = info.source:match("@(.*/)") or ""


local lib_path = ''

if os.getenv("HOME") then
    lib_path = path .. "candango_engine.so"
else
    perror("undefined os")
end

local load_lua = package.loadlib(lib_path, "candango_engine_start_point")

---@type CandangoEngine
local lib = load_lua()

---@type Set_globals
set_globals_caracter = set_globals_caracter

return lib

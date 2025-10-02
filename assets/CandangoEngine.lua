---@class CandangoKeysNames
---@field init string
---@field end string

---@class CandangoKeys
---@field ignore CandangoKeysNames
---@field raw CandangoKeysNames
---@field function CandangoKeysNames
---@field variable CandangoKeysNames

---@class CandangoResponse
---@field text string | nil
---@field error_message string | nil
---@field in_error boolean

---@class CandangoEngine
---@field render_text_by_path fun(path:string):CandangoResponse
---@field Get_text_by_file_content fun(path:string):string

---@type CandangoKeys
Keys = Keys

---@return CandangoEngine
local function get_CandangoEngine_lib()

    local info = debug.getinfo(1, "S")
    local path = info.source:match("@(.*/)") or ""
    if not path then
        error("path not found")
    end

  local file = "CandangoEngine.so"
  local start_point = "luaopen_CandangoEngine_start_point"

    local possible_local_file = path .. file
    local possible_local_lib = package.loadlib(possible_local_file, start_point)
    if possible_local_lib then
        return possible_local_lib()
    end

    local formmated_version = string.gsub(_VERSION, "Lua ", "")

    local global_path = "/usr/lib/lua/" .. formmated_version .. "/" .. file
    --verify if global path exists
    local possible_global_lib = package.loadlib(global_path, start_point)
    if possible_global_lib then
        return possible_global_lib()
    end

    error("lua not found")

end

local lib = get_CandangoEngine_lib()

return lib
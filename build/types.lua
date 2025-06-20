
--TYPES = darwin.candango.Get_text_by_file_content("assets/types/types.lua")

function Update_types()

  darwin.dtw.copy_any_overwriting("assets/types/CandangoEngine.lua", "realeses/CandangoEngine/CandangoEngine.lua")
  darwin.dtw.copy_any_overwriting("assets/types/CandangoEngine.lua", "test/lua/CandangoEngine/CandangoEngine.lua")

end





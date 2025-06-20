


function Camalga()

  local max_content = darwin.camalgamator.ONE_MB * 10
  local max_recursion = 100
  result = darwin.camalgamator.generate_amalgamation_with_callback("src/main.c",
    function(import, path)
      --print("import:", import)
      --print("path:", path)
      --print("-------------")

      if path == "../dependencies/dep.LuaCEmbed.h" then
        return "dont-include"
      end

      return "include-once"
    end,
    max_content,
    max_recursion
)
  io.open("realeses/CandangoEngine.c", "w"):write(result)

end






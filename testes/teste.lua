

candango = require("candangoEngine.candango_engine")

data_do_dia_de_entrega = "28/04/2026"

link = "https://cdn.jsdelivr.net/npm/chart.js"

set_globals_caracter.init_ignore = "#"
set_globals_caracter.open_brackets = "{"
set_globals_caracter.close_brackets = "}"
set_globals_caracter.define_code_raw = "%"
set_globals_caracter.define_call_function = "!"

function slasla()
  return "Meu nome é samuel Henrique."
end

global_default = ""

variavel = {}

variavel.nsei = "samuel"

local text_formated = candango.Render_text(candango.Get_text_by_file_content("testes/teste_home.html"))

if not text_formated.exist_error then
    local arquivo = io.open("testes/response.html", "w")

    if arquivo then
        arquivo:write(text_formated.render_text)

        arquivo:close()
        print("Texto salvo com sucesso.")
    end

else

    print(text_formated.error_message)

end








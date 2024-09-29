

candango = require("candangoEngine.candango_engine")

function slasla()
  return "Meu nome é samuel Henrique."
end

variavel = {}

variavel.nsei = "samuel"

local text_formated = candango.Render_text(candango.Get_text_by_file_content("testes/teste_home.html"))

local arquivo = io.open("testes/response.html", "w")

if arquivo then
    arquivo:write(text_formated)

    arquivo:close()
    print("Texto salvo com sucesso.")
else
    print("Erro ao abrir o arquivo.")
end









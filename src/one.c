
//silver_chain_scope_start
//mannaged by silver chain
#include "imports/imports.def.h"
//silver_chain_scope_end


#ifndef PRIVATE_CANDANGU_ENGINE_ONE_C
#define PRIVATE_CANDANGU_ENGINE_ONE_C

LuaCEmbedNamespace lua_n;

int main() {

  lua_n = newLuaCEmbedNamespace();

  LuaCEmbed *l = newLuaCEmbedEvaluation();


  lua_n.evaluate(l, "enff = \"VAriavel final\"");
  lua_n.evaluate(l, "SouFoda = \"Eu sou muito foda\"");
  lua_n.evaluate(l, "valor_Bancario = \"Meu valor bancario\"");
  lua_n.evaluate(l, "idade = 20");
  lua_n.evaluate(l, "samuel_Henrique = \"Samuelzão\"");
  lua_n.evaluate(l, "idade_banco = 20");
  lua_n.evaluate(l, "%s = \"\"", VARABLE_GLOBAL_TEXT_BY_LUA);
  

  char *texto = private_get_string_in_file_content("testes/teste_home.html");
    
  char *texto_formatado = private_print_until_delimiter(lua_n, l, texto);

  printf("\n%s\n", texto_formatado);

  //char *resultado = private_process_block(lua_n, l, " samuel henrique de sla {samuel_Henrique}");

  //lua_n.evaluate(l, "%s", resultado);

  //printf("\n\t%s\n\n", lua_n.globals.get_string(l, VARABLE_GLOBAL_TEXT_BY_LUA));
  

  lua_n.free(l);
  free(texto);

  return 0;
}

#endif /* ifndef MACRO */

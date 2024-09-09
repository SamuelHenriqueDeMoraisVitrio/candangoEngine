
#ifndef PRIVATE_CANDANGU_ENGINE_ONE_C
#define PRIVATE_CANDANGU_ENGINE_ONE_C

#include "definitions.c"
#include "dependencies/luacembed/LuaCEmbed.h"

LuaCEmbedNamespace lua_n;

int main() {

  lua_n = newLuaCEmbedNamespace();

  LuaCEmbed *l = newLuaCEmbedEvaluation();


  lua_n.evaluate(l, "enff = \"VAriavel final\"");
  lua_n.evaluate(l, "SouFoda = \"Eu sou muito foda\"");
  lua_n.evaluate(l, "valor_Bancario = \"Meu valor bancario\"");

  char *texto = private_get_string_in_file_content("testes/teste_home.html");
    
  char *texto_formatado = private_print_until_delimiter(lua_n, l, texto);

  printf("\n%s\n", texto_formatado);
    
  lua_n.free(l);
  free(texto);

  return 0;
}

#endif /* ifndef MACRO */

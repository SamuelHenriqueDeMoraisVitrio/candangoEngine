
#include "imports/imports.def.h"


int main() {

  Candango_lua = newLuaCEmbedNamespace();
  LuaCEmbed *l = newLuaCEmbedEvaluation();
  
  private_callbacks(l);

  Candango_lua.evaluate(l, "teste = 20");

  long value = Candango_lua.get_evaluation_long(l, "%s('a')", CANDANGO_LUA_RENDER_TEXT_BY_PATH);

  if (Candango_lua.has_errors(l)) {
    printf("Error candango: %s", Candango_lua.get_error_message(l));
    exit(1);
  }

  printf("\n\tvalue:%ld\n", value);

  //Candango_read_text_by_chunck("big_text.txt");
  //printf("%s", Candango_read_text_by_chunck("big_text.txt"));

  return 0;
}


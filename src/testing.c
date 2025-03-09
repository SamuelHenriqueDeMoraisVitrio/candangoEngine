
#include "imports/imports.def.h"


int main() {

  Candango_lua = newLuaCEmbedNamespace();
  LuaCEmbed *l = newLuaCEmbedEvaluation();
  
  create_table_globais(l);

  private_callbacks(l);

  Candango_lua.evaluate(l, "teste = 20");

  Candango_lua.evaluate(l, "local name_file_in = 'small_text.txt'; local response = render_text_by_path(name_file_in)");

  if (Candango_lua.has_errors(l)) {
    printf("Error candango: %s", Candango_lua.get_error_message(l));
    exit(1);
  }

  //Candango_read_text_by_chunck("big_text.txt");
  //printf("%s", Candango_read_text_by_chunck("big_text.txt"));

  return 0;
}


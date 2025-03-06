
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end


LuaCEmbedResponse *Candango_render_text_by_path_and_save(LuaCEmbed *args){

  return NULL;
}

LuaCEmbedResponse *Candango_render_text_by_path(LuaCEmbed *args){

  char *str = Candango_lua.args.get_str(args, 0);

  if (Candango_lua.has_errors(args)) {
    printf("Error candango: Not provieded args in function\n%s", Candango_lua.get_error_message(args));
    exit(1);
  }

  long teste = Candango_lua.get_evaluation_long(args, "teste");

  if (Candango_lua.has_errors(args)) {
    printf("Error candango: %s", Candango_lua.get_error_message(args));
    exit(1);
  }

  return Candango_lua.response.send_long(teste);
}













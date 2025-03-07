
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

  bool in_error = false;
  const char *text = Candango_read_text_by_chunck(str, args, &in_error);

  LuaCEmbedTable *response = Candango_lua.tables.new_anonymous_table(args);
  Candango_lua.tables.set_string_prop(response, "response", in_error?NULL:text);
  Candango_lua.tables.set_string_prop(response, "error_message", in_error?text:NULL);
  Candango_lua.tables.set_bool_prop(response, "in_error", in_error);

  return Candango_lua.response.send_table(response);
}













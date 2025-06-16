
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end


/*
  * Function that performs the entire rendering 
  * process but saves it in a specific path.
*/
LuaCEmbedResponse *Candango_render_text_by_path_and_save(LuaCEmbed *args){

  return NULL;
}

/*
  * Function that receives a file 
  * path and from there it renders 
  * the text and returns the rendered 
  * text.
*/
LuaCEmbedResponse *Candango_render_text_by_path(LuaCEmbed *args){

  char *str = Candango_lua.args.get_str(args, 0);

  if (Candango_lua.has_errors(args)) {
    printf("Error candango: Not provieded args in function\n%s", Candango_lua.get_error_message(args));
    exit(1);
  }

  Candango_set_keys();

  LuaCEmbed *machine_virtual_extension = Candango_lua.newLuaLib(args->state);

  bool in_error = false;
  const char *text = Candango_read_text_by_chunck(str, machine_virtual_extension, &in_error);

  LuaCEmbedTable *response = Candango_lua.tables.new_anonymous_table(args);
  Candango_lua.tables.set_string_prop(response, "text", in_error?NULL:text);
  Candango_lua.tables.set_string_prop(response, "error_message", in_error?text:NULL);
  Candango_lua.tables.set_bool_prop(response, "in_error", in_error);

  return Candango_lua.response.send_table(response);
}













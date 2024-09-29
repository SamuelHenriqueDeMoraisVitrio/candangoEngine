
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end



LuaCEmbedResponse *get_string_in_file_content(LuaCEmbed *args){

  char *request_args = lua.args.get_str(args, 0);

  if(lua.has_errors(args)){
    char *error_msg =  lua.get_error_message(args);
    return  lua.response.send_error(error_msg);
  }

  return lua.response.send_str(private_get_string_in_file_content(request_args));
}



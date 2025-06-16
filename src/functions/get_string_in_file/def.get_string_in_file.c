
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end



LuaCEmbedResponse *get_string_in_file_content(LuaCEmbed *args){

  char *request_args = Candango_lua.args.get_str(args, 0);

  if(Candango_lua.has_errors(args)){
    char *error_msg = Candango_lua.get_error_message(args);
    return  Candango_lua.response.send_error(error_msg);
  }

  return Candango_lua.response.send_str(private_get_string_in_file_content(request_args));
}



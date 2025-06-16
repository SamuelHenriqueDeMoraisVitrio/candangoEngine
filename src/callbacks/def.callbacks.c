
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.dec.h"
//silver_chain_scope_end

/*
  * Main function to define the 
  * callbacks that can be used in the lib.

#define CANDANGO_LUA_GET_TEXT_BY_FILE_CONTENT "Get_text_by_file_content"
#define CANDANGO_LUA_RENDER_TEXT_BY_PATH "render_text_by_path"
*/

void private_callbacks(LuaCEmbed *l){

  Candango_lua.add_callback(l, CANDANGO_LUA_GET_TEXT_BY_FILE_CONTENT, get_string_in_file_content);
  Candango_lua.add_callback(l, CANDANGO_LUA_RENDER_TEXT_BY_PATH, Candango_render_text_by_path);

}

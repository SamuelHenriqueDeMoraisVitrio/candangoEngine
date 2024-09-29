
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.dec.h"
//silver_chain_scope_end


void private_callbacks(LuaCEmbed *l){

  lua.add_callback(l, LUA_GET_TEXT_BY_FILE_CONTENT, get_string_in_file_content);
  lua.add_callback(l, LUA_RENDER_TEXT, private_render_text_by_lua);

}


//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.dec.h"
//silver_chain_scope_end

void private_callbacks(LuaCEmbed *l){

  Candango_lua.add_callback(l, CANDANGO_LUA_GET_TEXT_BY_FILE_CONTENT, get_string_in_file_content);
  Candango_lua.add_callback(l, CANDANGO_LUA_RENDER_TEXT_BY_PATH, Candango_render_text_by_path);

}

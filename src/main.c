
//silver_chain_scope_start
//mannaged by silver chain
#include "imports/imports.def.h"
//silver_chain_scope_end

int candango_engine_start_point(lua_State *state) {

  lua = newLuaCEmbedNamespace();
  LuaCEmbed *l = lua.newLuaLib(state);

  private_callbacks(l);
  
  return lua.perform(l);
}


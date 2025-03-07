
//silver_chain_scope_start
//mannaged by silver chain
#include "imports/imports.def.h"
//silver_chain_scope_end



int luaopen_CandangoEngine_start_point(lua_State *state) {

  Candango_lua = newLuaCEmbedNamespace();
  LuaCEmbed *l = Candango_lua.newLuaLib(state);

  create_table_globais(l);

  private_callbacks(l);

  return Candango_lua.perform(l);
}



//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end


void create_table_key(LuaCEmbed *l, const char *name_table, const char *init, const char *end){
  LuaCEmbedTable *Candango_key = Candango_lua.tables.new_anonymous_table(l);
  Candango_lua.tables.set_string_prop(Candango_key, "init", init);
  Candango_lua.tables.set_string_prop(Candango_key, "end", end);
  Candango_lua.tables.set_sub_table_prop(Candango_globals_caracters, name_table, Candango_key);
}

void create_table_globais(LuaCEmbed *l){
  Candango_globals_caracters = Candango_lua.globals.new_table(l, "set_keys_caracters");
  create_table_key(l, "IGNORE", CANDANGO_KEY_INIT_IGNORE, CANDANGO_KEY_END_IGNORE);
  create_table_key(l, "RAW", CANDANGO_KEY_INIT_RAW_CONTEXT, CANDANGO_KEY_END_RAW_CONTEXT);
  create_table_key(l, "FUNCTION", CANDANGO_KEY_INIT_FUNCTION, CANDANGO_KEY_END_FUNCTION);
  create_table_key(l, "VARIABLE", CANDANGO_KEY_INIT_VARIABLE, CANDANGO_KEY_END_VARIABLE);
}






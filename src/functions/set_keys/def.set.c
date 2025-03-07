
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end


void create_table_key(LuaCEmbed *l, const char *name_table, const char *init, const char *end){
  LuaCEmbedTable *Candango_key = Candango_lua.tables.new_anonymous_table(l);
  Candango_lua.tables.set_string_prop(Candango_key, CANDANGO_INIT_PROP, init);
  Candango_lua.tables.set_string_prop(Candango_key, CANDANGO_END_PROP, end);
  Candango_lua.tables.set_sub_table_prop(Candango_globals_caracters, name_table, Candango_key);
}

void create_table_globais(LuaCEmbed *l){
  Candango_globals_caracters = Candango_lua.globals.new_table(l, CANDANGO_TABLE_SET_KEYS);
  create_table_key(l, CANDANGO_IGNORE_PROP, CANDANGO_DEFAULT_KEY_INIT_IGNORE, CANDANGO_DEFAULT_KEY_END_IGNORE);
  create_table_key(l, CANDANGO_RAW_PROP, CANDANGO_DEFAULT_KEY_INIT_RAW_CONTEXT, CANDANGO_DEFAULT_KEY_END_RAW_CONTEXT);
  create_table_key(l, CANDANGO_FUNCTION_PROP, CANDANGO_DEFAULT_KEY_INIT_FUNCTION, CANDANGO_DEFAULT_KEY_END_FUNCTION);
  create_table_key(l, CANDANGO_VARIABLE_PROP, CANDANGO_DEFAULT_KEY_INIT_VARIABLE, CANDANGO_DEFAULT_KEY_END_VARIABLE);

  Candango_set_keys();
}

void Candango_set_key_in_global(const char *table_name, char *init_out, char *end_out){
  LuaCEmbedTable *Candango_table = Candango_lua.tables.get_sub_table_prop(Candango_globals_caracters, table_name);
  init_out = Candango_lua.tables.get_string_prop(Candango_table, CANDANGO_INIT_PROP);
  end_out = Candango_lua.tables.get_string_prop(Candango_table, CANDANGO_END_PROP);
}

void Candango_set_keys(){
  Candango_set_key_in_global(CANDANGO_IGNORE_PROP, CANDANGO_KEY_INIT_IGNORE, CANDANGO_KEY_END_IGNORE);
  Candango_set_key_in_global(CANDANGO_RAW_PROP, CANDANGO_KEY_INIT_RAW_CONTEXT, CANDANGO_KEY_END_RAW_CONTEXT);
  Candango_set_key_in_global(CANDANGO_FUNCTION_PROP, CANDANGO_KEY_INIT_FUNCTION, CANDANGO_KEY_INIT_FUNCTION);
  Candango_set_key_in_global(CANDANGO_VARIABLE_PROP, CANDANGO_KEY_INIT_VARIABLE, CANDANGO_KEY_INIT_VARIABLE);
}

const char **Candango_get_init_keys(){

  const char **Candango_keys = malloc(CANDANGO_SIZE_INIT_KEYS * sizeof(char *) + 1);

  Candango_keys[0] = CANDANGO_KEY_INIT_IGNORE;
  Candango_keys[1] = CANDANGO_KEY_INIT_RAW_CONTEXT;
  Candango_keys[2] = CANDANGO_KEY_INIT_FUNCTION;
  Candango_keys[3] = CANDANGO_KEY_INIT_VARIABLE;

  return Candango_keys;
}




//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end

/*
 * Here are functions to create a global table where you can configure 
 * the keys used in the text, such as '{' for 'ze'. Or leave the defaults below.

//Values keys
#define CANDANGO_DEFAULT_KEY_INIT_IGNORE  "$#"
#define CANDANGO_DEFAULT_KEY_END_IGNORE  "#$"

#define CANDANGO_DEFAULT_KEY_INIT_RAW_CONTEXT  "#{"
#define CANDANGO_DEFAULT_KEY_END_RAW_CONTEXT  "}"

#define CANDANGO_DEFAULT_KEY_INIT_FUNCTION  "!{"
#define CANDANGO_DEFAULT_KEY_END_FUNCTION "}"

#define CANDANGO_DEFAULT_KEY_INIT_VARIABLE "{"
#define CANDANGO_DEFAULT_KEY_END_VARIABLE "}"

//names_keys
#define CANDANGO_TABLE_SET_KEYS "keys"
#define CANDANGO_IGNORE_PROP "ignore"
#define CANDANGO_RAW_PROP "raw"
#define CANDANGO_FUNCTION_PROP "function"
#define CANDANGO_VARIABLE_PROP "variable"

#define CANDANGO_INIT_PROP "init"
#define CANDANGO_END_PROP "end"
*/

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
}

void Candango_set_key_in_global(const char *table_name, char **init_out, char **end_out){
  LuaCEmbedTable *Candango_table = Candango_lua.tables.get_sub_table_prop(Candango_globals_caracters, table_name);
  *init_out = Candango_lua.tables.get_string_prop(Candango_table, CANDANGO_INIT_PROP);
  *end_out = Candango_lua.tables.get_string_prop(Candango_table, CANDANGO_END_PROP);
}

void Candango_set_keys(){
  Candango_set_key_in_global(CANDANGO_IGNORE_PROP, &CANDANGO_KEY_INIT_IGNORE, &CANDANGO_KEY_END_IGNORE);
  Candango_set_key_in_global(CANDANGO_RAW_PROP, &CANDANGO_KEY_INIT_RAW_CONTEXT, &CANDANGO_KEY_END_RAW_CONTEXT);
  Candango_set_key_in_global(CANDANGO_FUNCTION_PROP, &CANDANGO_KEY_INIT_FUNCTION, &CANDANGO_KEY_END_FUNCTION);
  Candango_set_key_in_global(CANDANGO_VARIABLE_PROP, &CANDANGO_KEY_INIT_VARIABLE, &CANDANGO_KEY_END_VARIABLE);

  Candango_update_init_keys();
}

void Candango_update_init_keys(){
  Candango_keys_init[0] = CANDANGO_KEY_INIT_IGNORE;
  Candango_keys_init[1] = CANDANGO_KEY_INIT_RAW_CONTEXT;
  Candango_keys_init[2] = CANDANGO_KEY_INIT_FUNCTION;
  Candango_keys_init[3] = CANDANGO_KEY_INIT_VARIABLE;
}



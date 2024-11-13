
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end



void set_globals(){
  DEFINE_CODE_RAW = (char)lua.tables.get_string_prop(globals_caracters, "define_code_raw")[0];
  INIT_IGNORE = (char)lua.tables.get_string_prop(globals_caracters, "init_ignore")[0];
  DEFINE_CALL_FUNCTION = (char)lua.tables.get_string_prop(globals_caracters, "define_call_function")[0];
  OPEN_BRACKETS_CARACTER = (char)lua.tables.get_string_prop(globals_caracters, "open_brackets")[0];
  CLOSE_BRACKETS_CARACTER = (char)lua.tables.get_string_prop(globals_caracters, "close_brackets")[0];
}

void create_table_globais(LuaCEmbed *l){
  globals_caracters = lua.globals.new_table(l, "set_globals_caracter");
  lua.tables.set_string_prop(globals_caracters, "define_code_raw", "%%");
  lua.tables.set_string_prop(globals_caracters, "init_ignore", "#");
  lua.tables.set_string_prop(globals_caracters, "define_call_function", "!");
  lua.tables.set_string_prop(globals_caracters, "open_brackets", "{");
  lua.tables.set_string_prop(globals_caracters, "close_brackets", "}");

}



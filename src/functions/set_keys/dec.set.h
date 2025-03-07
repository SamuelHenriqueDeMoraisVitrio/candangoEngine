
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end




void create_table_key(LuaCEmbed *l, const char *name_table, const char *init, const char *end);

void create_table_globais(LuaCEmbed *l);

void Candango_set_key_in_global(const char *table_name, char *init_out, char *end_out);

void Candango_set_keys();

const char **Candango_get_init_keys();





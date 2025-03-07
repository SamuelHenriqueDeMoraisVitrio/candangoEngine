
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.typesA.h"
//silver_chain_scope_end





char CANDANGO_KEY_INIT_IGNORE[5] = "$#\0";
char CANDANGO_KEY_END_IGNORE[5] = "#$\0";

char CANDANGO_KEY_INIT_RAW_CONTEXT[5] = "{#\0";
char CANDANGO_KEY_END_RAW_CONTEXT[5] = "#}\0";

char CANDANGO_KEY_INIT_FUNCTION[5] = "!{\0";
char CANDANGO_KEY_END_FUNCTION[5] = "}\0";

char CANDANGO_KEY_INIT_VARIABLE[5] = "{\0";
char CANDANGO_KEY_END_VARIABLE[5] = "}\0";

const char *Candango_keys_init[CANDANGO_SIZE_INIT_KEYS];


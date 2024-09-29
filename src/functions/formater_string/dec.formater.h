
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

bool private_is_valid_variable(LuaCEmbed *l, const char *str, int len);

char *private_recursivly_str_in_struct(LuaCEmbed *l, char *str);

char *private_str_append(char *dest, const char *src, ...);

char *private_process_block(LuaCEmbed *l, char *str);

bool private_verifyr_second_open_bracket_recurslivy(LuaCEmbed *l, char **str, char **result);

LuaCEmbedResponse *private_render_text_by_lua(LuaCEmbed *args);

bool private_verifyr_function_call(LuaCEmbed *l, char **str, char **result);



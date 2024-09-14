
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end


//char *private_print_until_delimiter(LuaCEmbedNamespace lua, LuaCEmbed *l, char *str);

bool private_is_valid_variable(LuaCEmbedNamespace lua, LuaCEmbed *l, const char *str, int len);

//bool private_verifyr_second_open_bracket(LuaCEmbedNamespace lua, LuaCEmbed *l, char **str);

char *private_recursivly_str_in_struct(LuaCEmbedNamespace lua, LuaCEmbed *l, char *str);

char *private_str_append(char *dest, const char *src, ...);

char *private_process_block(LuaCEmbedNamespace lua, LuaCEmbed *l, char *str);

bool private_verifyr_second_open_bracket_recurslivy(LuaCEmbedNamespace lua, LuaCEmbed *l, char **str, char **result);

char *private_render_text_by_lua(LuaCEmbedNamespace lua, LuaCEmbed *l, char *str);



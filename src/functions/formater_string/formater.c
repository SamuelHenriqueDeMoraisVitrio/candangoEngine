
#include "../uniq.definitions.h"
#include <stdio.h>

bool private_is_valid_variable(const char *str, int len) {
    for (int i = 0; i < len; i++) {
if (!(isalnum(str[i]) || str[i] == '_')) {  
            return false;
        }
    }
    return true;
}

char *private_print_until_delimiter(LuaCEmbedNamespace lua, LuaCEmbed *l, char *str) {

    lua.evaluate(l, "%s = \"\"", VARABLE_GLOBAL_TEXT_BY_LUA);

    if (!str) {
        return lua.globals.get_string(l, VARABLE_GLOBAL_TEXT_BY_LUA);
    }

    bool inside_quotes = false;
    char quote_type = '\0';
    bool inside_braces = false;
    const char *start = NULL;
    char valor_buffer[200];
    int valor_index = 0;

    while (*str != '\0') {
        if ((*str == '`') && !inside_braces) {
            if (inside_quotes && *str == quote_type) {
                inside_quotes = false;
            } else if (!inside_quotes) {
                inside_quotes = true;
                quote_type = *str;
            }
            lua.evaluate(l, "%s = %s .. \"%c\"", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, *str);
        } else if (*str == '{' && !inside_quotes) {
            inside_braces = true;
            start = str + 1;
            valor_index = 0;
        } else if (*str == '}' && inside_braces) {
            inside_braces = false;

            const char *p = start;
            while (p != str && valor_index < sizeof(valor_buffer) - 1) {
                valor_buffer[valor_index++] = *p++;
            }
            valor_buffer[valor_index] = '\0';

            if (private_is_valid_variable(valor_buffer, valor_index)) {
                lua.evaluate(l, "%s = %s .. %s", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, valor_buffer);
            } else {
                lua.evaluate(l, "%s = %s .. \"{%s}\"", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, valor_buffer);
            }
        } else {
            if (!inside_braces) {
                lua.evaluate(l, "%s = %s .. \"%c\"", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, *str);
            }
        }

        str++;
    }
    
    return lua.globals.get_string(l, VARABLE_GLOBAL_TEXT_BY_LUA);

}




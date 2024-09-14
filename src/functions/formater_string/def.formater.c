
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end


bool private_is_valid_variable(const char *str, int len) {
    for (int i = 0; i < len; i++) {
        if (!(isalnum(str[i]) || str[i] == '_')) {  
            return false;
        }
    }
    return true;
}

bool private_verifyr_second_open_bracket_recurslivy(LuaCEmbedNamespace lua, LuaCEmbed *l, char **str, char **result) {

    int count_second_bracket = 0;
    int start_second = 0;
    int start_main = 0;
    int final_second_bracket = 0;
    int final_bracket_main = 0;
    bool open_second = false;
    bool close_second = false;
    int add_bracket = 0;

    while (true) {
        count_second_bracket++;
        if (*(*str + count_second_bracket) == '\0') {
            return false;
        }
        if (*(*str + count_second_bracket) == ' ') {
            continue;
        }
        if(*(*str + count_second_bracket) == '\n'){
            *(*str + count_second_bracket) = ' ';
        }
        if (*(*str + count_second_bracket) == '}') {
            if (!open_second) {
                return false;
            }
            if (add_bracket > 0) {
                add_bracket--;
                continue;
            }
            if (!close_second) {
                final_second_bracket = count_second_bracket;
                start_main = final_second_bracket + 1;
                close_second = true;
                continue;
            }
            final_bracket_main = count_second_bracket + 1;
            break;
        }
        if (*(*str + count_second_bracket) == '{') {
            if (!open_second) {
                start_second = count_second_bracket;
                open_second = true;
            } else {
                add_bracket++;
            }
        }
    }

    char text_no_formated[final_second_bracket - start_second + 1];
    char text_formated[final_bracket_main - start_main + 1];

    strncpy(text_no_formated, *str + start_second + 1, final_second_bracket - start_second - 1);
    text_no_formated[final_second_bracket - start_second - 1] = '\0';

    strncpy(text_formated, *str + start_main, final_bracket_main - start_main - 1);
    text_formated[final_bracket_main - start_main - 1] = '\0';

    *result = private_str_append(*result, " %s %s end", text_no_formated, private_process_block(lua, l, text_formated));

    *str = *str + final_bracket_main;

    return true;
}

char *private_str_append(char *dest, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    char temp[1];
    int size = vsnprintf(temp, 1, format, args) + 1;
    va_end(args);

    char *formatted_str = (char *)malloc(size);
    if (formatted_str == NULL) {
        return NULL;
    }
    
    va_start(args, format);
    vsprintf(formatted_str, format, args);
    va_end(args);

    if (dest == NULL) {
        dest = (char *)malloc(size);
        strcpy(dest, formatted_str);
    } else {
        dest = (char *)realloc(dest, strlen(dest) + size);
        strcat(dest, formatted_str);
    }

    free(formatted_str);
    return dest;
}


char *private_process_block(LuaCEmbedNamespace lua, LuaCEmbed *l, char *str) {

    char *result_str = NULL;

    if (!str) {
        return "";
    }

    bool inside_quotes = false;
    char quote_type = '\0';
    bool inside_braces = false;
    const char *start = NULL;
    char valor_buffer[200];
    int valor_index = 0;
    bool formater_start = false;
    bool formater_text_start = false;
    bool open_brackets_by_text_no_formating = false;

    while (*str != '\0') {
        if(*str == '\n'){
            str++;
            continue;
        }
        if (*str == '`' && !inside_braces) {
            if (inside_quotes && *str == quote_type) {
                inside_quotes = false;
            } else if (!inside_quotes) {
                inside_quotes = true;
                quote_type = *str;
            }
            result_str = private_str_append(result_str, " %s = %s .. \"%c\" ", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, *str);
        } else if (*str == '{' && !inside_quotes) {
            open_brackets_by_text_no_formating = private_verifyr_second_open_bracket_recurslivy(lua, l, &str, &result_str);
            if(!open_brackets_by_text_no_formating){
                inside_braces = true;
                start = str + 1;
                valor_index = 0;
            }
            open_brackets_by_text_no_formating = false;
        } else if (*str == '}' && inside_braces) {
            inside_braces = false;

            const char *p = start;
            while (p != str && valor_index < sizeof(valor_buffer) - 1) {
                valor_buffer[valor_index++] = *p++;
            }
            valor_buffer[valor_index] = '\0';

            if (private_is_valid_variable(valor_buffer, valor_index)) {
                result_str = private_str_append(result_str, " %s = %s .. %s ", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, valor_buffer);
            } else {
                result_str = private_str_append(result_str, " %s = %s .. \"{%s}\" ", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, valor_buffer);
            }
        } else {
            if (!inside_braces || inside_quotes) {
                result_str = private_str_append(result_str, " %s = %s .. \"%c\" ", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, *str);
            }
        }

        str++;
    }
    

    return result_str;
}



char *private_render_text_by_lua(LuaCEmbedNamespace lua, LuaCEmbed *l, char *str){
    
    lua.evaluate(l, "%s = \"\"", VARABLE_GLOBAL_TEXT_BY_LUA);

    if (!str) {
        return lua.globals.get_string(l, VARABLE_GLOBAL_TEXT_BY_LUA);
    }

    lua.evaluate(l, " %s ", private_process_block(lua, l, str));

    return lua.globals.get_string(l, VARABLE_GLOBAL_TEXT_BY_LUA);
}

/*
bool private_verifyr_second_open_bracket(LuaCEmbedNamespace lua, LuaCEmbed *l, char **str) {
    int count_second_bracket = 0;
    int start_second = 0;
    int start_main = 0;
    int final_second_bracket = 0;
    int final_bracket_main = 0;
    bool open_second = false;
    bool close_second = false;
    int add_bracket = 0;

    while (true) {
        count_second_bracket++;
        if (*(*str + count_second_bracket) == '\0') {
            return false;
        }
        if (*(*str + count_second_bracket) == ' ') {
            continue;
        }
        if(*(*str + count_second_bracket) == '\n'){
            *(*str + count_second_bracket) = ' ';
            continue;
        }
        if (*(*str + count_second_bracket) == '}') {
            if (!open_second) {
                return false;
            }
            if (add_bracket > 0) {
                add_bracket--;
                continue;
            }
            if (!close_second) {
                final_second_bracket = count_second_bracket;
                start_main = final_second_bracket + 1;
                close_second = true;
                continue;
            }
            final_bracket_main = count_second_bracket + 1;
            break;
        }
        if (*(*str + count_second_bracket) == '{') {
            if (!open_second) {
                start_second = count_second_bracket;
                open_second = true;
            } else {
                add_bracket++;
            }
        }
    }

    char text_no_formated[final_second_bracket - start_second + 1];
    char text_formated[final_bracket_main - start_main + 1];

    strncpy(text_no_formated, *str + start_second + 1, final_second_bracket - start_second - 1);
    text_no_formated[final_second_bracket - start_second - 1] = '\0';

    strncpy(text_formated, *str + start_main, final_bracket_main - start_main - 1);
    text_formated[final_bracket_main - start_main - 1] = '\0';

    lua.evaluate(l, " %s %s end", text_no_formated, private_process_block(lua, l, text_formated));

    *str = *str + final_bracket_main;

    return true;
}
*/

/*
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
    bool formater_start = false;
    bool formater_text_start = false;
    bool open_brackets_by_text_no_formating = false;

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
            open_brackets_by_text_no_formating = private_verifyr_second_open_bracket(lua, l, &str);
            if(open_brackets_by_text_no_formating == false){
                inside_braces = true;
                start = str + 1;
                valor_index = 0;
            }
            open_brackets_by_text_no_formating = false;
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
            if (!inside_braces || inside_quotes) {
                lua.evaluate(l, "%s = %s .. \"%c\"", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, *str);
            }
        }

        str++;
    }
    
    return lua.globals.get_string(l, VARABLE_GLOBAL_TEXT_BY_LUA);

}
*/

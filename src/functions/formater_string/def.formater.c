
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end

bool private_verifyr_second_open_bracket_recurslivy(LuaCEmbed *l, char **str, char **result) {

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
        if (*(*str + count_second_bracket) == CLOSE_BRACKETS_CARACTER) {
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
        if (*(*str + count_second_bracket) == OPEN_BRACKETS_CARACTER) {
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

    char *result_str_leak = private_process_block(l, text_formated);
    *result = private_str_append(*result, " %s %s end", text_no_formated, result_str_leak);

    *str = *str + final_bracket_main - 1;

    free(result_str_leak);

    return true;
}

bool private_verifyr_function_call(LuaCEmbed *l, char **str, char **result) {
    bool start_call = false;
    bool close_call = false;
    int start_function_call = 0;
    int close_function_call = 0;
    int count_lines = 0;

    while (*(*str + count_lines) == ' ') {
        count_lines++;
    }

    while (true) {
        if (*(*str + count_lines) == '\0') {
            return false;
        }
        if (*(*str + count_lines) == DEFINE_CALL_FUNCTION) {
            start_call = true;
            start_function_call = count_lines + 1;
            if (*(*str + start_function_call) == CLOSE_BRACKETS_CARACTER) {
                return false;
            }
        } else if (*(*str + count_lines) == CLOSE_BRACKETS_CARACTER) {
            if (!start_call) {
                return false;
            }
            close_function_call = count_lines;
            close_call = true;
            break;
        }
        count_lines++;
    }

    if (!close_call) {
        return false;
    }

    int length = close_function_call - start_function_call;

    if (length <= 0) {
        return false;
    }

    char text_call[length + 1];
    strncpy(text_call, *str + start_function_call, length);
    text_call[length] = '\0';

    *result = private_str_append(*result, " %s = %s .. %s ", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, text_call);

    *str = *str + close_function_call;

    return true;
}

bool private_verifyr_raw_code_call(LuaCEmbed *l, char **str, char **result) {
    
    bool start_call = false;
    bool close_call = false;
    int start_function_call = 0;
    int close_function_call = 0;
    int count_lines = 0;
    int open_brackets = 0;

    

    while (true) {
        count_lines++;
        if (*(*str + count_lines) == '\0') {
            return false;
        }
        if(*(*str + count_lines) == '\n'){
            *(*str + count_lines) = ' ';
        }
        if (*(*str + count_lines) == DEFINE_CODE_RAW) {
            start_call = true;
            start_function_call = count_lines + 1;
            if (*(*str + start_function_call) == CLOSE_BRACKETS_CARACTER) {
                return false;
            }
        } else if (*(*str + count_lines) == CLOSE_BRACKETS_CARACTER) {
            if (!start_call) {
                return false;
            }
            if(open_brackets < 1){
                close_function_call = count_lines;
                close_call = true;
                break;
            }
            open_brackets--;
        } else if (*(*str + count_lines) == OPEN_BRACKETS_CARACTER) {
            if(!start_call){
                return false;
            }
            open_brackets++;
        }
    }


    if (!close_call) {
        return false;
    }

    int length = close_function_call - start_function_call;

    if (length <= 0) {
        return false;
    }

    char text_call[length + 1];
    strncpy(text_call, *str + start_function_call, length);
    text_call[length] = '\0';

    *result = private_str_append(*result, " %s ", text_call);

    *str = *str + close_function_call;

    return true;
}

char *private_str_append(char *dest, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    char temp[1];
    int size = vsnprintf(temp, sizeof(temp), format, args) + 1;
    va_end(args);

    char *formatted_str = (char *)malloc(size);
    if (formatted_str == NULL) {
        return NULL;
    }

    va_start(args, format);
    vsnprintf(formatted_str, size, format, args);
    va_end(args);

    if (dest == NULL) {
        dest = formatted_str;
    } else {
        char *new_dest = (char *)realloc(dest, strlen(dest) + size);
        if (new_dest == NULL) {
            free(formatted_str);
            return NULL;
        }
        dest = new_dest;
        strcat(dest, formatted_str);
        free(formatted_str);
    }

    return dest;
}

void private_add_line_breack(char **str, char **result_str, bool started_string, bool inside_braces){

    if(started_string){
        *result_str = private_str_append(*result_str, "\\n");
    }

    (*str)++;
}

void private_init_str_append(char **result, bool *init_str){

    *result = private_str_append(*result, " %s = %s .. \"", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA);
    *init_str = true;
}

char *private_process_block(LuaCEmbed *l, char *str) {

    char *result_str = NULL;

    if (!str) {
        return "";
    }

    bool inside_quotes = false;
    bool inside_braces = false;
    const char *start = NULL;
    char valor_buffer[200];
    int valor_index = 0;
    bool formater_start = false;
    bool formater_text_start = false;
    bool open_brackets_by_text_no_formating = false;
    bool started_a_string = false;

    

    while (*str != '\0') {
        if(*str == '\n'){
            private_add_line_breack(&str, &result_str, started_a_string, inside_braces);
            continue;
        }
        if(*str == '\"'){
            if(!inside_braces){
                if(!started_a_string){
                    result_str = private_str_append(result_str, " %s = %s .. \"\\\"", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA); 
                    started_a_string = true;
                }else{
                    result_str = private_str_append(result_str, "\\\"");
                }
                str++;
                continue;
            }
            //*str = ' ';
        }
        if(*str == '\\'){
            if(*(str + 1) == INIT_IGNORE){
                str++;
                continue;
            }
        }
        if (*str == INIT_IGNORE && !inside_braces) {

            if (*(str - 1) != '\\'){
                if (*(str + 1) == '/') {
                    inside_quotes = false;
                    str++;
                } else{
                    inside_quotes = true;
                }
                str++;
                continue;
            }

            if(!started_a_string){
                result_str = private_str_append(result_str, " %s = %s .. \"%c", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, *str);
                started_a_string = true;
            }else{
                result_str = private_str_append(result_str, "%c", *str);
            }
            str++;
            continue;
        }else if (*str == OPEN_BRACKETS_CARACTER && !inside_quotes) {
            if(started_a_string){
                result_str = private_str_append(result_str, "\" ");
                started_a_string = false;
            }
            if(!private_verifyr_raw_code_call(l, &str, &result_str)){
                open_brackets_by_text_no_formating = private_verifyr_second_open_bracket_recurslivy(l, &str, &result_str);
                if(!open_brackets_by_text_no_formating){
                    if(!private_verifyr_function_call(l, &str, &result_str)){
                        inside_braces = true;
                        start = str + 1;
                        valor_index = 0;
                    }
                }else{
                    private_init_str_append(&result_str, &started_a_string);
                }
            }
            open_brackets_by_text_no_formating = false;
        }else if (*str == CLOSE_BRACKETS_CARACTER && inside_braces) {
            inside_braces = false;

            const char *p = start;
            while (p != str && valor_index < sizeof(valor_buffer) - 1) {
                valor_buffer[valor_index++] = *p++;
            }
            valor_buffer[valor_index] = '\0';

            result_str = private_str_append(result_str, " %s = %s .. %s ", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, valor_buffer);
            private_init_str_append(&result_str, &started_a_string);
        } else{
            if (!inside_braces) {
                if(!started_a_string){
                    result_str = private_str_append(result_str, " %s = %s .. \"%c", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, *str);
                    started_a_string = true;
                }else{
                    result_str = private_str_append(result_str, "%c", *str);
                }
            }
        }
        if(*str == '\\'){
            if(!started_a_string){
                result_str = private_str_append(result_str, " %s = %s .. \"%s", VARABLE_GLOBAL_TEXT_BY_LUA, VARABLE_GLOBAL_TEXT_BY_LUA, "\\\\");
                started_a_string = true;
            }else{
                result_str = private_str_append(result_str, "%s", "\\\\");
            }
            str++;
            continue;
        }

        str++;
    }

    if(started_a_string){
        result_str = private_str_append(result_str, "\" ");
        started_a_string = false;
    }

    return result_str;
}

LuaCEmbedResponse *private_render_text_by_lua(LuaCEmbed *args){

    set_globals();

    if(lua.args.get_type(args, 0) != 4){ // iqual the string
        return NULL;
    }
    
    char *str = lua.args.get_str(args, 0);

    if (lua.has_errors(args)) {
        return NULL;
    }

    LuaCEmbed *machine_virtual_extension = lua.newLuaLib(args->state);

    lua.evaluate(machine_virtual_extension, "%s = \"\"", VARABLE_GLOBAL_TEXT_BY_LUA);

    char *response;

    if (!str) {
        response = lua.globals.get_string(machine_virtual_extension, VARABLE_GLOBAL_TEXT_BY_LUA);
        //lua.free(machine_virtual_extension);
        return lua.response.send_str(response);
    }

    char *result_str = private_process_block(machine_virtual_extension, str);

    lua.evaluate(machine_virtual_extension, " %s ", result_str);

    free(result_str);
    
    LuaCEmbedTable *table_response = lua.tables.new_anonymous_table(args);

    if (lua.has_errors(machine_virtual_extension)) {
        lua.tables.set_bool_prop(table_response, "exist_error", true);
        lua.tables.set_string_prop(table_response, "error_message", lua.get_error_message(machine_virtual_extension));
        lua.tables.set_string_prop(table_response, "render_text", "");
        //lua.free(machine_virtual_extension);
        return lua.response.send_table(table_response);
    }

    lua.tables.set_bool_prop(table_response, "exist_error", false);
    lua.tables.set_string_prop(table_response, "render_text", lua.globals.get_string(args, VARABLE_GLOBAL_TEXT_BY_LUA));
    lua.tables.set_string_prop(table_response, "error_message", "");

    //lua.free(machine_virtual_extension);

    return lua.response.send_table(table_response);
}





#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../src/dependencies/doTheWorld/doTheWorld.h"

void print_until_delimiter(char *str) {

  if(!str){
    return;
  }

  bool inside_quotes = false;
  char quote_type = '\0';
  bool inside_braces = false;
  const char *start = NULL;
  char valor_buffer[200];
  int valor_index = 0;

  while (*str != '\0') {
      if ((*str == '"' || *str == '\'') && !inside_braces) {

        if (inside_quotes && *str == quote_type) {
          inside_quotes = false;
        } else if (!inside_quotes) {
          inside_quotes = true;
          quote_type = *str;
        }
        putchar(*str);
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

        char outro_valor[214];
        sprintf(outro_valor, "[Capturado: %s]", valor_buffer);

        printf("%s", outro_valor);
      } else {
        if (!inside_braces) {

            putchar(*str);
        }
      }

      str++;
  }
  putchar('\n');
}

int main() {
  char *texto = dtw_load_string_file_content("testes/teste_home.html");
  
  print_until_delimiter(texto);
  
  free(texto);

  return 0;
}

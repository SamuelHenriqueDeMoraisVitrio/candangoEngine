
#include <stdio.h>
#include <stdbool.h>  // Para usar booleanos
#include <string.h>   // Para manipulação de strings

void print_until_delimiter(const char *str) {
    bool inside_quotes = false;   // Para verificar se estamos dentro de aspas
    char quote_type = '\0';       // Tipo de aspas (' ou ")
    bool inside_braces = false;   // Para verificar se estamos dentro das chaves
    const char *start = NULL;     // Para armazenar o início da string nas chaves
    char valor_buffer[200];       // Buffer temporário para armazenar o valor dentro das chaves
    int valor_index = 0;          // Índice do buffer

    while (*str != '\0') {
        if ((*str == '"' || *str == '\'') && !inside_braces) {
            // Detecta aspas de abertura ou fechamento, apenas se não estivermos dentro de chaves
            if (inside_quotes && *str == quote_type) {
                inside_quotes = false;  // Fecha as aspas
            } else if (!inside_quotes) {
                inside_quotes = true;   // Abre as aspas
                quote_type = *str;
            }
            putchar(*str);  // Imprime as aspas
        } else if (*str == '{' && !inside_quotes) {
            // Detecta abertura de chave, apenas se não estivermos dentro de aspas
            inside_braces = true;
            start = str + 1;  // Pula o '{' para começar a processar dentro das chaves
            valor_index = 0;  // Reseta o índice do buffer
        } else if (*str == '}' && inside_braces) {
            // Detecta fechamento de chave
            inside_braces = false;

            // Copia o conteúdo dentro das chaves para a variável `valor_buffer`
            const char *p = start;
            while (p != str && valor_index < sizeof(valor_buffer) - 1) {
                valor_buffer[valor_index++] = *p++;
            }
            valor_buffer[valor_index] = '\0';  // Finaliza a string no buffer

            // Mostra o valor capturado para fins de teste
            printf("[Capturado: %s]", valor_buffer);
        } else {
            if (!inside_braces) {
                // Imprime o conteúdo normal fora das chaves
                putchar(*str);
            }
        }

        str++;
    }
    putchar('\n');  // Pula uma linha ao final
}

int main() {
    const char *texto = "Exemplo {teste_valor} de string {outro_valor}";
    
    print_until_delimiter(texto);
    
    return 0;
}

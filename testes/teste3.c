
#include <stdio.h>
#include <ctype.h>  // Para isalnum (verificar se é alfanumérico)
#include <stdbool.h>  // Para usar booleanos

void print_until_delimiter(const char *str) {
    bool inside_quotes = false;   // Para verificar se estamos dentro de aspas
    char quote_type = '\0';       // Tipo de aspas (' ou ")
    bool inside_braces = false;   // Para verificar se estamos dentro das chaves
    const char *start = NULL;     // Para armazenar o início da string nas chaves
    
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
        } else if (*str == '}' && inside_braces) {
            // Detecta fechamento de chave
            inside_braces = false;

            // Verifica se o conteúdo entre as chaves é válido (letras, números, ou _)
            const char *p = start;
            bool valid = true;
            while (p != str) {
                if (!isalnum(*p) && *p != '_') {
                    valid = false;  // Encontrou caractere inválido
                    break;
                }
                p++;
            }

            // Se válido, imprime o conteúdo dentro das chaves
            if (valid && start != str) {
                printf("[conteúdo válido: ");
                for (p = start; p != str; p++) {
                    putchar(*p);
                }
                printf("]");
            } else {
                // Se inválido, imprime o conteúdo como parte normal da string
                printf("{");
                for (p = start; p != str; p++) {
                    putchar(*p);
                }
                printf("}");
            }
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
    const char *texto = "Exemplo {valido_nome} de string {invalido nome} com aspas \"{invalido}\" e sem aspas {outro_valido}";
    
    print_until_delimiter(texto);
    
    return 0;
}

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

            if (valid && start != str) {
                printf("Conteúdo válido dentro das chaves: ");
                for (p = start; p != str; p++) {
                    putchar(*p);  // Imprime o conteúdo dentro das chaves
                }
                putchar('\n');
            } else {
                printf("Conteúdo inválido dentro das chaves.\n");
            }
        }

        str++;
    }
}

int main() {
    const char *texto = "Exemplo {primeiro} de string {segundo valor} com aspas `{terceiro}` e sem aspas {quarto_valor}";
    
    print_until_delimiter(texto);
    
    return 0;
}


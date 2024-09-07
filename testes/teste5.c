#include <stdio.h>
#include <stdlib.h>  // Para malloc e free
#include <ctype.h>   // Para isalnum (verificar se é alfanumérico)
#include <stdbool.h> // Para usar booleanos
#include <string.h>  // Para manipulação de strings

void process_string(const char *str) {
    bool inside_quotes = false;   // Para verificar se estamos dentro de aspas
    char quote_type = '\0';       // Tipo de aspas (' ou ")
    bool inside_braces = false;   // Para verificar se estamos dentro das chaves
    const char *start = NULL;     // Para armazenar o início da string nas chaves
    char *valor_buffer = NULL;    // Ponteiro para armazenar o valor dentro das chaves
    char *texto_antes = NULL;     // Ponteiro para armazenar o texto antes das chaves
    int texto_antes_len = 0;      // Comprimento do texto antes das chaves

    // Contador para calcular o tamanho do texto antes das chaves
    const char *cursor = str;
    while (*cursor != '\0' && *cursor != '{') {
        texto_antes_len++;
        cursor++;
    }

    // Aloca memória para o texto antes das chaves
    texto_antes = (char *)malloc(texto_antes_len + 1);  // +1 para o caractere nulo
    if (texto_antes == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    // Copia o texto antes das chaves para a variável
    strncpy(texto_antes, str, texto_antes_len);
    texto_antes[texto_antes_len] = '\0';  // Adiciona o caractere nulo

    // Move o ponteiro da string original para onde as chaves começam
    str += texto_antes_len;

    // Itera sobre a string para capturar o valor dentro das chaves
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

            // Calcula o comprimento do conteúdo dentro das chaves
            int valor_len = str - start;

            // Aloca memória para o valor dentro das chaves
            valor_buffer = (char *)malloc(valor_len + 1);  // +1 para o caractere nulo
            if (valor_buffer == NULL) {
                printf("Erro ao alocar memória.\n");
                free(texto_antes);  // Libera a memória alocada antes
                return;
            }

            // Copia o conteúdo dentro das chaves para a variável `valor_buffer`
            strncpy(valor_buffer, start, valor_len);
            valor_buffer[valor_len] = '\0';  // Adiciona o caractere nulo

            // Mostra o valor capturado para fins de teste
            printf("[Capturado: %s]\n", valor_buffer);

            break;  // Encerra a busca após capturar o primeiro valor válido
        } else {
            if (!inside_braces) {
                putchar(*str);  // Imprime o texto normal
            }
        }

        str++;
    }

    // Exibe o texto capturado antes da primeira chave válida
    printf("Texto antes da primeira chave válida: \"%s\"\n", texto_antes);

    // Libera a memória alocada
    free(texto_antes);
    if (valor_buffer != NULL) {
        free(valor_buffer);
    }
}

int main() {
    const char *texto = "Exemplo de string {variavel_valida} com mais conteúdo";

    process_string(texto);

    return 0;
}


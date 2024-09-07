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

    // Vamos iterar até o final da string
    const char *cursor = str;
    
    while (*cursor != '\0') {
        texto_antes_len = 0;  // Reiniciando para cada nova parte antes das chaves
        
        // Captura o texto antes da próxima chave '{'
        const char *start_text = cursor;
        while (*cursor != '\0' && *cursor != '{') {
            cursor++;
            texto_antes_len++;
        }
        
        // Aloca e armazena o texto antes das chaves
        texto_antes = (char *)malloc(texto_antes_len + 1);  // +1 para o caractere nulo
        if (texto_antes == NULL) {
            printf("Erro ao alocar memória.\n");
            return;
        }
        strncpy(texto_antes, start_text, texto_antes_len);
        texto_antes[texto_antes_len] = '\0';  // Adiciona o caractere nulo

        // Exibe o texto antes das chaves
        printf("Texto antes das chaves: \"%s\"\n", texto_antes);
        free(texto_antes);  // Libera a memória

        // Se chegamos no fim da string, saímos do loop
        if (*cursor == '\0') {
            break;
        }

        // Agora processamos o conteúdo dentro das chaves
        cursor++;  // Pula o '{'
        const char *start_braces = cursor;

        int valor_len = 0;
        while (*cursor != '\0' && *cursor != '}') {
            cursor++;
            valor_len++;
        }

        // Se encontramos o '}', capturamos o valor dentro das chaves
        if (*cursor == '}') {
            // Aloca e armazena o valor dentro das chaves
            valor_buffer = (char *)malloc(valor_len + 1);  // +1 para o caractere nulo
            if (valor_buffer == NULL) {
                printf("Erro ao alocar memória.\n");
                return;
            }
            strncpy(valor_buffer, start_braces, valor_len);
            valor_buffer[valor_len] = '\0';  // Adiciona o caractere nulo

            // Exibe o valor dentro das chaves
            printf("Valor dentro das chaves: \"%s\"\n", valor_buffer);
            free(valor_buffer);  // Libera a memória

            cursor++;  // Pula o '}'
        }
    }
}

int main() {
    const char *texto = "Exemplo de string {variavel1} texto entre {vari avel2} mais texto";

    process_string(texto);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Este programa gera 1 milhão de registros (NUM_REGISTROS) em um
 * arquivo binário chamado "registros.bin".
 *
 * Cada registro possui:
 *   - chave   → int
 *   - dado1   → long aleatório
 *   - dado2   → string aleatória de 1000 caracteres
 *   - dado3   → string aleatória de 5000 caracteres
 *
 * O usuário escolhe a ordem das chaves:
 *   - "aleatorio"
 *   - "ascendente"
 *   - "descendente"
 */

#define NUM_REGISTROS 1000000  // Total de registros gerados     
#define TAM_DADO2 5000         // Tamanho da string dado3

// Estrutura usada para gerar os registros binários
typedef struct {
    int chave;
    long int dado1;
    char dado2[TAM_DADO2 + 1];// +1 para '\0'
} TipoRegistro;


/*
 * Gera uma string aleatória contendo 'len' caracteres.
 */
void gerar_string_aleatoria(char *str, int len) {
    const char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    for (int i = 0; i < len; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        str[i] = charset[key];
    }
    str[len] = '\0'; // final da string
}


/*
 * Embaralha o vetor de inteiros usando algoritmo Fisher-Yates.
 * É usado para gerar chaves aleatórias.
 */
void embaralhar(int *array, int tamanho) {
    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}


int main(int argc, char *argv[]) {

    /*
     * ======= TRATAMENTO DOS ARGUMENTOS =======
     */
    if (argc != 2) {
        printf("Uso: %s <modo: aleatorio | ascendente | descendente>\n", argv[0]);
        return 1;
    }

    const char *modo = argv[1];


    /*
     * ======= GERAR VETOR INICIAL DE CHAVES =======
     * Vetor começando de 1 até NUM_REGISTROS
     * que será depois embaralhado ou invertido.
     */
    int *chaves = malloc(NUM_REGISTROS * sizeof(int));
    if (!chaves) {
        perror("Erro ao alocar memória para chaves");
        return 1;
    }

    for (int i = 0; i < NUM_REGISTROS; i++) {
        chaves[i] = i + 1;
    }

    /*
     * ======= AJUSTAR ORDEM DAS CHAVES =======
     */
    if (strcmp(modo, "aleatorio") == 0) {
        embaralhar(chaves, NUM_REGISTROS);

    } else if (strcmp(modo, "descendente") == 0) {

        // Inversão simples (1,2,3,... → 1M,...,3,2,1)
        for (int i = 0; i < NUM_REGISTROS / 2; i++) {
            int tmp = chaves[i];
            chaves[i] = chaves[NUM_REGISTROS - 1 - i];
            chaves[NUM_REGISTROS - 1 - i] = tmp;
        }

    } else if (strcmp(modo, "ascendente") != 0) {
        printf("Modo inválido. Use: aleatorio, ascendente ou descendente.\n");
        free(chaves);
        return 1;
    }


    /*
     * ======= ABRIR ARQUIVO BINÁRIO PARA ESCRITA =======
     */
    FILE *arquivo = fopen("registros.bin", "wb");
    if (!arquivo) {
        perror("Erro ao abrir arquivo binário para escrita");
        free(chaves);
        return 1;
    }

    srand((unsigned)time(NULL)); // semente para randomização


    /*
     * ======= GERAR E ESCREVER CADA REGISTRO =======
     */
    TipoRegistro reg;

    for (int i = 0; i < NUM_REGISTROS; i++) {

        reg.chave = chaves[i];

        // long aleatório combinando duas chamadas de rand()
        reg.dado1 = ((long)rand() << 16) | rand();

        gerar_string_aleatoria(reg.dado2, TAM_DADO2);

        fwrite(&reg, sizeof(TipoRegistro), 1, arquivo);

        // Progresso a cada 100 mil registros
        if ((i + 1) % 100000 == 0)
            printf("Gerados %d registros...\n", i + 1);
    }


    /*
     * ======= FINALIZAR =======
     */
    fclose(arquivo);
    free(chaves);

    printf("\nArquivo 'registros.bin' criado com sucesso no modo '%s'.\n",
           modo);

    return 0;
}

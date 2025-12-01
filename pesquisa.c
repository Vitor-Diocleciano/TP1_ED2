#include "pesquisa.h"
#include "Acesso_Sequencial_Indexado.h"
#include "arvoreBinaria.h"
#include "arvoreB.h"
#include "arvoreB_e.h"

/*
 * Programa principal responsável por:
 *   - Ler argumentos da linha de comando
 *   - Abrir o arquivo correspondente (asc, desc, aleatório)
 *   - Executar o método de busca solicitado
 *   - Exibir resultados e métricas
 */

int main(int argc, char *argv[]) {

    /*
     * ====== VALIDAÇÃO DE ARGUMENTOS ======
     */
    if (argc < 5 || argc > 6) {
        printf("Uso incorreto!\n");
        printf("Formato: <metodo> <quantidade> <modo> <chave> [-P]\n");
        return 1;
    }

    // Método de pesquisa (1, 2, 3 ou 4)
    int opcao = atoi(argv[1]);

    // Quantidade de registros que devem ser lidos do arquivo
    int quantidade = atoi(argv[2]);

    // Situação do arquivo (ordenado asc, desc ou aleatório)
    int modo = atoi(argv[3]);

    // Chave que o usuário quer encontrar
    int chave = atoi(argv[4]);

    // Flag opcional para imprimir todos os registros
    bool imprimir = false;

    if (argc == 6 && strcmp(argv[5], "[-P]") == 0) {
        imprimir = true;
    }

    // Estrutura que receberá o registro encontrado
    TipoItem x;

    // Estruturas de análise do pré-processamento e da pesquisa
    Analise analise1, analise2;

    /*
     * ====== SELECIONAR ARQUIVO CORRETO ======
     */
    char nomeArq[21];

    if (modo == 1) {
        strcpy(nomeArq, "ascendente.bin");
    } else if (modo == 2) {
        strcpy(nomeArq, "descendente.bin");
    } else if (modo == 3) {
        strcpy(nomeArq, "aleatorio.bin");
    } else {
        printf("Modo inválido!\n");
        exit(1);
    }

    /*
     * ====== ABRIR ARQUIVO ======
     */
    FILE *arquivo = fopen(nomeArq, "rb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    /*
     * ====== IMPRIMIR REGISTROS (OPCIONAL) ======
     */
    if (imprimir) {
        rewind(arquivo);
        for (int i = 0; i < quantidade; i++) {
            if (fread(&x, sizeof(TipoItem), 1, arquivo) != 1) {
                printf("Erro ao ler registro.\n");
                return 1;
            }
            printf("\nRegistro %d:\nChave: %d\nDado1: %ld\nDado2: %s\n",
                   i + 1, x.chave, x.dado1, x.dado2);
        }
    }

    rewind(arquivo); // Garantir leitura desde o início

    /*
     * ====== SELEÇÃO DO MÉTODO ======
     */
    bool encontrado = false;

    switch (opcao) {

        case 1: // ASI
            encontrado = ASI(arquivo, quantidade, chave, &x, &analise1, &analise2);
            break;

        case 2: // Árvore Binária
            encontrado = ABP(arquivo, quantidade, chave, &x, &analise1, &analise2);
            break;

        case 3: // Árvore B
            encontrado = AB(arquivo, quantidade, chave, &x, &analise1, &analise2);
            break;

        case 4: // Árvore B*
            encontrado = ABE(arquivo, quantidade, &x, chave, &analise1, &analise2);
            break;

        default:
            printf("Método inválido!\n");
            fclose(arquivo);
            return 1;
    }

    /*
     * ====== IMPRIMIR RESULTADOS ======
     */
    if (encontrado) {
        printf("\nItem encontrado!\n");
        printf("Chave: %d\nDado1: %ld\nDado2: %s\n",
               x.chave, x.dado1, x.dado2);
    } else {
        printf("\nItem NÃO encontrado!\n");
    }

    printf("\n==== PRÉ-PROCESSAMENTO ====\n");
    printf("Comparações: %d\n", analise1.comparacoes);
    printf("Transferências: %d\n", analise1.transeferencia);
    printf("Tempo: %.6lf s\n", analise1.tempo);

    printf("\n======= PESQUISA =======\n");
    printf("Comparações: %d\n", analise2.comparacoes);
    printf("Transferências: %d\n", analise2.transeferencia);
    printf("Tempo: %.6lf s\n", analise2.tempo);

    fclose(arquivo);
    return 0;
}

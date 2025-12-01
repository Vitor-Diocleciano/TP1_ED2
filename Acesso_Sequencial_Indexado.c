#include "Acesso_Sequencial_Indexado.h"

/*
 * ======================== FUNÇÃO ASI ============================
 * Constrói uma tabela de índices (pegando a chave do PRIMEIRO item
 * de cada página). Essa tabela permite identificar rapidamente qual
 * página deve conter a chave procurada.
 *
 * Depois realiza a pesquisa na página correta usando busca binária.
 * ================================================================
 */
bool ASI(FILE *arq, int quantidade, int chave,
         TipoItem *x, Analise *analise1, Analise *analise2)
{
    // ====================== PRÉ-PROCESSAMENTO =====================
    clock_t inicio = clock(); // início do tempo

    // Tabela de índices: cada posição guarda a chave do 1º item da página
    TipoIndice tabela[MAXTABELA];

    TipoItem item;
    int pos = 0; // quantidade de páginas indexadas

    // zera contadores
    analise1->comparacoes = 0;
    analise1->transeferencia = 0;

    /*
     * Construção da tabela:
     * lê apenas o PRIMEIRO registro de cada página e salva a chave.
     */
    for (int i = 0; i < quantidade; i += ITENSPAGINA) {

        // Lê o primeiro item da página
        fread(&item, sizeof(TipoItem), 1, arq);

        // Armazena a chave do primeiro registro da página
        tabela[pos].chave = item.chave;
        pos++;

        analise1->transeferencia++;

        // Pula os próximos registros da página para ir ao início da página seguinte
        fseek(arq, (ITENSPAGINA - 1) * sizeof(TipoItem), SEEK_CUR);
    }

    // tempo do pré-processamento
    analise1->tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;

    // ========================== PESQUISA ==========================
    inicio = clock(); // reinicia contagem para a fase de busca

    // zera contadores de análise da busca
    analise2->comparacoes = 0;
    analise2->transeferencia = 0;

    /*
     * Realiza a pesquisa usando a tabela.
     * Se encontrar, retorna true; caso contrário, false.
     */
    bool achou = pesquisa(arq, tabela, pos, quantidade, analise2, x, chave);

    analise2->tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;

    return achou;
}



/*
 * ======================= FUNÇÃO PESQUISA ========================
 * Usa a tabela de índices para identificar em qual página a chave
 * procurada pode estar. Depois lê essa página inteira e aplica
 * busca binária nos registros.
 * ================================================================
 */
bool pesquisa(FILE *arq, TipoIndice *tab, int NumPagina, int quantidade,
              Analise *analise, TipoItem *x, int chave)
{
    TipoItem pagina[ITENSPAGINA]; // buffer que conterá a página carregada
    int quantItens;
    long desloc;

    rewind(arq); // garante leitura do início

    /*
     * Procurar a página provável:
     * tab[i].chave é a chave do 1º item da página i.
     * Quando tab[i].chave > chave, a chave está na página anterior.
     */
    int i = 0;
    while (i < NumPagina && tab[i].chave <= chave) {
        i++;
        analise->comparacoes++;
    }

    // Se a chave é menor que a chave do 1º índice → não está no arquivo
    if (i == 0) {
        return false;
    }

    /*
     * Descobre quantos itens tem na página:
     * - páginas completas: ITENSPAGINA
     * - última página pode estar incompleta
     */
    if (i < NumPagina) {
        quantItens = ITENSPAGINA;
    } else {
        int resto = quantidade % ITENSPAGINA;
        quantItens = (resto == 0) ? ITENSPAGINA : resto;
    }

    // Calcula posição da página no arquivo
    desloc = (i - 1) * ITENSPAGINA * sizeof(TipoItem);
    fseek(arq, desloc, SEEK_SET);

    // lê toda a página para a memória
    size_t lidos = fread(pagina, sizeof(TipoItem), quantItens, arq);
    if (lidos < (size_t)quantItens) {
        printf("ERRO: não foi possível carregar a página completamente.\n");
    }

    analise->transeferencia++;

    /*
     * Agora busca dentro da página com busca binária.
     */
    int posicao = buscaBinaria(pagina, 0, quantItens - 1, chave, analise);

    if (posicao != -1) {
        // copia registro encontrado para *x
        *x = pagina[posicao];
        return true;
    }

    return false;
}



/*
 * ======================= BUSCA BINÁRIA ==========================
 * Algoritmo recursivo clássico de busca binária.
 * As comparações são contabilizadas na estrutura Analise.
 * ================================================================
 */
int buscaBinaria(TipoItem *registros, int esquerda, int direita,
                 int chave, Analise *analise)
{
    if (esquerda <= direita) {

        int meio = esquerda + (direita - esquerda) / 2;

        // compara chave com a posição do meio
        analise->comparacoes++;

        if (registros[meio].chave == chave) {
            return meio;
        }

        if (registros[meio].chave < chave) {
            return buscaBinaria(registros, meio + 1, direita, chave, analise);
        }

        return buscaBinaria(registros, esquerda, meio - 1, chave, analise);
    }

    return -1; // não encontrado
}

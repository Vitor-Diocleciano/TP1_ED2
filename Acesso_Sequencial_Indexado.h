#ifndef Acesso_Sequencial_Indexado
#define Acesso_Sequencial_Indexado

#include "pesquisa.h"

/*
 * Função principal do Acesso Sequencial Indexado (ASI).
 *
 * Parâmetros:
 *  - arq        → ponteiro para o arquivo binário aberto
 *  - quantidade → número total de registros no arquivo
 *  - chave      → chave buscada
 *  - x          → ponteiro onde será armazenado o registro encontrado
 *  - analise1   → estrutura que armazena desempenho do pré-processamento
 *  - analise2   → estrutura que armazena desempenho da pesquisa
 *
 * Retorno:
 *  - true  → registro encontrado
 *  - false → não encontrado
 */
bool ASI(FILE *arq, int quantidade, int chave,
         TipoItem *x, Analise *analise1, Analise *analise2);

/*
 * Função auxiliar que realiza a busca no arquivo usando a tabela de índices.
 */
bool pesquisa(FILE *arq, TipoIndice *tab, int NumPagina, int quantidade,
              Analise *analise, TipoItem *x, int chave);

/*
 * Busca binária dentro de uma única página lida na memória.
 */
int buscaBinaria(TipoItem *registros, int esquerda, int direita,
                 int chave, Analise *analise);

#endif

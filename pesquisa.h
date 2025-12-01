#ifndef PESQUISA_H
#define PESQUISA_H

// Bibliotecas padrão
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
 * ====== CONSTANTES GERAIS DO PROJETO ======
 */

// Número de itens armazenados em uma página de disco (para ASI)
#define ITENSPAGINA 50

// Tamanho máximo da tabela de índices do ASI
#define MAXTABELA 1000

// Tamanhos dos campos de string dos registros
#define TAM_DADO2 5000
//#define TAM_DADO3 5000

/*
 * ====== CONSTANTES E ESTRUTURAS PARA ÁRVORE B ======
 */

#define ORDEM 1000                 // Ordem mínima da árvore B
#define MAX_REGISTROS (2 * ORDEM)  // Número máximo de chaves em uma página
#define MAX_FILHOS (2 * ORDEM + 1) // Número máximo de filhos

/*
 * ====== ESTRUTURA DE ANÁLISE ======
 * Guarda métricas de contagem usadas para avaliar o desempenho
 * dos métodos de pesquisa.
 */
typedef struct {
    int transeferencia;   // Quantidade de leituras feitas no arquivo (páginas/vetores)
    int comparacoes;      // Quantidade de comparações de chaves feitas
    double tempo;         // Tempo total de execução (em segundos)
} Analise;

/*
 * ====== TIPO ITEM ======
 * Estrutura que representa UM registro armazenado no arquivo binário.
 */
typedef struct {
    int chave;                       // chave usada na busca
    long int dado1;                  // dado simples numérico
   // char dado2[TAM_DADO2 + 1];       // string grande
    char dado2[TAM_DADO2 + 1];       // string MUITO grande
} TipoItem;

/*
 * ====== ACESSO SEQUENCIAL INDEXADO ======
 * Estrutura contendo apenas a chave do primeiro item de cada página.
 * Usada como índice secundário.
 */
typedef struct {
    int chave;
} TipoIndice;

/*
 * ====== ÁRVORE BINÁRIA DE PESQUISA ======
 * Cada nó possui:
 *   - um registro
 *   - posição de filho esquerdo
 *   - posição de filho direito
 */
typedef struct {
    TipoItem itemArvore;
    long esq;
    long dir;
} ArvoreBinaria;

/*
 * ====== ÁRVORE B ======
 */
#define M 5 // Grau mínimo (para testes)

// Página da Árvore B
typedef struct {
    int n;                        // Número de chaves existentes
    int folha;                    // 1 = folha | 0 = interno
    TipoItem itens[2 * M];        // Vetor de chaves armazenadas
    long filhos[2 * M + 1];       // Ponteiros para filhos
} PaginaB;

/*
 * ====== ÁRVORE B* (VARIAÇÃO MAIS EFICIENTE) ======
 */

typedef enum { INTERNO, FOLHA } TipoNo;

typedef struct {
    int nchaves;
    int chaves[MAX_REGISTROS];
    long filhos[MAX_FILHOS]; // offsets no arquivo de índices
} PaginaInterna;

typedef struct {
    int nchaves;
    long registros_offsets[MAX_REGISTROS]; // offsets no arquivo de dados
    long prox_folha;                       // próximo nó folha
} PaginaFolha;

typedef struct {
    TipoNo tipo;
    union {
        PaginaInterna interna;
        PaginaFolha folha;
    } conteudo;
} TipoPagina;

#endif

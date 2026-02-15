/* 
 * Objetivo: Comparar a implementação e lógica de duas estruturas de dados fundamentais:
 * 1. BST (Binary Search Tree): Ótima para ordenação e busca geral.
 * 2. Trie (Prefix Tree): Especializada em strings e busca por prefixos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// ============================================================================
// ESTRUTURA 1: ÁRVORE BINÁRIA DE BUSCA (BST)
// Lógica: Cada nó tem até 2 filhos. Menores à esquerda, maiores à direita.
// ============================================================================

typedef struct NoBST {
    char palavra[50];       // Dado armazenado (string)
    struct NoBST* esquerda; // Ponteiro para subárvore com valores menores
    struct NoBST* direita;  // Ponteiro para subárvore com valores maiores
} NoBST;

// Cria um novo nó para a BST
NoBST* criarNoBST(char* palavra) {
    NoBST* novo = (NoBST*)malloc(sizeof(NoBST));
    if (novo) {
        strcpy(novo->palavra, palavra);
        novo->esquerda = NULL;
        novo->direita = NULL;
    }
    return novo;
}

// Insere uma string na BST mantendo a ordem alfabética (strcmp)
NoBST* inserirBST(NoBST* raiz, char* palavra) {
    // Caso base: encontrou um lugar vazio, insere aqui
    if (raiz == NULL) return criarNoBST(palavra);

    int cmp = strcmp(palavra, raiz->palavra);

    if (cmp < 0) {
        // Se a palavra é "menor" (vem antes no alfabeto), vai para a esquerda
        raiz->esquerda = inserirBST(raiz->esquerda, palavra);
    } else if (cmp > 0) {
        // Se a palavra é "maior", vai para a direita
        raiz->direita = inserirBST(raiz->direita, palavra);
    }
    // Se cmp == 0, a palavra já existe (ignoramos duplicatas neste exemplo)
    
    return raiz;
}

// Busca uma string na BST
bool buscarBST(NoBST* raiz, char* palavra) {
    if (raiz == NULL) return false; // Chegou ao fim e não achou

    int cmp = strcmp(palavra, raiz->palavra);

    if (cmp == 0) return true; // Achou!
    else if (cmp < 0) return buscarBST(raiz->esquerda, palavra); // Busca na esquerda
    else return buscarBST(raiz->direita, palavra); // Busca na direita
}

// --- Percursos da BST ---

// Em Ordem (In-Order): Esquerda -> Raiz -> Direita
// Resultado: Imprime as strings em ordem alfabética crescente.
void emOrdemBST(NoBST* raiz) {
    if (raiz != NULL) {
        emOrdemBST(raiz->esquerda);
        printf("%s ", raiz->palavra);
        emOrdemBST(raiz->direita);
    }
}

// Pré-Ordem (Pre-Order): Raiz -> Esquerda -> Direita
void preOrdemBST(NoBST* raiz) {
    if (raiz != NULL) {
        printf("%s ", raiz->palavra);
        preOrdemBST(raiz->esquerda);
        preOrdemBST(raiz->direita);
    }
}

// Pós-Ordem (Post-Order): Esquerda -> Direita -> Raiz
void posOrdemBST(NoBST* raiz) {
    if (raiz != NULL) {
        posOrdemBST(raiz->esquerda);
        posOrdemBST(raiz->direita);
        printf("%s ", raiz->palavra);
    }
}

// Libera memória da BST
void liberarBST(NoBST* raiz) {
    if (raiz != NULL) {
        liberarBST(raiz->esquerda);
        liberarBST(raiz->direita);
        free(raiz);
    }
}

// ============================================================================
// ESTRUTURA 2: TRIE (ÁRVORE DE PREFIXOS)
// Lógica: Cada nó representa uma letra. O caminho da raiz até um nó forma a palavra.
// ============================================================================

#define TAM_ALFABETO 26 // Considerando apenas letras minúsculas a-z

typedef struct NoTrie {
    struct NoTrie* filhos[TAM_ALFABETO]; // Vetor de ponteiros para as próximas letras
    bool fimDaPalavra;                   // Marca se este nó encerra uma palavra válida
} NoTrie;

// Cria um novo nó para a Trie
NoTrie* criarNoTrie() {
    NoTrie* novo = (NoTrie*)malloc(sizeof(NoTrie));
    if (novo) {
        novo->fimDaPalavra = false;
        for (int i = 0; i < TAM_ALFABETO; i++) {
            novo->filhos[i] = NULL; // Inicializa todos os filhos como NULL
        }
    }
    return novo;
}

// Auxiliar: Converte char para índice (0 a 25)
int charParaIndice(char c) {
    return tolower(c) - 'a';
}

// Insere uma palavra na Trie
void inserirTrie(NoTrie* raiz, char* palavra) {
    NoTrie* atual = raiz;
    
    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = charParaIndice(palavra[i]);
        
        // Validação simples para garantir que é letra
        if (indice < 0 || indice >= TAM_ALFABETO) continue;

        // Se não existe o caminho para essa letra, cria
        if (atual->filhos[indice] == NULL) {
            atual->filhos[indice] = criarNoTrie();
        }
        // Avança para o próximo nó
        atual = atual->filhos[indice];
    }
    // Marca o último nó como fim de uma palavra completa
    atual->fimDaPalavra = true;
}

// Busca uma palavra exata na Trie
bool buscarTrie(NoTrie* raiz, char* palavra) {
    NoTrie* atual = raiz;
    
    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = charParaIndice(palavra[i]);
        
        if (indice < 0 || indice >= TAM_ALFABETO) return false;

        // Se o caminho for interrompido (NULL), a palavra não existe
        if (atual->filhos[indice] == NULL) {
            return false;
        }
        atual = atual->filhos[indice];
    }
    // Retorna true apenas se chegamos ao final E estiver marcado como fim de palavra
    return (atual != NULL && atual->fimDaPalavra);
}

// Libera memória da Trie (Recursivo)
void liberarTrie(NoTrie* raiz) {
    if (raiz == NULL) return;
    for (int i = 0; i < TAM_ALFABETO; i++) {
        liberarTrie(raiz->filhos[i]);
    }
    free(raiz);
}

// ============================================================================
// MAIN: TESTES E COMPARAÇÃO
// ============================================================================

int main() {
    char* palavras[] = {"casa", "carro", "caminhao", "arvore", "dado", "bola"};
    int qtd = 6;

    printf("========================================================\n");
    printf("       ESTRUTURAS DE DADOS: BST vs TRIE\n");
    printf("========================================================\n");
    printf("Palavras a inserir: casa, carro, caminhao, arvore, dado, bola\n\n");

    // ------------------------------------------------------------
    // TESTE 1: BST
    // ------------------------------------------------------------
    printf("--- [1] Testando BST (Binary Search Tree) ---\n");
    NoBST* raizBST = NULL;
    
    for(int i = 0; i < qtd; i++) {
        raizBST = inserirBST(raizBST, palavras[i]);
    }

    printf("Percurso Em Ordem (Ordenado): ");
    emOrdemBST(raizBST);
    printf("\n");

    printf("Percurso Pre-Ordem: ");
    preOrdemBST(raizBST);
    printf("\n");

    printf("Percurso Pos-Ordem: ");
    posOrdemBST(raizBST);
    printf("\n");

    // Teste de Busca BST
    char busca1[] = "carro";
    char busca2[] = "avião";
    printf("Busca '%s': %s\n", busca1, buscarBST(raizBST, busca1) ? "ENCONTRADO" : "NAO ENCONTRADO");
    printf("Busca '%s': %s\n", busca2, buscarBST(raizBST, busca2) ? "ENCONTRADO" : "NAO ENCONTRADO");

    liberarBST(raizBST);
    printf("\n");

    // ------------------------------------------------------------
    // TESTE 2: TRIE
    // ------------------------------------------------------------
    printf("--- [2] Testando Trie (Prefix Tree) ---\n");
    NoTrie* raizTrie = criarNoTrie();

    for(int i = 0; i < qtd; i++) {
        inserirTrie(raizTrie, palavras[i]);
    }

    // Teste de Busca Trie
    // Note que a Trie é muito eficiente para verificar prefixos ou palavras exatas
    printf("Busca '%s': %s\n", busca1, buscarTrie(raizTrie, busca1) ? "ENCONTRADO" : "NAO ENCONTRADO");
    
    // Teste interessante da Trie: Palavra que existe como prefixo, mas não completa
    char busca3[] = "caminh"; // Prefixo de caminhao
    printf("Busca '%s' (prefixo de caminhao): %s\n", busca3, 
           buscarTrie(raizTrie, busca3) ? "ENCONTRADO" : "NAO ENCONTRADO (Pois nao eh palavra completa)");

    liberarTrie(raizTrie);
    
    printf("\nMemoria liberada. Fim do programa.\n");
    return 0;
}

/*
          [casa]
          /    \
      [carro]  [dado]
      /
  [caminhao]
    /
 [arvore]
    \
   [bola]

*/
/*
(Raiz)
  |
  +--- a --- r --- v --- o --- r --- e (*)
  |
  +--- b --- o --- l --- a (*)
  |
  +--- c --- a --+-- m --- i --- n --- h --- a --- o (*)
  |              |
  |              +-- r --- r --- o (*)
  |              |
  |              +-- s --- a (*)
  |
  +--- d --- a --- d --- o (*)

*/
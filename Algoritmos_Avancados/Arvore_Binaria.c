/*
Programa: Implementação de Árvore Binária em C
------------------------------------------------------------
Este programa demonstra como construir uma árvore binária simples
utilizando alocação dinâmica de memória em C. Ele permite:
- Inserir elementos na árvore binária (alocação dinâmica)
- Percorrer e exibir os elementos usando:
    * Pré-Ordem
    * Em Ordem
    * Pós Ordem
[PONTO DE ATENÇÃO #1] Estrutura básica do nó da árvore binária 
[PONTO DE ATENÇÃO #2] Função responsável por criar um novo nó
[PONTO DE ATENÇÃO #3] Função de inserção: posiciona o novo valor 
*/

#include <stdio.h>
#include <stdlib.h>

// [PONTO DE ATENÇÃO #1] Estrutura básica do nó da árvore binária
typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} No;

// [PONTO DE ATENÇÃO #2] Função responsável por criar um novo nó
No* criarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No)); // Alocação dinâmica
    if (novoNo == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// [PONTO DE ATENÇÃO #3] Função de inserção: posiciona o novo valor (Lógica BST)
No* inserir(No* raiz, int valor) {
    // Caso base: se a árvore (ou subárvore) for vazia, cria o nó aqui
    if (raiz == NULL) {
        return criarNo(valor);
    }

    // Se o valor for menor, vai para a esquerda
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    }
    // Se o valor for maior, vai para a direita
    else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    // Se for igual, não faz nada (não permitimos duplicatas neste exemplo)

    return raiz;
}

// --- Funções de Percurso (Traversals) ---

// Pré-Ordem: Raiz -> Esquerda -> Direita
// 1. Visita a raiz primeiro (imprime o valor).
// 2. Depois percorre toda a subárvore esquerda.
// 3. Por fim, percorre toda a subárvore direita.
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor); // Passo 1: Processa o nó atual
        preOrdem(raiz->esquerda);   // Passo 2: Chama recursivamente para a esquerda
        preOrdem(raiz->direita);    // Passo 3: Chama recursivamente para a direita
    }
}

// Em Ordem: Esquerda -> Raiz -> Direita (Imprime ordenado em BST)
// 1. Percorre toda a subárvore esquerda primeiro.
// 2. Visita a raiz (imprime o valor).
// 3. Percorre toda a subárvore direita.
// Nota: Em uma Árvore Binária de Busca, isso resulta nos números em ordem crescente.
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);    // Passo 1: Mergulha para a esquerda
        printf("%d ", raiz->valor); // Passo 2: Processa o nó atual (na volta da recursão)
        emOrdem(raiz->direita);     // Passo 3: Mergulha para a direita
    }
}

// Pós-Ordem: Esquerda -> Direita -> Raiz
// 1. Percorre toda a subárvore esquerda.
// 2. Percorre toda a subárvore direita.
// 3. Visita a raiz por último.
// Nota: Útil para deletar a árvore, pois garante que os filhos sejam processados antes do pai.
void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);   // Passo 1: Mergulha para a esquerda
        posOrdem(raiz->direita);    // Passo 2: Mergulha para a direita
        printf("%d ", raiz->valor); // Passo 3: Processa o nó atual (após visitar filhos)
    }
}

// Função auxiliar para liberar a memória da árvore
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int main() {
    No* raiz = NULL;

    printf("=== Implementação de Árvore Binária ===\n");
    printf("Inserindo valores: 50, 30, 20, 40, 70, 60, 80\n");

    // Construindo a árvore
    raiz = inserir(raiz, 50);
    inserir(raiz, 30);
    inserir(raiz, 20);
    inserir(raiz, 40);
    inserir(raiz, 70);
    inserir(raiz, 60);
    inserir(raiz, 10);

    /*
       Visualização da Árvore criada na memória:
             50
           /    \
         30      70
        /  \    /  \
      20   40  60   80
    */

    printf("\nExibindo em Pré-Ordem: ");
    preOrdem(raiz);

    printf("\nExibindo Em Ordem:   ");
    emOrdem(raiz);

    printf("\nExibindo em Pós-Ordem: ");
    posOrdem(raiz);
    printf("\n");

    // Limpeza de memória
    liberarArvore(raiz);
    printf("\nMemória liberada. Fim do programa.\n");

    return 0;
}
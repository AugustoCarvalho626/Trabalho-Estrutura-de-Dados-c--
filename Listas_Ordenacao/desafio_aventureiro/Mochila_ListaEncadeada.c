/*
 * Nome: Augusto Bento Carvalho
 *
 * Sistema de Inventário - Versão Lista Encadeada
 * 
 * Objetivo: Implementar mochila usando alocação dinâmica (Lista Encadeada).
 * Comparação: Permite inserção/remoção dinâmica sem limite fixo, mas o acesso é sequencial.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do Nó da Lista
typedef struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
    struct Item *prox; // Ponteiro para o próximo item
} Item;

// --- Funções Auxiliares ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removerEnter(char *str) {
    str[strcspn(str, "\n")] = 0;
}

// --- Funções da Lista Encadeada ---

/*
 * Função: inserirItem
 * Cria um novo nó e o insere no início da lista (inserção O(1)).
 */
void inserirItem(Item **cabeca) {
    Item *novoItem = (Item*) malloc(sizeof(Item));
    if (novoItem == NULL) {
        printf(">>> Erro de memória!\n");
        return;
    }

    printf("\n--- Novo Item (Lista) ---\n");
    printf("Nome: ");
    fgets(novoItem->nome, 30, stdin);
    removerEnter(novoItem->nome);

    printf("Tipo: ");
    fgets(novoItem->tipo, 20, stdin);
    removerEnter(novoItem->tipo);

    printf("Quantidade: ");
    scanf("%d", &novoItem->quantidade);
    limparBuffer();

    // Inserção no início
    novoItem->prox = *cabeca;
    *cabeca = novoItem;

    printf(">>> Item cadastrado com sucesso!\n");
}

void listarItens(Item *cabeca) {
    printf("\n=== Inventário (Lista Encadeada) ===\n");
    if (cabeca == NULL) {
        printf("(Vazio)\n");
    } else {
        printf("%-20s | %-15s | %s\n", "Nome", "Tipo", "Qtd");
        printf("------------------------------------------------\n");
        Item *atual = cabeca;
        while (atual != NULL) {
            printf("%-20s | %-15s | %d\n", 
                   atual->nome, atual->tipo, atual->quantidade);
            atual = atual->prox;
        }
    }
    printf("====================================\n");
}

void removerItem(Item **cabeca) {
    char nomeBusca[30];
    printf("\nNome do item para remover: ");
    fgets(nomeBusca, 30, stdin);
    removerEnter(nomeBusca);

    Item *atual = *cabeca;
    Item *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nomeBusca) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        // Achou o item
        if (anterior == NULL) {
            // É o primeiro da lista
            *cabeca = atual->prox;
        } else {
            // Está no meio ou fim
            anterior->prox = atual->prox;
        }
        free(atual);
        printf(">>> Item removido!\n");
    } else {
        printf(">>> Item não encontrado.\n");
    }
}

void buscarItem(Item *cabeca) {
    char nomeBusca[30];
    printf("\nBuscar por nome: ");
    fgets(nomeBusca, 30, stdin);
    removerEnter(nomeBusca);

    Item *atual = cabeca;
    while (atual != NULL) {
        if (strcmp(atual->nome, nomeBusca) == 0) {
            printf("\n>>> Item Encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQtd:  %d\n", 
                   atual->nome, atual->tipo, atual->quantidade);
            return;
        }
        atual = atual->prox;
    }
    printf(">>> Item não encontrado na lista.\n");
}

int main() {
    Item *lista = NULL; // Ponteiro para o início da lista (Head)
    int opcao;

    printf("======= Mochila (Lista Encadeada) =======\n");

    do {
        printf("\n1. Cadastrar Item\n2. Remover Item\n3. Listar Itens\n4. Buscar Item\n0. Sair\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1: inserirItem(&lista); listarItens(lista); break;
            case 2: removerItem(&lista); listarItens(lista); break;
            case 3: listarItens(lista); break;
            case 4: buscarItem(lista); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do Nó (cada música é um nó)
typedef struct No {
    char autor[50];
    char musica[50];
    struct No *prox; // Ponteiro para a próxima música
} No;

// Função auxiliar para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar (insere no início da lista para ser mais rápido/simples)
void cadastrar(No **inicio) {
    No *novo = malloc(sizeof(No)); // Aloca memória para o novo nó
    
    if (novo) {
        printf("Nome do Autor: ");
        fgets(novo->autor, 50, stdin);
        novo->autor[strcspn(novo->autor, "\n")] = 0; // Remove o \n do final

        printf("Nome da Musica: ");
        fgets(novo->musica, 50, stdin);
        novo->musica[strcspn(novo->musica, "\n")] = 0;

        novo->prox = *inicio; // O próximo do novo é o antigo início
        *inicio = novo;       // O novo passa a ser o início da lista
        printf(">>> Musica cadastrada com sucesso!\n");
    } else {
        printf("Erro ao alocar memoria!\n");
    }
}

// Função para excluir uma música pelo nome
void excluir(No **inicio) {
    char nomeBusca[50];
    printf("Digite o nome da musica para excluir: ");
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    No *atual = *inicio;
    No *anterior = NULL;

    // Percorre a lista procurando a música
    while (atual != NULL && strcmp(atual->musica, nomeBusca) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf(">>> Musica nao encontrada.\n");
        return;
    }

    // Se for o primeiro elemento
    if (anterior == NULL) {
        *inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual); // Libera a memória
    printf(">>> Musica excluida!\n");
}

// Função auxiliar para visualizar a lista
void listar(No *no) {
    printf("\n--- Playlist ---\n");
    while (no) {
        printf("Musica: %s | Autor: %s\n", no->musica, no->autor);
        no = no->prox;
    }
    printf("----------------\n");
}

int main() {
    No *lista = NULL; // Lista começa vazia
    int opcao;

    do {
        printf("\nMENU:\n1. Cadastrar Musica\n2. Excluir Musica\n3. Listar Todas\n0. Sair\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o \n deixado pelo scanf

        switch(opcao) {
            case 1: cadastrar(&lista); break;
            case 2: excluir(&lista); break;
            case 3: listar(lista); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

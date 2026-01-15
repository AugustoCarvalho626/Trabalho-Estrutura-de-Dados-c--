/*
 * Nome: Augusto Bento Carvalho
 *
 * Exemplo de Fila (Queue) - Cinema
 *
 * Lógica da Fila (FIFO - First In, First Out):
 * - O primeiro a entrar é o primeiro a sair (ser atendido).
 * - Inserções (Enqueue) acontecem sempre no FINAL.
 * - Remoções (Dequeue) acontecem sempre no INÍCIO.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma Pessoa (Nó da lista encadeada)
typedef struct No {
    char nome[50];
    struct No *prox; // Ponteiro para a próxima pessoa na fila
} No;

// Estrutura de Controle da Fila
// Mantemos ponteiros para o início (para atender) e fim (para inserir)
typedef struct {
    No *inicio;
    No *fim;
} Fila;

// Função auxiliar para limpar buffer (padrão dos seus códigos)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Inicializa a fila como vazia
void inicializarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// ENQUEUE: Adiciona uma pessoa no final da fila
void entrarNaFila(Fila *f) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }

    printf("Nome da pessoa: ");
    fgets(novo->nome, 50, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = 0; // Remove o \n
    novo->prox = NULL; // Como é o último, não tem ninguém depois dele

    // Lógica de inserção
    if (f->fim == NULL) {
        // Se a fila estava vazia, o novo é tanto o início quanto o fim
        f->inicio = novo;
        f->fim = novo;
    } else {
        // Se já tem gente, o atual último aponta para o novo
        f->fim->prox = novo;
        // O novo passa a ser o fim da fila
        f->fim = novo;
    }
    printf(">>> %s entrou na fila!\n", novo->nome);
}

// DEQUEUE: Remove a pessoa do início da fila (Atendimento)
void atenderPessoa(Fila *f) {
    if (f->inicio == NULL) {
        printf("\n>>> A fila esta vazia! Ninguem para atender.\n");
        return;
    }

    No *temp = f->inicio; // Guarda quem será atendido (o primeiro)
    
    printf("\n>>> Atendendo: %s (Ingresso comprado!)\n", temp->nome);

    // O início da fila passa a ser o próximo da lista
    f->inicio = f->inicio->prox;

    // Se a fila ficou vazia após a remoção, precisamos atualizar o fim para NULL
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(temp); // Libera a memória da pessoa atendida
}

// Mostra quem está na fila
void mostrarFila(Fila *f) {
    if (f->inicio == NULL) {
        printf("\nFila do Cinema: (Vazia)\n");
        return;
    }

    printf("\n=== Fila do Cinema ===\n");
    printf("Bilheteria <--- ");
    No *atual = f->inicio;
    while (atual != NULL) {
        printf("[%s] <--- ", atual->nome);
        atual = atual->prox;
    }
    printf("(Fim)\n");
}

int main() {
    Fila filaCinema;
    inicializarFila(&filaCinema);
    int opcao;

    do {
        printf("\n--- CINEMA ---\n");
        printf("1. Chegar pessoa (Entrar na fila)\n");
        printf("2. Atender pessoa (Sair da fila)\n");
        printf("3. Ver fila\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1: entrarNaFila(&filaCinema); break;
            case 2: atenderPessoa(&filaCinema); break;
            case 3: mostrarFila(&filaCinema); break;
            case 0: printf("Fechando bilheteria...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    // Limpeza de memória final (opcional para este exemplo simples, mas boa prática)
    while (filaCinema.inicio != NULL) {
        atenderPessoa(&filaCinema);
    }

    return 0;
}

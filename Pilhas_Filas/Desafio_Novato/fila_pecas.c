// ======================================================================================
// NOME DO PROJETO: Tetris Stack - Fila de Peças
// DESCRIÇÃO:       Simulação da fila de peças futuras de um jogo tipo Tetris,
//                  utilizando uma estrutura de dados de fila circular para gerenciar
//                  a entrada e saída de peças.
// AUTOR:           Augusto Bento Carvalho
// 
// ======================================================================================


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Constantes e Definições de Tipos ---

// Define o tamanho máximo da fila de peças visíveis para o jogador.
#define TAM_FILA 5

/*
 * Representa uma única peça do jogo.
 *
 * Cada peça tem um tipo (nome) e um identificador único (id).
 */
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único da peça
} Peca;

/**
 * Estrutura de controle da Fila Circular.
 *
 * Gerencia o array de peças e os índices de início, fim e o total de elementos.
 * A fila circular permite reutilizar o espaço do array de forma eficiente.
 */
typedef struct {
    Peca itens[TAM_FILA]; // Array que armazena as peças
    int inicio;           // Índice do primeiro elemento da fila
    int fim;              // Índice da próxima posição livre no final da fila
    int total;            // Número de elementos atualmente na fila
} Fila;

// --- Protótipos das Funções ---

void inicializarFila(Fila *f);
Peca gerarPeca();
void enfileirar(Fila *f);
void desenfileirar(Fila *f);
void exibirFila(Fila *f);
void exibirMenu();
void limparBuffer();

// --- Função Principal ---

int main() {
    // Inicializa o gerador de números aleatórios para a criação de peças.
    srand(time(NULL));

    Fila filaDePecas;
    int opcao;

    printf("=== BEM-VINDO AO TETRIS STACK ===\n");

    // 1. Inicializa a fila como vazia.
    inicializarFila(&filaDePecas);

    // 2. Preenche a fila com o número inicial de peças.
    printf("Gerando fila inicial de peças...\n");
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&filaDePecas);
    }

    // Loop principal do jogo
    do {
        printf("\nConfira a seguir seu estado:\n");
        exibirFila(&filaDePecas);
        exibirMenu();

        printf("Escolha sua ação: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o buffer de entrada para evitar erros de leitura

        switch (opcao) {
            case 1:
                // Jogar peça (remover da frente)
                desenfileirar(&filaDePecas);
                break;
            case 2:
                // Adicionar nova peça (inserir no final)
                enfileirar(&filaDePecas);
                break;
            case 0:
                printf("\nEncerrando o jogo. Até a próxima!\n");
                break;
            default:
                printf("\nOpção inválida! Por favor, escolha uma ação válida.\n");
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

/**
 * Inicializa a fila, definindo seus controles para um estado vazio.
 */
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

/**
 * Gera uma nova peça aleatória com um ID único.
 * Retorna uma nova estrutura Peca.
 */
Peca gerarPeca() {
    static int proximoId = 0; // Variável estática para garantir IDs únicos
    Peca novaPeca;
    char tipos[] = "IOTL";

    novaPeca.id = proximoId++; // Atribui o ID atual e o incrementa para a próxima chamada
    novaPeca.nome = tipos[rand() % 4]; // Sorteia um dos 4 tipos de peça

    return novaPeca;
}

/**
 * Adiciona uma nova peça ao final da fila (enqueue).
 * A função verifica se a fila não está cheia antes de inserir.
 */
void enfileirar(Fila *f) {
    if (f->total == TAM_FILA) {
        printf("\nAVISO: A fila de peças está cheia! Jogue uma peça para adicionar outra.\n");
        return;
    }
    Peca nova = gerarPeca();
    f->itens[f->fim] = nova;
    f->fim = (f->fim + 1) % TAM_FILA; // Lógica circular: volta para 0 se chegar ao fim do array
    f->total++;
    printf("\n--> Peça [%c %d] adicionada à fila!\n", nova.nome, nova.id);
  
}

/**
 * Remove a peça da frente da fila (dequeue).
 * A função verifica se a fila não está vazia antes de remover.
 */
void desenfileirar(Fila *f) {
    if (f->total == 0) {
        printf("\nAVISO: A fila de peças está vazia! Não há peças para jogar.\n");
        return;
    }
    Peca pecaJogada = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA; // Lógica circular para o início
    f->total--;
    printf("\n<-- Peça [%c %d] jogada! Removida da frente da fila.\n", pecaJogada.nome, pecaJogada.id);
}

/**
 * Exibe o estado atual de todas as peças na fila.
 */
void exibirFila(Fila *f) {
    printf("\nFila de peças\n");
    if (f->total == 0) {
        printf("[ Vazia ]\n");
        return;
    }

    int i = f->inicio;
    for (int contador = 0; contador < f->total; contador++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % TAM_FILA; // Avança o índice de forma circular
    }
    printf("\n");
}

/**
 * Exibe o menu de opções para o jogador.
 */
void exibirMenu() {
    printf("=============================\n");
    printf("Opções de ação:\n");
    printf("1\tJogar peça (dequeue)\n");
    printf("2\tInserir nova peça (enqueue)\n");
    printf("0\tSair\n");
    printf("=============================\n");
}

/**
 * Limpa o buffer de entrada do teclado. Útil após usar scanf.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
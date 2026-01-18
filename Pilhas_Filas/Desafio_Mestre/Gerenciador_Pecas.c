/*
 * ======================================================================================
 * NOME DO PROJETO: Gerenciador de Peças - Desafio Final (Mestre)
 * DESCRIÇÃO:       Sistema de gerenciamento de peças utilizando Fila Circular e Pilha.
 *                  Implementa mecânicas de jogo, reserva, trocas simples e em bloco,
 *                  com reposição automática de peças na fila.
 * AUTOR:           Augusto Bento Carvalho
 * ======================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Constantes e Definições ---

#define TAM_FILA 5   // Capacidade da Fila Circular
#define TAM_PILHA 3  // Capacidade da Pilha de Reservas

// Estrutura da Peça
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// Estrutura da Fila Circular
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// Estrutura da Pilha
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// --- Protótipos das Funções ---

void inicializarFila(Fila *f);
void inicializarPilha(Pilha *p);
Peca gerarPeca();
void adicionarNovaPeca(Fila *f); // Função interna para manter a fila cheia
void preencherFilaInicial(Fila *f);

// Ações do Usuário
void jogarPeca(Fila *f);
void reservarPeca(Fila *f, Pilha *p);
void usarPecaReserva(Pilha *p);
void trocarPecaAtual(Fila *f, Pilha *p);
void trocaMultipla(Fila *f, Pilha *p);

// Utilitários
void exibirEstado(Fila *f, Pilha *p);
void limparBuffer();

// --- Função Principal ---

int main() {
    srand(time(NULL)); // Semente para números aleatórios

    Fila filaPecas;
    Pilha pilhaReservas;
    int opcao;

    // 1. Inicialização das estruturas
    inicializarFila(&filaPecas);
    inicializarPilha(&pilhaReservas);

    // 2. Preenchimento inicial da fila
    printf("Inicializando sistema...\n");
    preencherFilaInicial(&filaPecas);

    // Loop do Menu Principal
    do {
        exibirEstado(&filaPecas, &pilhaReservas);

        printf("\n=== AÇÕES ESTRATÉGICAS ===\n");
        printf("1. Jogar peça (Dequeue)\n");
        printf("2. Reservar peça (Push da Fila para Pilha)\n");
        printf("3. Usar peça reservada (Pop da Pilha)\n");
        printf("4. Trocar peça atual (Swap: Fila <-> Pilha)\n");
        printf("5. Troca múltipla (Swap 3x3)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                jogarPeca(&filaPecas);
                break;
            case 2:
                reservarPeca(&filaPecas, &pilhaReservas);
                break;
            case 3:
                usarPecaReserva(&pilhaReservas);
                break;
            case 4:
                trocarPecaAtual(&filaPecas, &pilhaReservas);
                break;
            case 5:
                trocaMultipla(&filaPecas, &pilhaReservas);
                break;
            case 0:
                printf("\nEncerrando o gerenciador. Até logo!\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

void inicializarPilha(Pilha *p) {
    p->topo = -1; // Pilha vazia
}

Peca gerarPeca() {
    static int proximoId = 1;
    Peca nova;
    char tipos[] = "IOTL";
    
    nova.id = proximoId++;
    nova.nome = tipos[rand() % 4];
    
    return nova;
}

// Adiciona uma peça automaticamente ao final da fila (se houver espaço)
void adicionarNovaPeca(Fila *f) {
    if (f->total < TAM_FILA) {
        Peca p = gerarPeca();
        f->itens[f->fim] = p;
        f->fim = (f->fim + 1) % TAM_FILA;
        f->total++;
        printf("   -> Nova peça [%c %d] entrou na fila (Auto-Refill).\n", p.nome, p.id);
    }
}

void preencherFilaInicial(Fila *f) {
    for (int i = 0; i < TAM_FILA; i++) {
        adicionarNovaPeca(f);
    }
}

// Ação 1: Jogar (Remove da fila e repõe automaticamente)
void jogarPeca(Fila *f) {
    if (f->total == 0) {
        printf("\n[AVISO] Fila vazia! Nada para jogar.\n");
        return;
    }

    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->total--;

    printf("\n>>> Você JOGOU a peça [%c %d]!\n", p.nome, p.id);

    // Requisito: Gerar nova peça automaticamente
    adicionarNovaPeca(f);
}

// Ação 2: Reservar (Move da fila para a pilha e repõe na fila)
void reservarPeca(Fila *f, Pilha *p) {
    if (f->total == 0) {
        printf("\n[AVISO] Fila vazia! Nada para reservar.\n");
        return;
    }
    if (p->topo >= TAM_PILHA - 1) {
        printf("\n[AVISO] Pilha de reservas CHEIA! Use uma peça ou faça uma troca.\n");
        return;
    }

    // Remove da fila
    Peca pecaMovida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->total--;

    // Adiciona na pilha
    p->topo++;
    p->itens[p->topo] = pecaMovida;

    printf("\n>>> Peça [%c %d] movida para a RESERVA.\n", pecaMovida.nome, pecaMovida.id);

    // Requisito: Gerar nova peça automaticamente na fila
    adicionarNovaPeca(f);
}

// Ação 3: Usar Reserva (Remove do topo da pilha)
void usarPecaReserva(Pilha *p) {
    if (p->topo == -1) {
        printf("\n[AVISO] Não há peças reservadas!\n");
        return;
    }

    Peca pUsada = p->itens[p->topo];
    p->topo--;

    printf("\n>>> Você USOU a peça de reserva [%c %d]!\n", pUsada.nome, pUsada.id);
}

// Ação 4: Trocar Peça Atual (Swap entre início da fila e topo da pilha)
void trocarPecaAtual(Fila *f, Pilha *p) {
    if (f->total == 0) {
        printf("\n[ERRO] Fila vazia, impossível trocar.\n");
        return;
    }
    if (p->topo == -1) {
        printf("\n[ERRO] Pilha vazia, impossível trocar.\n");
        return;
    }

    // Realiza a troca
    Peca temp = f->itens[f->inicio];
    f->itens[f->inicio] = p->itens[p->topo];
    p->itens[p->topo] = temp;

    printf("\n>>> TROCA REALIZADA! A peça da frente agora é [%c %d].\n", 
           f->itens[f->inicio].nome, f->itens[f->inicio].id);
}

// Ação 5: Troca Múltipla (Troca as 3 primeiras da fila com as 3 da pilha)
void trocaMultipla(Fila *f, Pilha *p) {
    // Verifica se a pilha tem 3 peças (índices 0, 1, 2 existem se topo >= 2)
    if (p->topo < 2) {
        printf("\n[ERRO] A pilha precisa ter 3 peças para a troca múltipla.\n");
        return;
    }
    // Verifica se a fila tem pelo menos 3 peças
    if (f->total < 3) {
        printf("\n[ERRO] A fila precisa ter pelo menos 3 peças para a troca múltipla.\n");
        return;
    }

    printf("\n>>> REALIZANDO TROCA MÚLTIPLA (3 PEÇAS) <<<\n");

    // Índices da fila para as 3 primeiras posições
    int idx1 = f->inicio;
    int idx2 = (f->inicio + 1) % TAM_FILA;
    int idx3 = (f->inicio + 2) % TAM_FILA;

    // Índices da pilha (Topo, Topo-1, Topo-2)
    int pIdx1 = p->topo;
    int pIdx2 = p->topo - 1;
    int pIdx3 = p->topo - 2;

    Peca temp;

    // Troca 1 (Frente <-> Topo)
    temp = f->itens[idx1];
    f->itens[idx1] = p->itens[pIdx1];
    p->itens[pIdx1] = temp;

    // Troca 2
    temp = f->itens[idx2];
    f->itens[idx2] = p->itens[pIdx2];
    p->itens[pIdx2] = temp;

    // Troca 3
    temp = f->itens[idx3];
    f->itens[idx3] = p->itens[pIdx3];
    p->itens[pIdx3] = temp;

    printf(">>> Troca em bloco concluída com sucesso!\n");
}

void exibirEstado(Fila *f, Pilha *p) {
    printf("\n========================================\n");
    
    // Exibir Fila
    printf("FILA (Próximas): ");
    if (f->total == 0) printf("[ Vazia ]");
    else {
        int idx = f->inicio;
        for (int i = 0; i < f->total; i++) {
            printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
            idx = (idx + 1) % TAM_FILA;
        }
    }
    printf("\n");

    // Exibir Pilha
    printf("PILHA (Reserva): ");
    if (p->topo == -1) printf("[ Vazia ]");
    else {
        // Mostra da base para o topo ou topo para base? 
        // Visualmente, pilha costuma ser mostrada com o topo acessível.
        // Vamos mostrar: [Base] ... [Topo] <---
        for (int i = 0; i <= p->topo; i++) {
            printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
        }
        printf("<--- TOPO");
    }
    printf("\n========================================\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct {
    char nome[30];
    int idade;
} Pessoa;

typedef struct {
    Pessoa dados[MAX];
    int inicio, fim;
} fila;

typedef struct {
    Pessoa dados[MAX];
    int topo;
} pilha;

void inicializa_fila(fila *f) {
    f->inicio = 0;
    f->fim = 0;
}

void inicializa_pilha(pilha *p) {
    p->topo = -1;
}

void insere_fila(fila *f, Pessoa p) {
    if (f->fim < MAX) {
        f->dados[f->fim++] = p;
    }
}

Pessoa remover_fila(fila *f) {
    return f->dados[f->inicio++];
}

void push(pilha *p, Pessoa pes) {
    if (p->topo < MAX - 1) {
        p->dados[++p->topo] = pes;
    }
}

Pessoa pop(pilha *p) {
    return p->dados[p->topo--];
}

void exibirfila(fila *f) {
    for (int i = f->inicio; i < f->fim; i++) {
        printf("Nome: %s, Idade: %d\n", f->dados[i].nome, f->dados[i].idade);
    }
}


int main() {

    fila filaoriginal, filainvertida;
    pilha auxiliar;
    
    inicializa_fila(&filaoriginal);
    inicializa_fila(&filainvertida);
    inicializa_pilha(&auxiliar);

    Pessoa pessoas[] = {
        {"João", 25},
        {"Maria", 30},
        {"Pedro", 22},
        {"Ana", 28}};

    for (int i = 0; i < 4; i++) {
        insere_fila(&filaoriginal, pessoas[i]);
    }

    printf("Fila Original:\n");
    exibirfila(&filaoriginal);    

    while (filaoriginal.inicio < filaoriginal.fim) {
        push(&auxiliar, remover_fila(&filaoriginal));
    }

    while (auxiliar.topo >= 0) {
        insere_fila(&filainvertida, pop(&auxiliar));
    }

    printf("Fila invertida:\n");
    exibirfila(&filainvertida);


    return 0;

}
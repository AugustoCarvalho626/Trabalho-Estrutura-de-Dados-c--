#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    char nome[50];
    int idade;
} Pessoa;

typedef struct {
    Pessoa itens [MAX];
    int topo;
} pilha;

void inicializar(pilha *p) {
    p->topo = -1;
}

int vazia(pilha *p) {
    return (p->topo == -1);
}

int cheia(pilha *p) {
    return (p->topo == MAX - 1);
}

void push(pilha *p, Pessoa nova) {
    if (cheia(p)) {
        printf("A pilha está cheia!. Não é possível inserir.\n");
        return;
    }
        p->topo++;
        p->itens[p->topo] = nova;
    }

void pop(pilha *p, Pessoa *removida) {
    if (vazia(p)) {
        printf("A pilha está vazia!. Não é possível remover.\n");
        return;
    }
    *removida = p->itens[p->topo];
    p->topo--;
}

void peek(pilha *p, Pessoa *visualizada) {
    if (vazia(p)) {
        printf("A pilha está vazia!. Não é possível visualizar.\n");
        return;
    }
    *visualizada = p->itens[p->topo];
}

void imprimir(pilha *p) {
    if (vazia(p)) {
        printf("A pilha está vazia!. Não é possível imprimir.\n");
        return;
    }
    printf("Pilha:\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%s, %d]\n", p->itens[i].nome, p->itens[i].idade);
    }
    printf("\n");       
}


int main() {

    pilha p;
    inicializar(&p);

    Pessoa a = {"João", 25};
    Pessoa b = {"Maria", 30};
    Pessoa c = {"Pedro", 28};

    push(&p, a);
    push(&p, b);
    push(&p, c);

    imprimir(&p);

    Pessoa removida;
    pop(&p, &removida);
    printf("Pessoa removida: [%s, %d]\n", removida.nome, removida.idade);

    imprimir(&p);

    Pessoa topo;
    peek(&p, &topo);
    printf("Topo da pilha: [%s, %d]\n", topo.nome, topo.idade);

    return 0;
}


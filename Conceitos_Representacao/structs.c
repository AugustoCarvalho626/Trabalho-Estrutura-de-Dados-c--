#include <stdio.h>

typedef struct 
{
    char nome[50];
    int idade;
    float media;
} Aluno;

int main(){

    // cliando e inicializando uma variável do tipo Aluno
    Aluno aluno1 = {"joão", 20, 8.5};

    // Acessando os dados com o operador
    printf("Aluno: %s\n", aluno1.nome);
    printf("Idade: %d\n", aluno1.idade);
    printf("Média: %.2f\n", aluno1.media);

    return 0;

}


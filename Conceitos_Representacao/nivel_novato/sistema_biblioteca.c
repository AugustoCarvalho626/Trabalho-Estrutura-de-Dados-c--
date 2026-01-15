/*======================================================================
    Prática: Sistema de Biblioteca - Parte 1

    Objetivo Desta Parte:
    Implementar o cadastro e a listagem de livros usando um array estático.
    Foco em structs, entrada/saída de dados e organização básica.

======================================================================*/


#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

// --- Constantes Globais ---
#define max_livros 50
#define tam_string 100

// --- Definição da Estrutura (Struct) ---
struct livro {
    char nome[tam_string];
    char autor[tam_string];
    char editora[tam_string];
    int edicao;    
};

// --- Função para limpar o buffer de entrada ---
void limparbufferentrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    }
    
// --- Fumção principal (main) ---
int main() {
    struct livro biblioteca[max_livros];
    int totallivros = 0;
    int opcao;
    
    // --- Laço principal do menu ---
    do {

        // Exibe o menu de opções.
        printf("=====================================\n");
        printf("     BIBLIOTECA - PARTE 1\n");
        printf("=====================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("0 - Sair\n");
        printf("-------------------------------------\n");
        printf("Escolha uma opção: ");
    
     // lê a opção do usuário.
    scanf("%d", &opcao);
    limparbufferentrada();  // LImpa o '\n' deixado pelo scanf.


     // --- Processamento da Opção ---
    switch (opcao)
    {
    case 1:   // Cadastro de livro
        printf("--- Cadastro de novo livro: ---\n\n");

        if (totallivros < max_livros) {
            printf("Digite o nome do livro: ");
            fgets (biblioteca[totallivros].nome, tam_string, stdin);

            printf("Digite o autor: ");
            fgets(biblioteca[totallivros].autor, tam_string, stdin);

            printf("Digite a editora: ");
            fgets(biblioteca[totallivros].editora, tam_string, stdin);

            biblioteca[totallivros].nome[strcspn(biblioteca[totallivros].nome, "\n")] = '\0';
            biblioteca[totallivros].autor[strcspn(biblioteca[totallivros].autor, "\n")] = '\0';
            biblioteca[totallivros].editora[strcspn(biblioteca[totallivros].editora, "\n")] = '\0';

            printf("Digite a edição: ");
            scanf("%d", &biblioteca[totallivros].edicao);
            limparbufferentrada();

            totallivros++;

            printf("\n Livro cadastrado com sucesso!\n");
        } else {
            printf("Biblioteca cheia! Não é possível cadastrar mais livros.\n");
        }

        printf("\n Precione enter para continuar...");
        getchar(); // pausa para o usuário ler a mensagem antes de voltar ao menu.
        break;
    
    case 2: 
        printf("--- Lista de livros cadastrados ---\n\n");

        if (totallivros == 0) {
            printf("Nenhum livro cadastrado ainda. \n");
        } else {
            for (int i = 0; i < totallivros; i++) {
                printf("------------------------------------------------\n");
                printf("Livro %d\n", i + 1);
                printf("Nome: %s \n", biblioteca[i].nome);
                printf("Autor: %s\n", biblioteca[i].autor);
                printf("Editora: %s\n", biblioteca[i].editora);
                printf("Edição: %d\n", biblioteca[i].edicao);
            }
            printf("---------------------------------------------------\n");
        }

    // A pausa é crucial para que o usuário veja a lista antes do próximo loop limpar a tela.

    printf("\n Pressione enter para continuar...");
    getchar();
    break;
    
    case 0:  // Sair
        printf("\n Saindo do Sistema...\n");
        break;

        default:  // Opção inválida
        printf("\n Opção invalida! Tente novamente.\n");
        printf("\n Pressione Enter para continuar...");
        getchar();
        break;
    }

    } while (opcao !=0);
    

return 0; 
    }
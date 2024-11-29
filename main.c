#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filmes.h"
#include <locale.h>


#define CAMINHO_DIRETORIO "C:\\MeusFilmes"

int main(void) {
    setlocale(LC_ALL, "pt-BR");
    criarDiretorio(CAMINHO_DIRETORIO); //Cria o diretorio

    exibirTelaLogin();
    return 0

    Filme filmes[MAX_FILMES];
    int numfilmes = 0;
    int opcao;

    //Carrega os filmes do arquivo no começo
    carregarFilme(filmes, &numfilmes);

    listarFilme(filmes, numfilmes);

    do {
        printf("MENU\n***Meus Filmes***\n");
        printf("1. Registrar Filme\n");
        printf("2. Remover Filme\n");
        printf("3. Listar Filmes\n");
        printf("4. Abrir arquivos de filmes\n");
        printf("5. Sair\n");
        printf("\nEscolha uma das opções, por favor!!\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                registrarFilme(filmes, &numfilmes);
            break;
            case 2:
                removerFilme(filmes, &numfilmes);
            break;
            case 3:
                listarFilme(filmes, numfilmes);
            break;
            case 4:
                //Abre o arquivo "filmes.txt" no bloco de notas
#ifdef _WIN32
                system("notepad C:\\MeusFilmes\\filmes.txt");
#else
            printf("Esse sistema operacional não a abertura automática do bloco de notas");
#endif
            break;
            case 5:
                printf("SAINDO...\n");
            default:
                printf("Escolha uma das opções válidas!!");
        }
    }
    while (opcao != 5);
    return 0;
}

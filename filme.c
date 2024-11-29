//Arquivo que armazena as funcões do código

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filmes.h"
#include <direct.h>
#include <errno.h>


// Defina o caminho do arquivo
#define CAMINHO_ARQUIVO "C:\\MeusFilmes\\filmes.txt" // Caminho padrão do arquivo
// Função para criar o diretório se ele não existir

void criarDiretorio(const char *caminho) {
#ifdef _WIN32
    if (_mkdir(caminho) != 0) {
        if (errno != EEXIST) {
            perror("Erro ao criar diretório");
        }
    }
#else
    if (mkdir(caminho, 0777) != 0) {
        if (errno != EEXIST) {
            perror("Erro ao criar diretório");
        }
    }
#endif
}

void registrarFilme(Filme filmes[], int *numFilmes) {
    if (*numFilmes >= MAX_FILMES) {
        printf("O limite de filmes foi atingido\n");
        return;
    }

    Filme novoFilme;
    novoFilme.id = *numFilmes + 1;

    // Limpa o buffer antes de começar a ler strings
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite o título do filme, por favor: \n");
    fgets(novoFilme.titulo, sizeof(novoFilme.titulo), stdin);
    novoFilme.titulo[strcspn(novoFilme.titulo, "\n")] = '\0';

    printf("Digite o nome do diretor do filme, por favor: \n");
    fgets(novoFilme.diretor, sizeof(novoFilme.diretor), stdin);
    novoFilme.diretor[strcspn(novoFilme.diretor, "\n")] = '\0';

    printf("Digite o ano de lançamento do filme, por favor: \n");
    scanf("%d", &novoFilme.anoLancamento);

    filmes[(*numFilmes)++] = novoFilme;
    salvarFilme(novoFilme);
    printf("Filme registrado com sucesso!\n");
}



void removerFilme(Filme filmes[], int *numFilmes) {
    int id;
    printf("Digite o ID do filme que deseja remover: \n");
    scanf("%d", &id);

    int encontrado = 0;
    for (int i = 0; i < *numFilmes; i++) {
        if (filmes[i].id == id) {
            encontrado = 1;
            // Move todos os filmes após o removido uma posição para trás
            for (int j = i; j < *numFilmes - 1; j++) {
                filmes[j] = filmes[j + 1];
            }
            (*numFilmes)--;
            break;
        }
    }

    if (!encontrado) {
        printf("Filme não encontrado!\n");
        return;
    }

    // Ajustar IDs dos filmes restantes para manter a sequência
    for (int i = 0; i < *numFilmes; i++) {
        filmes[i].id = i + 1;
    }

    // Reescrever o arquivo sem o filme removido
    FILE *arquivo = fopen(CAMINHO_ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para reescrita!\n");
        return;
    }

    for (int i = 0; i < *numFilmes; i++) {
        fprintf(arquivo, "ID: %d\nTítulo: %s\nDiretor: %s\nAno de Lançamento: %d\n\n",
                filmes[i].id, filmes[i].titulo, filmes[i].diretor, filmes[i].anoLancamento);
    }

    fclose(arquivo);
    printf("Filme removido e arquivo atualizado com sucesso!\n");
}




void listarFilme(Filme filmes[], int numFilmes) {
    for (int i = 0; i < numFilmes; i++) {
        printf("ID: %d\n", filmes[i].id);
        printf("Título: %s\n", filmes[i].titulo);
        printf("Diretor: %s\n", filmes[i].diretor);
        printf("Ano: %d\n\n", filmes[i].anoLancamento);
    }
}

void salvarFilme(Filme filme) {
    FILE *arquivo = fopen(CAMINHO_ARQUIVO, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!!\n");
        return;
    }

    fprintf(arquivo, "ID: %d\nTítulo: %s\nDiretor: %s\n Ano de Lançamento: %d\n\n", filme.id, filme.titulo,filme.diretor, filme.anoLancamento);

    fclose(arquivo);
}

void carregarFilme(Filme filmes[], int *numFilmes) {
    FILE *arquivo = fopen(CAMINHO_ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo encontrado!!\n");
        return;
    }
    *numFilmes = 0;
    while (fscanf(arquivo, "ID: %d\n", &filmes[*numFilmes].id) != EOF) {
        fgets(filmes[*numFilmes].titulo, sizeof(filmes[*numFilmes].titulo), arquivo);
        filmes[*numFilmes].titulo[strcspn(filmes[*numFilmes].titulo, "\n")] = '\0';

        fgets(filmes[*numFilmes].diretor, sizeof(filmes[*numFilmes].diretor), arquivo);
        filmes[*numFilmes].diretor[strcspn(filmes[*numFilmes].diretor, "\n")] = '\0';

        fscanf(arquivo, "Ano de Lançamento: %d\n\n", &filmes[*numFilmes].anoLancamento);
        (*numFilmes)++;
    }
    fclose(arquivo);
}
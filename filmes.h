#ifndef FILMES_H
#define FILMES_H

#define MAX_FILMES 100

typedef struct  {
    int id;
    char titulo[100];
    char diretor[100];
    int anoLancamento;
}Filme;


void criarDiretorio(const char *caminho);
void registrarFilme(Filme filmes[], int *numFilmes);
void removerFilme(Filme filmes[], int *numFilmes);
void listarFilme(Filme filmes[], int numFilmes);
void salvarFilme(Filme filme);
void carregarFilme(Filme filmes[], int *numFilmes);
void exibirTelaLogin;

#endif //FILMES_H

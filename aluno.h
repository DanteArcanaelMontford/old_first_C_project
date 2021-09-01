#ifndef ALUNO_H_INCLUDED
#define ALUNO_H_INCLUDED

/** Definição do tipo Aluno **/
typedef struct aluno Aluno;

/** Funcao que recebe arquivo de entrada e cria uma saida com as estatisticas dos alunos **/
void aluno_estatistica(FILE *entrada, char *nomeEntrada, FILE *saida, char *nomeSaida);

/** Função para/home/omnis/Downloads/projeto2/aluno.h capturar os dados do arquivo e colocá-los em um vetor do tipo struct aluno **/
Aluno *aluno_captura(FILE *f, char *nomeArquivo,int linhas);

/** Contador de linhas do arquivo para suport na função de captura **/
int aluno_contaLinhas(FILE *f, char *nomeArquivo);

/** Função quicksort para ordenar o vetor de alunos **/
void quickSort(Aluno *vet, int inicio, int fim);

/** Busca binária: faz busca dos alunos pelo nome **/
int aluno_bSearch(Aluno *vet, int n, char *nomeAluno);

/** Lista alunos que escolheram Engenharia da Computação **/
void aluno_computacaoLista(Aluno *vet, int linhas);

/** Lista alunos que escolhem Engenharia de Software **/
void aluno_softwareLista(Aluno *vet, int linhas);

/** Outra função de busca por nome **/
int aluno_busca(Aluno *vet, int linhas, char *nome);

/** Função para gerar o menu de opções **/
void menu(Aluno *vet, int linhas);


#endif // ALUNO_H_INCLUDED

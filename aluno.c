#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

/**Struct aluno para facilitar manipulação dos dados**/
struct aluno
{
    char nome[51];
    char sexo;
    int ano;
    char inst[8];
    char curso[51];

};

/** Contador de linhas do arquivo para suport na função de captura **/
int aluno_contaLinhas(FILE *f, char *nomeArquivo)
{

    char c;
    int qtddLinhas = 0;
    while((c = fgetc(f)) != EOF)
    {
        if(c == '\n') qtddLinhas++;
    }
    return(qtddLinhas);
}

/** Funcao que recebe arquivo de entrada e cria uma saida com as estatisticas dos alunos **/
void aluno_estatistica(FILE *entrada, char *nomeEntrada, FILE *saida, char *nomeSaida)
{
    entrada = fopen(nomeEntrada, "rt");
    saida = fopen(nomeSaida, "wt");
    Aluno a;

    float total;
    float publica = 0;
    float masculino = 0;
    float feminino = 0;
    float privada = 0;
    float software = 0;
    float computacao = 0;

    float p1, p2, p3, p4, p5, p6;

    for(total = 0; fscanf(entrada, "%[^\t] %c %i %s %[^\n]", a.nome, &a.sexo, &a.ano, a.inst, a.curso) == 5; total++)
    {
        if(strcmp(a.inst, "publica") == 0) publica++;
        if(strcmp(a.inst, "privada") == 0) privada++;
        if(a.sexo == 'M') masculino++;
        if(a.sexo == 'F') feminino++;
        if(strcmp(a.curso, "Engenharia de Software") == 0) software++;
        if(strcmp(a.curso, "Engenharia de Computacao") == 0) computacao++;

    }

    p1 = (publica / total) * 100;
    p2 = (privada / total) * 100;
    p3 = (feminino / total) * 100;
    p4 = (masculino / total) * 100;
    p5 = (software / total) * 100;
    p6 = (computacao / total) * 100;

    fprintf(saida, "Vieram de escola publica: %.2f%%\n", p1);
    fprintf(saida, "Vieram de escola privada: %.2f%%\n", p2);
    fprintf(saida, "Sexo feminino: %.2f%%\n", p3);
    fprintf(saida, "Sexo masculino: %.2f%%\n", p4);
    fprintf(saida, "Escolheu Engenharia de Software: %.2f%%\n", p5);
    fprintf(saida, "Escolheu Engenharia de computacao: %.2f%%\n", p6);
}

/** Função para capturar os dados do arquivo e colocá-los em um vetor do tipo struct aluno **/
Aluno *aluno_captura(FILE *f, char *nomeArquivo,int linhas)
{
    f = fopen(nomeArquivo, "rt");

    Aluno *vet = (Aluno*) malloc(linhas * sizeof(Aluno));
    int i;
    for(i = 0; i < linhas; i++)
    {
        fscanf(f, "%[^\t] %c %i %s %[^\n]", vet[i].nome, &vet[i].sexo, &vet[i].ano, vet[i].inst, vet[i].curso);
    }

    return(vet);
}

/***Funcoes para testes iniciais de leitura e escrita dos arquivos***/
void printLinha(Aluno *aluno)
{
        printf("%s %c %i %s %s\n", aluno->nome, aluno->sexo, aluno->ano, aluno->inst, aluno->curso);
}

void aluno_printLinhas(Aluno *vet, int n)
{
    int i;
    for(i = 0; i < n; i++)
        printLinha(&vet[i]);
        //printf("%s %c %i %s %s\n", vet[i].nome, vet[i].sexo, vet[i].ano, vet[i].inst, vet[i].curso);
}
/************************************************************************/

/** Funcao de suport para quicksort **/
void swapAluno(Aluno *a1, Aluno *a2)
{
    Aluno aux = *a1;
    *a1 = *a2;
    *a2 = aux;
}

/** Oredenador bolha, alternativa ao ordenador rapido para pequena quantidade de alunos **/
void bubbleSort(Aluno *vet, int n)
{
    int i, j;
    for(i = n - 1; i >= 0; i--)
    {
        for(j = 0; j < n; j++)
        {
            if(strcmp(vet[j + 1].nome, vet[j].nome) < 0)
                swapAluno(&vet[j+1], &vet[j]);
        }
    }
}

/** Função de partição para quicksort: retorna posição do pivô **/
int partition(Aluno *vet, int inicio, int fim)
{
    char *pivot = (char*) malloc(strlen(vet[fim].nome) + 1 * sizeof(char));
    strcpy(pivot, vet[fim].nome);
    int i;
    int pivotPosition = inicio;

    for(i = inicio; i < fim; i++)
    {
        if(strcmp(vet[i].nome, pivot) < 0)
        {
            swapAluno(&vet[i], &vet[pivotPosition]);
            pivotPosition++;
        }
    }

    swapAluno(&vet[fim], &vet[pivotPosition]);

    return(pivotPosition);
}

/** Função quicksort para ordenar o vetor de alunos **/
void quickSort(Aluno *vet, int inicio, int fim)
{
    if(inicio < fim)
    {
        int pivot = partition(vet, inicio, fim);
        quickSort(vet, inicio, pivot - 1);
        quickSort(vet, pivot + 1, fim);
    }
}

/** Busca binária: faz busca dos alunos pelo nome **/
int aluno_bSearch(Aluno *vet, int n, char *nomeAluno)
{
    int inicio = 0;
    int fim = n - 1;
    int meio;

    while(inicio <= fim)
    {
        meio = (inicio + fim) / 2;
        if(strcmp(nomeAluno, vet[meio].nome) == 0)
            return(meio);
        else
            if(strcmp(nomeAluno, vet[meio].nome)  == -1)
                fim = meio - 1;
            else
                inicio = meio + 1;
    }
    printf("Posicao = %i\n", meio);
    return(-1);
}

/** Lista alunos que escolheram Engenharia da Computação **/
void aluno_computacaoLista(Aluno *vet, int linhas)
{
    int i;
    char nome[51];
    system("clear");

    printf("**********************Optaram por Egenharia de Computacao***********************\n");
    for(i = 0; i < linhas; i++)
    {
        sscanf(vet[i].curso, "%[^\n]", nome);
        if(strstr(nome, "Engenharia de Computacao"))
            printf("%s\n", vet[i].nome);
    }
    printf("\n");
    printf("********************************************************************************\n");
}

/** Lista alunos que escolhem Engenharia de Software **/
void aluno_softwareLista(Aluno *vet, int linhas)
{
    int i;
    char nome[51];
    system("clear");

    printf("**********************Optaram por Egenharia de Software*************************\n");
    for(i = 0; i < linhas; i++)
    {
        sscanf(vet[i].curso, "%[^\n]", nome);
        if(strstr(nome, "Engenharia de Software"))
            printf("%s\n", vet[i].nome);
    }
    printf("\n");
    printf("********************************************************************************\n");
}

/** Outra função de busca por nome **/
int aluno_busca(Aluno *vet, int linhas, char *nome)
{
    int i;
    system("clear");

    for(i = 0; i < linhas; i++)
    {
        if(strstr(vet[i].nome, nome))
        {
            printf("********************************************************************************\n");
            printf("%s\n\nSexo: %c\nAno: %i\nTipo da instituicao: %s\nCurso escolhido: %s\n", vet[i].nome, vet[i].sexo, vet[i].ano, vet[i].inst, vet[i].curso);
            printf("********************************************************************************\n");
        }
    }

    return(0);
}

/** Função para gerar o menu de opções **/
void menu(Aluno *vet, int linhas)
{
    char opcao;

    do
    {

        printf("*****************************************\n");
        printf("(1)->[Lista alunos de E. de Software]\n(2)->[Lista alunos de E. de Computacao]\n(3)->[Buscar um aluno por nome]\n(q/Q)->[Sair]\n");
        printf("*****************************************\n");
        printf("Qual sua escolha: ");
        scanf(" %c", &opcao);

        if(opcao == '1') aluno_softwareLista(vet, linhas);

        else if(opcao == '2') aluno_computacaoLista(vet, linhas);

        else if(opcao == '3')
        {
            char nome[51];
            printf("Qual nome do aluno buscado: ");
            scanf("%s", nome);
            aluno_busca(vet, linhas, nome);
        }

    }while(opcao != 'q' && opcao != 'Q');
}


#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"


int main(void)
{
    /** Abertura do arquivo de entrada na main **/
    FILE *entrada = fopen("alunos.txt", "rt");
    if(!entrada) exit(1);

    /** Abertura do arquivo de saída na main **/
    FILE *saida = fopen("saida.txt", "wt");
    if(!saida) exit(1);

    /** Chamada da função que gera arquivo de saída com as estatísticas dos alunos **/
    aluno_estatistica(entrada, "alunos.txt", saida, "saida.txt");

    /** Chamada da função que conta as linhas do arquivo **/
    int linhas = aluno_contaLinhas(entrada, "alunos.txt");

    /** Chamada da função de captura dos dados do arquivo para colocar em um vetor **/
    Aluno *vet = aluno_captura(entrada, "alunos.txt",linhas);

    /** Chamada da função geradora do menu **/
    menu(vet, linhas);

    /** Fechamento dos arquivos de entrada e saída **/
    fclose(entrada);
    fclose(saida);
    return 0;
}




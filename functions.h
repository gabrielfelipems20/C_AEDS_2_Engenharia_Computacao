#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#define TRUE 1 //Define a constante TRUE
#define FALSE 0 //Define a constante FALSE
#define NOTA_MINIMA 6.0 //Define a constante NOTA_MINIMA


typedef struct{//Define a struct do tipo ALUNO
    int id, status;
    char nome[30];
    float nota1, nota2, nota3, media;
}ALUNO;

//Cabeçalho das funçoes usadas no programa
void menu();
int nLinhas();
ALUNO *alocaAlunos(ALUNO *aluno, int numero_de_linhas);
ALUNO *bubbleSort(ALUNO *aluno, int numero_de_linhas);
void imprimeTodos(ALUNO *aluno, int numero_de_linhas);
void imprimeNomes(ALUNO *aluno, int numero_de_linhas);
void imprimeNomes_notas(ALUNO * aluno, int numero_de_linhas);
void buscaAluno(ALUNO *aluno, int numero_de_linhas);
void maior(ALUNO *aluno, int numero_de_linhas);
void menor(ALUNO *aluno, int numero_de_linhas);
void imprimeStatus(ALUNO *alunos, int numero_de_linhas);

#endif

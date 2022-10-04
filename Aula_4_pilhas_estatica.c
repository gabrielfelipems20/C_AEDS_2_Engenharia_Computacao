#include <stdlib.h>
#include <stdio.h>
#define MAX 10



typedef struct {
    int vetor[MAX];
    unsigned int topo;
}PILHA;

PILHA* criaPilha();
void liberaPilha(PILHA* pilha);
int push(PILHA* pilha, int valor);
int pull(PILHA* pilha, int* valor);
int estaVazia(PILHA* pilha);
int estaCheia(PILHA* pilha);



int main(void){

    PILHA *pilha_1;
    pilha_1 = criaPilha();


    int aux;
    int numero_int;
    int check1;
    int check2;
    int valor_removido;

    do{

        printf("\n-----TRABALHANDO COM PILHAS-----\n");
        LABEL_1:
        printf("\n1 PARA EMPILHAR UM DADO DO TIPO INT\n");
        printf("\n2 PARA DESEMPILHAR UM DADO INSERIDO\n");
        printf("\n0 PARA SAIR\n");
        scanf("%d", &aux);
        

        switch (aux){
            case 0:
                liberaPilha(pilha_1);
                break;
            case 1:
                printf("\nDIGITE UM NUMERO INTEIRO: \n");
                scanf("%d", &numero_int);

                check1 = push(pilha_1, numero_int);
                if (check1 == 1){
                    printf("\nNUMERO %d EMPILHADO NA POSICAO %d DA PILHA\n", numero_int, pilha_1->topo);
                } else {
                    check2 = estaCheia(pilha_1);
                    if (check2 == 1){
                        printf("\nA PILHA ESTA CHEIA NAO E POSSIVEL EMPILHAR MAIS DADOS\n");
                    } else {
                        printf("\nA PILHA NAO ESTA CHEIA, OUTRO ERRO ACONTECEU\n");
                    }
                }
                break;
            case 2:
                    check1 = pull(pilha_1, &valor_removido);
                if (check1 == 1){
                    printf("\nNUMERO %d FOI DESEMPILHADO\n", numero_int);
                } else {
                    check2 = estaVazia(pilha_1);
                    if (check2 == 1){
                        printf("\nA PILHA ESTA VAZIA NAO E POSSIVEL DESEMPILHAR MAIS DADOS\n");
                    } else {
                        printf("\nA PILHA NAO ESTA VAZIA, OUTRO ERRO ACONTECEU\n");
                    }
                }
                break;
            default:
                printf("\nOPCAO INVALIDA\n");
                goto LABEL_1;
        }

    } while (aux != 0);
}



PILHA* criaPilha(){

    PILHA *pilha;
    pilha = (PILHA*)malloc(sizeof(PILHA));

    if(pilha == NULL){
        return NULL;     // ponteiros vazios tem valor NULL
    } else {
        pilha->topo = 0;
        return pilha;
    }
}

void liberaPilha(PILHA* pilha){

    free(pilha);
}

int push(PILHA* pilha, int valor){

    if(pilha->topo < MAX){
        pilha->vetor[pilha->topo] = valor;
        pilha->topo++;
        return 1;
    } else {
        return 0;
    }
}

int pull(PILHA* pilha, int* valor){

    if(pilha->topo != 0){
        valor = pilha->vetor[pilha->topo];
        pilha->topo--;
        return 1;
    } else {
        return 0;
    }
}

int estaVazia(PILHA* pilha){

    if (pilha->topo == 0){
        return 1;
    } else {
        return 0;
    }
}

int estaCheia(PILHA* pilha){
    if (pilha->topo == MAX - 1){
        return 1;
    } else {
        return 0;
    }
}

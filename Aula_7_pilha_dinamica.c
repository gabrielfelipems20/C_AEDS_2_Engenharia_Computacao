#include <stdio.h>
#include <stdlib.h>

// Struct dos nós da pilha
typedef struct elemento{
    int info;
    struct elemento *link;
}ELEMENTO;

//Struct da pilha
typedef struct pilha{
    struct elemento *topo_pilha;
    int lenght;
}PILHA;

//Cabeçalho de funções
int push(PILHA *pilha, int valor); //Empilha
int pop(PILHA *pilha, int *valor); //Desempilha
int popAll(PILHA *pilha); //Desempilha todos
int isEmpty(PILHA *pilha); // Pilha vazia


/*--------------------------------------------MAIN--------------------------------------------------*/


int main(void){

    PILHA pilha1;
    pilha1.topo_pilha = NULL;

    //Inserindo elementos a, b, e c na pilha.

    int a = push(&pilha1, 30);
    if(a){
       printf("ELEMENTO A INSERIDO\nNUMERO %d\n", pilha1.topo_pilha->info); // Elemento do topo
    } else {
        printf("ERRO AO INSERIR ELEMENTO");
    }

    int b = push(&pilha1, 55);
    if(b){
        printf("ELEMENTO B INSERIDO\nNUMERO %d\n", pilha1.topo_pilha->info); // Elemento do topo
    } else {
        printf("ERRO AO INSERIR ELEMENTO");
    }

    int c = push(&pilha1, 100);
    if(c){
       printf("ELEMENTO C INSERIDO\nNUMERO %d\n", pilha1.topo_pilha->info); // Elemento do topo
    } else {
        printf("ERRO AO INSERIR ELEMENTO");
    }

    printf("\nTAMANHO DA PILHA: %d\n", pilha1.lenght);

    //Remove o elemento do topo

    int n_removido;
    int d = pop(&pilha1, &n_removido);
    if(d){
        printf("ELEMENTO %d REMOVIDO\n", n_removido);
        printf("TOPO AGORA PASSA A SER %d\n", pilha1.topo_pilha->info);
    } else {
        printf("ERRO AO REMOVER ELEMENTO\n");
    }

    printf("\nTAMANHO DA PILHA: %d\n", pilha1.lenght);


    // Exclui a pilha

    int l = popAll(&pilha1);
    if (l){
        printf("PILHA EXCLUIDA\n");
    } else {
        printf("ERRO AO EXCLUIR A PILHA");
    }
  
    int v = isEmpty(&pilha1);
     if (v){
        printf("PILHA VAZIA\n");
    } else {
        printf("PILHA COM ELEMENTOS\n");
    }

    return 0;
}


/*--------------------------------------------FUNÇÕES----------------------------------------------*/


int push(PILHA *pilha, int valor){

    ELEMENTO *novo_elemento = (ELEMENTO*)malloc(sizeof(ELEMENTO));
    novo_elemento->info = valor; // Novo elemento recebe valor

    if(isEmpty(pilha)){ // Pilha vazia
        pilha->topo_pilha = novo_elemento; // Topo da pilha recebe o novo elemento
        novo_elemento->link = NULL;
        pilha->lenght = 1; //Aumenta o tamanho da pilha
        if (!isEmpty(pilha)){ //Se foi inserido elemento na pilha
            return 1; 
        } else {
            return 0;
        }

    } else { // Pilha ja possui elementos
        novo_elemento->link = pilha->topo_pilha; //Link do novo elemento aponta para o elemento anterior
        pilha->topo_pilha = novo_elemento; // Topo da pilha recebe o endereço do novo elemento
        pilha->lenght++; //Aumenta tamanho da pilha
        if (novo_elemento->link != pilha->topo_pilha){ //se o endereço do topo e do elemento sao diferentes
            return 1;
        } else {
            return 0;
        }
    }
}

int pop(PILHA *pilha, int *valor){

    PILHA aux;
    
    if(!isEmpty(pilha)){ // Se a pilha tem elementos
        aux.topo_pilha = pilha->topo_pilha; //Aux aponta para o topo a ser removido
        *valor = pilha->topo_pilha->info; // Variavel valor recebe o dado removido
        pilha->topo_pilha = pilha->topo_pilha->link; // Topo aponta para o elemento anterior
        if (aux.topo_pilha != pilha->topo_pilha){ //Se o topo aponta para elemento anterior
            free(aux.topo_pilha); //Libero memoria do elemento anterior
            pilha->lenght--;
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int popAll(PILHA *pilha){

    int valor;

    if(!isEmpty(pilha)){ // Se a pilha não está vazia
        do{ // Remove os elementos da pilha

            pop(pilha, &valor);

        }while(!isEmpty(pilha)); //Enquanto a pilha nao estiver vazia

        if(isEmpty(pilha)){ // Se a pilha está vazia
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int isEmpty(PILHA *pilha){
    if (pilha->topo_pilha == NULL){//Se o topo aponta pra NULL
        return 1; // Pilha vazia(retorna 1)
    } else {
        return 0; // Pilha com elementos
    }
}
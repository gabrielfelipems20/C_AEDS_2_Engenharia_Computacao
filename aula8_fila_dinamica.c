#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    int info;
    struct elemento *link;
}ELEMENTO;

typedef struct fila{
    struct elemento *inicio;
    struct elemento *fim;
    int lenght;
}FILA;

int filaVazia(FILA *fila);
int insereElemento(FILA *fila, int valor);
int removeElemento(FILA *fila, int *valor);
int excluiFila(FILA *fila);

/*-------------------------------------------------MAIN----------------------------------------------*/

int main(){

    FILA fila1;
    fila1.fim = NULL;
    fila1.inicio = NULL;

    //Inserindo elementos a, b, e c na fila.

    int a = insereElemento(&fila1, 666);
    if(a){
       printf("ELEMENTO A INSERIDO\nNUMERO %d\n", fila1.fim->info); 
    } else {
        printf("ERRO AO INSERIR ELEMENTO");
    }

    int b = insereElemento(&fila1, 69);
    if(b){
       printf("ELEMENTO B INSERIDO\nNUMERO %d\n", fila1.fim->info); 
    } else {
        printf("ERRO AO INSERIR ELEMENTO");
    }

    int c = insereElemento(&fila1, 171);
    if(c){
       printf("ELEMENTO C INSERIDO\nNUMERO %d\n", fila1.fim->info); 
    } else {
        printf("ERRO AO INSERIR ELEMENTO");
    }

    //Remove elemento da fila

    int n_removido;
    int d = removeElemento(&fila1, &n_removido);
    if(d == 1){
        printf("ELEMENTO %d REMOVIDO\n", n_removido);
        printf("INICIO AGORA PASSA A SER %d\n", fila1.inicio->info);
    } else {
        printf("ERRO AO REMOVER ELEMENTO\n");
    }

    // Exclui a fila

    int l = excluiFila(&fila1);
    if (l == 1){
        printf("FILA EXCLUIDA\n");
    } else {
        printf("ERRO AO EXCLUIR A FILA");
    }
    
     if (filaVazia(&fila1)){
        printf("FILA VAZIA\n");
    } else {
        printf("FILA COM ELEMENTOS\n");
    }

    return 0;
}


/*------------------------------------------------FUNÇOES----------------------------------------------*/

int filaVazia(FILA *fila){

    if(fila->inicio == NULL && fila->fim == NULL){
        return 1;
    } else {
        return 0;
    }
}

int insereElemento(FILA *fila, int valor){

    ELEMENTO *novo_elemento = (ELEMENTO*)malloc(sizeof(ELEMENTO)); // Aloca memoria para um novo elemento
    novo_elemento->link = NULL;

    if(novo_elemento != NULL){ // Se foi alocado memoria para o elemento
        if (filaVazia(fila)){ // Se a fila está vazia
            fila->inicio = novo_elemento; // Inicio recebe o endereço do novo elemento
            fila->fim = novo_elemento; // Fim recebe o endereço do novo elemento
            if (!filaVazia(fila)){ // Se agora, inicio e fim apontam para o elemento
                novo_elemento->info = valor; //Novo elemento recebe valor
                fila->lenght = 1; // Aumenta o tamanho da fila
                return 1; //Elemento inserido
            } else {
                return 0; //Erro na criaçao do elemento
            }
        } else { // Se a fila nao está vazia(inicio e fim apontam para elementos da fila)
            fila->fim->link = novo_elemento; // Linka elemento anterior ao novo
            fila->fim = novo_elemento; // Fim recebe o endereço do novo elemento
            novo_elemento->info = valor; // novo elemento recebe valor
            fila->lenght++; // Tamanho da fila aumenta
            return 1; //Elemento inserido
        }
    } else {
        return 0; //Erro na criaçao do elemento
    }
}

int removeElemento(FILA *fila, int *valor){

    FILA aux;

    if(!filaVazia(fila)){ // Se a fila nao esta vazia
        *valor = fila->inicio->info; // valor recebe o valor excluido
        aux.inicio = fila->inicio; // Aux recebe o endereço do inicio da fila
        fila->inicio = fila->inicio->link; // Inicio aponta para o proximo elemento(elemento anterior)
        
        if(fila->inicio != aux.inicio){
            free(aux.inicio); // Libera a memoria do ultimo elemento
            fila->lenght--; // Tamanho da fila diminui
            if (fila->inicio == NULL){
                fila->fim = NULL;
            }
            return 1;
        }
    } else {
        return 0;// Não há elementos na fila ou erro ao remover elementos
    }
}


int excluiFila(FILA *fila){

    int valor;

    if(!filaVazia(fila)){ //Se a fila esta vazia

        do{
            removeElemento(fila, &valor); // Remove elemento
        }while(!filaVazia(fila)); // Enquanto a fila nao estiver vazia

        if(filaVazia(fila)){ 
            return 1; // Retorna 1 se a fila esta vazia 
        } else {
            return 0;// 0 se a fila nao esta vazia
        }
    } 
}
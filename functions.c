/*
    Arquivo  com as funções usadas no trabalho final da disciplina de AEDS 1 onde o objetivo era praticar
     os conhecimentos adquiridos sobre structs, ponteiros, alocação dinâmica de memória, arquivos, algoritmos de ordenaçao, 
    identação de código comentarios, funções, laços de repetição, e lógica de programação.
*/


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "funcoes.h"


void menu(){

    int x;
    int numero_linhas = nLinhas();
    ALUNO *alunos;//ponteiro que armazena o endere�o onde sera armazenado os dados do arquivo
    alunos = alocaAlunos(alunos, numero_linhas);//Recebe os dados do arquivo

    REPETE://Label goto que exibe novamente o menu se a op�ao 0 nao for selecionada

    do{//Imprime o menu ate ser escolhido uma op�ao valida
        printf("...............ESCOLHA UMA OPCAO.............\n\n");
        printf("1 - MOSTRAR  TODOS OS ELEMENTOS:\n");
        printf("2 - MOSTRAR O NOME DOS ALUNOS:\n");
        printf("3 - MOSTRAR O NOME E A NOTA FINAL DOS ALUNOS:\n");
        printf("4 - DADOS DE UM ALUNO POR BUSCA SEQUENCIAL:\n");
        printf("5 - MOSTRAR OS ALUNOS POR ORDEM CRESCENTE DE MATRICULA:\n");
        printf("6 - EDITAR A NOTA DE UM ALUNO:\n");
        printf("7 - DADOS DO ALUNO COM MAIOR NOTA:\n");
        printf("8 - DADOS DO ALUNO COM A MENOR NOTA:\n");
        printf("9 - MOSTRA QUAIS FORAM APROVADOS E QUAIS FORAM REPROVADOS:\n");
        printf("0 - SAIR DO PROGRAMA:\n");
        scanf("%d", &x);//Recebe o valor da op�ao pra ser usado em swith
    }while(x < 0 || x > 9);

    printf("OPCAO %d\n", x);//Exibe a op�ao escolhida

    switch(x){//Executa as fun�oes de acordo com a op�ao escolhida
        case 1:
            imprimeTodos(alunos, numero_linhas);
            break;
        case 2:
            imprimeNomes(alunos, numero_linhas);
            break;
        case 3:
            imprimeNomes_notas(alunos, numero_linhas);
            break;
        case 4:
            buscaAluno(alunos, numero_linhas);
            break;
        case 5:
            alunos = bubbleSort(alunos, numero_linhas);
            imprimeTodos(alunos, numero_linhas);
            break;
        case 6:
            editaNota(alunos, numero_linhas);
            break;
        case 7:
            maior(alunos, numero_linhas);
            break;
        case 8:
            menor(alunos, numero_linhas);
            break;
        case 9:
            imprimeStatus(alunos, numero_linhas);
            break;
        case 0://Finaliza o programa
            goto FIM_LOOP;// Executa o codigo a partir da label FIM_LOOP
            break;
    }
    goto REPETE;//Reexecuta o codigo a partir da label REPETE
    FIM_LOOP://Salta o comando goto REPETE,
    free(alunos);//Libera a memoria alocada dinamicamente da struct alunos
}

int nLinhas(){// Conta o numero de linhas que o arquivo lido possui
    FILE *arq;
    arq = fopen("tabela_alunos.txt", "r");//Abre o arquivo
    char ch;
    int cont = 1;

    while((ch = fgetc(arq)) != EOF){//Percorre cada caractere ate encontrar o fim do arquivo(EOF)
        if (ch == '\n'){//incrementa cont se encontra o caractere \n(ENTER)
            cont++;
        }
    }
    fclose(arq);//fecha o arquivo
    return cont;//Retorna o numero de linhas que possui o arquivo
}

ALUNO *alocaAlunos(ALUNO *aluno, int numero_de_linhas){//Aloca os dados dos alunos dinamicamente

    FILE *arq;//Abre o arquivo para o modo leitura
    arq = fopen("tabela_alunos.txt", "r");
    int i;
    aluno = (ALUNO*)malloc(sizeof(ALUNO) * numero_de_linhas);//Armazena uma quantidade de Bytes equivalente ao tamanho da struct ALUNO * numero de linhas

    for(i = 0; i < numero_de_linhas ; i++){//La�o que armazena os dados de cada aluno na struct
        fscanf(arq, "%d %s %f %f %f", &aluno[i].id, &aluno[i].nome,
                &aluno[i].nota1,&aluno[i].nota2, &aluno[i].nota3);

        aluno[i].media = (aluno[i].nota1 + aluno[i].nota2 + aluno[i].nota3) / 3;//calcula a media de cada aluno e armazena na struct

        if(aluno[i].media >= NOTA_MINIMA){
            aluno[i].status = TRUE;                //aluno com media maior que 6 recebe TRUE - aprovado
        } else if(aluno[i].media < NOTA_MINIMA){
            aluno[i].status = FALSE;               //aluno com nota menor que 6 recebe FALSE - reprovado
        }
    }
    fclose(arq);//fecha o arquivo
    return aluno;//retorna um ponteiro do tipo ALUNO
}

void imprimeTodos(ALUNO *aluno, int numero_de_linhas){//Imprime todos os dados dos alunos
    int i;

    for(i = 0; i < numero_de_linhas; i++){
        printf("ALUNO: %s\nID: %d\nNOTA 1: %.1f\nNOTA 2: %.1f\nNOTA 3: %.1f\nMEDIA: %.1f\n\n",
                aluno[i].nome, aluno[i].id, aluno[i].nota1, aluno[i].nota2, aluno[i].nota3, aluno[i].media);
    }
}

void imprimeNomes(ALUNO * aluno, int numero_de_linhas){//Imprime apenas os nomes dos alunos
    int i;

    for(i = 0; i < numero_de_linhas; i++){
        printf("%s\n", aluno[i].nome);
    }
}

void imprimeNomes_notas(ALUNO * aluno, int numero_de_linhas){//Imprime os nomes e as notas dos alunos
    int i;

    for(i = 0; i < numero_de_linhas; i++){
        printf("ALUNO: %s\nNOTA FINAL: %.1f\n\n\n",
               aluno[i].nome, aluno[i].media);
    }
}

ALUNO *bubbleSort(ALUNO *aluno, int numero_de_linhas){//Ordena os dados de acordo com o numero de matricula
    ALUNO aux; // struct auxiliar que copia os dados da struct do aluno com maior numero de matriculo
	int  troca, i, j;
	troca = TRUE; //verifica��o da troca em cada la�o

	for(j = numero_de_linhas - 1; (j >= 1) && (troca == TRUE); j--){
		troca = FALSE; //Se o valor continuar FALSE na pr�xima passada quer dizer que n�o houve troca e a fun��o � encerrada
		for(i = 0; i < j; i++){
				if(aluno[i].id > aluno[i+1].id){// Faz a troca da struct com maior numero de matricula; comparando cada posi�ao com a proxima, ate levar a maior ao topo
					aux = aluno[i];//struct na posicao i copiada em aux
					aluno[i] = aluno[i+1];// struct i recebe o valor da menor
					aluno[i+1] = aux; // a struct que antes era menor e trocada pela maior armzenada em aux
					troca = TRUE; //Se houve troca, "troca" recebe TRUE para continuar rodando.
			}
		}
	}
	return aluno;
}

void buscaAluno(ALUNO *aluno, int numero_de_linhas){//Busca sequencial por matricula
    int matricula, i, c = FALSE;
    ALUNO aux;

    printf("DIGITE O NUMERO DE MARICULA DO ALUNO: ");
    scanf("%d", &matricula);//armazena a matricula que sera buscada

    for(i = 0; i < numero_de_linhas; i++){ //percorre todos os elementos da lista
        if (aluno[i].id == matricula){ // se o valor procurado for igual a matricula do elemento da struct na posi�ao [i]
            aux = aluno[i]; // copia os dados da posi�ao para a struct auxiliar
            c = TRUE;  //muda o estado de c para true
        }
    }

    if(c == TRUE){ // se c for true imprime o valor armazenado na struct aux
        printf("ALUNO: %s\nNOTA 1: %.1f\nNOTA 2: %.1f\nNOTA 3: %.1f\nMEDIA: %.1f\n",
               aux.nome, aux.nota1, aux.nota2, aux.nota3, aux.media);
    } else { // senao imprime a msg de matricula nao encontrada
        printf("MATRICULA NAO ENCOTRADA\n");
    }
}

void editaNota(ALUNO *aluno, int numero_de_linhas){//Edita a nota de um aluno
    float n, media_aux;
    int h = 0, y, i, matricula;


    printf("DIGITE A MATRICULA:\n");
    scanf("%d", &matricula); //
    LABEL_1: // repete as op�oes de notas se o numero da op�ao for invalido
    printf(".....NOTA A SER EDITADA.....\n");
    printf("1 - NOTA 1\n");
    printf("2 - NOTA 2\n");
    printf("3 - NOTA 3\n");
    scanf("%d", &h);
    if(h < 1 || h > 3){
        printf("OPCAO INVALIDA, TENTE OUTRA");
        goto LABEL_1; // retoma o codigo apartir de LABEL_1
    }
    printf("NOVA NOTA: \n");// valor da nova nota
    scanf("%f", &n);

    switch(h){
        case 1:
       for(i = 0; i < numero_de_linhas; i++){
                if (aluno[i].id == matricula){ // percorre as matriculas ate encontrar a solicitada
                    printf("ALUNO: %s\nMATRICULA: %d\nNOTA 1: %.1f\nMEDIA: %f\n",//printa dados dos alunos que serao alterados
                            aluno[i].nome, aluno[i].id, aluno[i].nota1, aluno[i].media);
                    aluno[i].nota1 = n; //atribui a nova nota o valor da nova nota
                    y = i; //Salva aposi�ao de i para atribuir a nova media a posi�ao do vetor salva por i
                    media_aux = (aluno[i].nota1 + aluno[i].nota2 + aluno[i].nota3) / 3;
                }
            }
            aluno[y].media = media_aux; //atribui o valor da nova media calculada
            printf("NOTA ALTERADA: %.1f: \nNOVA MEDIA: %.1f\n", aluno[y].nota1, aluno[y].media);
            break;

        case 2:
            for(i = 0; i < numero_de_linhas; i++){
                if (aluno[i].id == matricula){
                    printf("ALUNO: %s\nMATRICULA: %d\nNOTA 2: %.1f\nMEDIA: %f\n",
                            aluno[i].nome, aluno[i].id, aluno[i].nota2, aluno[i].media);
                    aluno[i].nota2 = n;
                    y = i;
                    media_aux = (aluno[i].nota1 + aluno[i].nota2 + aluno[i].nota3) / 3;
                }
            }
            aluno[y].media = media_aux;
            printf("NOTA ALTERADA: %.1f: \nNOVA MEDIA: %.1f\n", aluno[y].nota2, aluno[y].media);
            break;

        case 3:
             for(i = 0; i < numero_de_linhas; i++){
                if (aluno[i].id == matricula){
                    printf("ALUNO: %s\nMATRICULA: %d\nNOTA 3: %.1f\nMEDIA: %f\n",
                            aluno[i].nome, aluno[i].id, aluno[i].nota3, aluno[i].media);
                    aluno[i].nota3 = n;
                    y = i;
                    media_aux = (aluno[i].nota1 + aluno[i].nota2 + aluno[i].nota3) / 3;
                }
            }
            aluno[y].media = media_aux;
            printf("NOTA ALTERADA: %.1f: \nNOVA MEDIA: %.1f\n", aluno[y].nota3, aluno[y].media);
            break;
    }
}

void maior(ALUNO * aluno, int numero_de_linhas){//Imprime os dados do aluno com maior nota
    int i, aux = 0;
    float maior = 0.0;

    for (i = 0; i < numero_de_linhas; i++){
        if(maior == 0.0){
            maior = aluno[i].media;
        }
        if(aluno[i].media > maior){
            maior = aluno[i].media;
            aux = i;
        }
    }
    printf("ALUNO: %s\nID: %d\nNOTA 1: %.1f\nNOTA 2: %.1f\nNOTA 3: %.1f\nMEDIA: %.1f\n\n",
           aluno[aux].nome,aluno[aux].id, aluno[aux].nota1, aluno[aux].nota2, aluno[aux].nota3, aluno[aux].media);
}

void menor(ALUNO * aluno, int numero_de_linhas){//Imprime dados do aluno com menor nota
    int i, aux = 0;
    float menor = 0.0;

    for (i = 0; i < numero_de_linhas; i++){
        if(menor == 0.0){
            menor = aluno[i].media;
        }
        else if(aluno[i].media < menor){
            menor = aluno[i].media;
            aux = i;
        }
    }
    printf("ALUNO: %s\nID: %d\nNOTA 1: %.1f\nNOTA 2: %.1f\nNOTA 3: %.1f\nMEDIA: %.1f\n\n",
           aluno[aux].nome,aluno[aux].id, aluno[aux].nota1, aluno[aux].nota2, aluno[aux].nota3, aluno[aux].media);
}

void imprimeStatus(ALUNO * alunos, int numero_de_linhas){
    int aux = FALSE, i, j;

    for (i = 0; i < numero_de_linhas; i++){
        if(aux == FALSE){ // impreime os alunos reprovados
            printf("......LISTA DOS APROVADOS.....\n");
            for(j = 0; j < numero_de_linhas; j++){
                if(alunos[j].status == 1){
                    printf("NOME: %s\nMEDIA:%.1f\n", alunos[j].nome, alunos[j].media);
                }
            }
            aux = TRUE;
            printf("......LISTA DOS REPROVADOS.....\n");
        }
        if(alunos[i].status == 0){ //imprime os aprovados
            printf("NOME: %s\nMEDIA:%.1f\n\n", alunos[i].nome, alunos[i].media);
        }
    }
}

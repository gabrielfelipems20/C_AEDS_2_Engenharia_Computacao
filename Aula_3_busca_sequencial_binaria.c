/* 
        Programa aloca memória para um vetor com dados de 116 estudantes do arquivo tabela_alunos.txt 
    e exibe as opções para o usuário realizar a busca pela matrícula do aluno retornando seus dados.
    O programa exibe três opções e calcula o tempo em milisegundos de processamento de cada:
    Busca Sequencial, Busca Binária com os dados já ordenados, e Busca Binária com os dados desordenados,
    utilizando o algoritmo Bubble Sort para ordenação;

    OBJETIVO: Demonstrar os conceitos aprendidos na disciplina de AEDS II sobre  Busca Sequencial e Binária, e ainda comparar 
    a eficiência de algoritmos além de reforçar aprendizados adquiridos como uso de ponteiros, structs, alocação dinâmica de memória
    arquivos e o uso da biblioteca <time.h>.
*/


#include <stdlib.h> //Bibliotecas usadas
#include <stdio.h>
#include <math.h>
#include <time.h>


typedef struct{     //Struct dos com os membros do tipo aluno
    int key;
    char name[20];
    float n1;
    float n2;
    float n3;
    float average;
}STUDENT;


int sequentialSearch(STUDENT *student_pointer, int key, int number_of_lines); // Cabeçalho de funções
int binarySearch(STUDENT *student_pointer, int key, int number_of_lines);
int countLines(FILE *file);
STUDENT *bubbleSort(STUDENT *students, int number_of_lines);


int main(void){


/*------------------------------------------------------ALOCAÇÃO DE MEMÓRIA-------------------------------------------------------------------*/


    FILE *file = fopen("tabela_alunos.txt", "r");       //Abre o arquivo tabela_alunos.txt para contagem de linhas
    if(file ==  NULL){
        printf("ERRO AO ABRIR O ARQUIVO\n");
    } else {
        printf("ARQUIVO ABERTO\n");
    }


    int n_lines = countLines(file);     //Conta o n° de linhas 


    STUDENT *students = (STUDENT*)malloc(sizeof(STUDENT) * n_lines);      //Aloca a memoria para os dados dos alunos do arquivo
    if(students == NULL){
        printf("ERRO AO ALOCAR MEMORIA\n");
    } else {
        printf("MEMORIA ALOCADA\n");
    }


    int i;
    file = fopen("tabela_alunos.txt", "r");     // Reabre o arquivo para ser inserido os dados na memoria
    for(i = 0; i < n_lines; i++){    //Insere os dados dos alunos na memoria reservada e calcula a média 

        fscanf(file, "%d %s %f %f %f", &students[i].key, &students[i].name, &students[i].n1, &students[i].n2, &students[i].n3);

        students[i].average = (students[i].n1, students[i].n2, students[i].n3) / 3;

    }
    fclose(file);  //Fecha o arquivo


/*------------------------------------------------------------------MAIN----------------------------------------------------------------------*/


    printf("\n--------NUMEROS DE MATRICULA A SEREM BUSCADOS------\n");
    for(i = 0; i < n_lines; i++){   // Imprime pro usuário as matrículas
        printf("Matricula: %d\n", students[i].key);
    }


    int x;
    int key_index;
    int key;
    clock_t start_time;
    clock_t end_time;
    double cpu_time_used;


    do{


        printf("1 - BUSCA SEQUENCIAL:\n");
        printf("2 - BUSCA BINARIA COM DADOS ORDENADOS:\n");
        printf("3 - BUSCA BINARIA COM DADOS DESORDENADOS:\n");
        printf("0 - SAIR:\n");

        scanf("%d", &x);

        switch (x){
        case 0:
            break;
        
        case 1:

            printf("\n--------POR BUSCA BINARIA------\n\n");
            printf("MATRICULA A SER BUSCADA: \n");
            scanf("%d", &key);

            start_time = clock();
            key_index = sequentialSearch(students, key, n_lines);
            end_time = clock();
            cpu_time_used = ((double) (end_time - start_time));

            printf("\nMatricula: %d\nNome: %s\nNota 1: %f\nNota 2: %f\nNota 3: %f\nMedia: %f\n\n\n", 
                    students[key_index].key, students[key_index].name, students[key_index].n1,
                    students[key_index].n2,  students[key_index].n3, students[key_index].average);
            printf("\nTempo de processamento gasto na busca sequencial: %f ms\n\n", cpu_time_used);

            break;

        case 2:

            printf("\n--------POR BUSCA BINARIA COM DADOS DESORDENADOS------\n\n");
            printf("MATRICULA A SER BUSCADA: \n");
            scanf("%d", &key);

            start_time = clock();
            bubbleSort(students, n_lines);
            key_index = binarySearch(students, key, n_lines);
            end_time = clock();
            cpu_time_used = ((double) (end_time - start_time));

            printf("\nMatricula: %d\nNome: %s\nNota 1: %f\nNota 2: %f\nNota 3: %f\nMedia: %f\n\n\n", 
                    students[key_index].key, students[key_index].name, students[key_index].n1,
                    students[key_index].n2,  students[key_index].n3, students[key_index].average);
            printf("\nTempo de processamento gasto na busca Binaria com dados desordenados: %f ms\n\n", cpu_time_used);
            break;

        case 3:

            printf("\n--------POR BUSCA BINARIA COM DADOS ORDENADOS------\n\n");
            printf("MATRICULA A SER BUSCADA: \n");
            scanf("%d", &key);

            bubbleSort(students, n_lines);
            start_time = clock();
            key_index = binarySearch(students, key, n_lines);
            end_time = clock();
            cpu_time_used = ((double) (end_time - start_time));

            printf("\nMatricula: %d\nNome: %s\nNota 1: %f\nNota 2: %f\nNota 3: %f\nMedia: %f\n\n\n", 
                    students[key_index].key, students[key_index].name, students[key_index].n1,
                    students[key_index].n2,  students[key_index].n3, students[key_index].average);
            printf("\nTempo de processamento gasto na busca Binaria com dados ordenados: %f ms\n\n", cpu_time_used);
            break;
        
        default:
            printf("\nNENHUMA BUSCA SELECIONADA\n");
        }

    }while(x != 0);


    free(students);  // Libera a memoria alocada para *students
    return 0;
}


/*----------------------------------------------------------------FUNÇÕES-----------------------------------------------------------------------*/


int sequentialSearch(STUDENT *student_pointer, int key, int number_of_lines){   // Busca Sequencial

    int i;

    for(i = 0; i < number_of_lines; i++){
        if (student_pointer[i].key == key){
            return i;
        }
    }
    return -1;
}


int binarySearch(STUDENT *student_pointer, int key, int number_of_lines){

    int i_center;
    int i_left;
    int i_right;

    i_left = 0;
    i_right = number_of_lines -1;

    do{

        i_center = (i_left + i_right) / 2;    
                                                    
        if(key > student_pointer[i_center].key){   
            i_left = i_center + 1;                   
        } else {                                                  
            i_right = i_center - 1;                 
        }

    }while(key != student_pointer[i_center].key && i_left <= i_right);

    if(key == student_pointer[i_center].key){
        return i_center;
    } else {
        return -1;
    }
}

int countLines(FILE *file){   // Conta o número de linhas de um arquivo

    char ch;
    int count = 1;

    while((ch = fgetc(file)) != EOF){
        if (ch == '\n'){
            count++;
        }
    }
    return count;
}

STUDENT *bubbleSort(STUDENT *students, int number_of_lines){    //Ordena um vetor de STUDENT para ser buscado em binarySearch();

    STUDENT aux; 
	int  shift, i, j;
	shift = 1; 

	for(j = number_of_lines - 1; (j >= 1) && (shift == 1); j--){

		shift = 0; 
		for(i = 0; i < j; i++){
				if(students[i].key > students[i+1].key){

					aux = students[i];
					students[i] = students[i+1];
					students[i+1] = aux; 
					shift = 1;
			}
		}
	}

	return students;
}
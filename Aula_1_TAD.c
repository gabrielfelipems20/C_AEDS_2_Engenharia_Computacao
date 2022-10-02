/*
    Programa abaixo cria uma struct do tipo POINT, que representa um ponto no plano cartesiano, e efetua operações
    sobre os mesmos como: criar um ponto, verificar se um ponto se encontra em um certo quadrante, alterar os eixos X e Y,
    e calcular a distância entre dois pontos.

    OBJETIVO: Demonstrar os conceitos aprendidos na disciplina de AEDS II sobre  TAD(tipos abstratos de dados), além de reforçar
    aprendizados adquiridos como uso de ponteiros e structs.
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct{

    float X, Y, highestPointValue;
    int quadrant;

}POINT;

POINT createPoint(float X_axis, float Y_axis);
int hasPoint(POINT point, int quadrant);
void changeAxisX(POINT *point, float new_axis_x_value);
void changeAxisY(POINT *point, float new_axis_y_value);
float calculateDistance(POINT point_A, POINT point_B);


/*------------------------------------------------------------------MAIN---------------------------------------------------------------*/

int main(void){

    POINT A, B;

    //cria os pontos A e B

    A = createPoint(2.0, 3.0);
    B = createPoint(-7.0, 6.0);

    //imprime as propiedades dos pontos

    printf("ponto A:\n");
    printf("Eixo X: %.2f\nEixo Y: %.2f\nMaior valor na coordenada: %.2f\nQuadrante: %d\n\n", A.X, A.Y, A.highestPointValue, A.quadrant);

    printf("ponto B:\n");
    printf("Eixo X: %.2f\nEixo Y: %.2f\nMaior valor na coordenada: %.2f\nQuadrante: %d\n\n", B.X, B.Y, B.highestPointValue, B.quadrant);

    //muda valores nos eixos x no ponto A e y no ponto B

    changeAxisX(&A, 9.0);
    printf(" Novo ponto A:\n");
    printf("Eixo X: %.2f\nEixo Y: %.2f\nMaior valor na coordenada: %.2f\nQuadrante: %d\n\n", A.X, A.Y, A.highestPointValue, A.quadrant);

    changeAxisY(&B, -3);
    printf(" Novo ponto B:\n");
    printf("Eixo X: %.2f\nEixo Y: %.2f\nMaior valor na coordenada: %.2f\nQuadrante: %d\n\n", B.X, B.Y, B.highestPointValue, B.quadrant);

    //imprime o quadrante em que os pontos se encontram

    printf("Ponto A está no quadrante %d\n", A.quadrant);
    printf("Ponto B está no quadrante %d\n\n", B.quadrant);

    //imprime os maiores valores nos pontos A e B

    printf("Maior valor do ponto A: %f\n", A.highestPointValue);
    printf("Maior valor do ponto B: %f\n\n", B.highestPointValue);

    //testa se o ponto a esta em um determinado quadrante

    if(hasPoint(A, 2)){
        printf("Esta no quadrante\n");
    } else {
        printf("Ponto A nao esta no quadrante 2\n\n");
    }

    //calcula e imprime a distancia entre os dois pontos

    float distancia1 = calculateDistance(A, B);
    printf("Distancia 1: %f\n", distancia1);
}

//-----------------------------------------------------------------FUNCOES-------------------------------------------------------------------


POINT createPoint(float X_axis, float Y_axis){
    POINT point;

    point.X = X_axis;
    point.Y = Y_axis;


    if (point.X > point.Y){

        point.highestPointValue = point.X;

    } else {

        point.highestPointValue = point.Y;

    }


    if (point.X >= 0 && point.Y >= 0){

        point.quadrant = 1;

    } else if (point.X <= 0 && point.Y >= 0){

        point.quadrant = 2;

    } else if (point.X <= 0 && point.Y <= 0){

        point.quadrant = 3;

    } else if (point.X >= 0 && point.Y <= 0){

        point.quadrant = 4;

    }

    return point;

}

int hasPoint(POINT point, int quadrant){

    if(quadrant >= 1 && quadrant <= 4){

        if(point.quadrant == quadrant){

            return 1;

        } else {

            return 0;

        }
        
    } else {

        return -1;

    }
}

void changeAxisX(POINT *point, float new_axis_x_value){

    POINT aux;

    aux = createPoint(new_axis_x_value, point->Y);

    point->highestPointValue = aux.highestPointValue;
    point->quadrant = aux.quadrant;
    point->X = aux.X;
    point->Y = aux.Y;

}

void changeAxisY(POINT *point, float new_axis_y_value){

    POINT aux;

    aux = createPoint(point->X, new_axis_y_value);

    point->highestPointValue = aux.highestPointValue;
    point->quadrant = aux.quadrant;
    point->X = aux.X;
    point->Y = aux.Y;

}

float calculateDistance(POINT point_A, POINT point_B){

    float distance;

    distance = sqrt((pow((point_B.X - point_A.X), 2) + 
                     pow((point_B.Y - point_A.Y), 2)));

    return distance;

}
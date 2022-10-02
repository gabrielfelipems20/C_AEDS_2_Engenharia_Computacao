#include <math.h>

typedef struct{

    float X, Y, highestPointValue;
    int quadrant;

}POINT;

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
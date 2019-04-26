#include "cabeceras/allvars.h"

//==============================================================================
double velx(double totalEnergy, double b, double x0){
    /*Esta funcion calcula la velocidad a patir de la ligadura del problema que 
    surge al imponer conservacion de la energia. */
    return sqrt( 2 * (totalEnergy - V(x0, b)) * 1/M);
}

double getEnergy(double x, double y, double vx, double vy){
    double v,E;
    v = sqrt(vx *vx + vy * vy);
    E = M * V(x, y) + .5 * M * v * v;  

    return E;
}

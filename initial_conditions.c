#include "cabeceras/allvars.h"

double getXPosition(double totalEnergy, double b){
    /*Esta funcion se utiliza para encontrar el x0 adecuado, tal que, no se tome
    un estado inicial con una energía mayor a totalEnergy, esto produciria 
    velocidades imaginarias.*/
    return sqrt(totalEnergy) / b;
}
//==============================================================================
double velx(double totalEnergy, double b, double x0){
    /*Esta funcion calcula la velocidad a patir de la ligadura del problema que 
    surge al imponer conservacion de la energia. */
    return sqrt( 2 * (totalEnergy - V(x0, b)) * 1/M);
}

#include "cabeceras/allvars.h"

void dimention(double eps, int *N, int *Nc, double t0, double x0, double y0, double vx_0, double vy_0, double E){

    double phi1, phi2;
    double b = -.6;
    int i = 0, j = 0; // i es un contador del numero de parametros de impacto y
    // j es un contador del numero de parametros para el cual es caotico.

    vx_0 = velx(E, b, x0);
    scattering_variables(t0, x0, b, vx_0, vy_0);
    while(b < -.1){
        //cada ciclo corresponde a un parametro de impacto(b) distinto. 
        i ++;
        phi1 = phi;
        b+= eps;
        vx_0 = velx(E, b, x0);
        scattering_variables(t0, x0, b, vx_0, vy_0);
        phi2 = phi;

        if (abs(phi2 - phi1) > .2)
            j++;
    }
    *N = i;
    *Nc = j;
}
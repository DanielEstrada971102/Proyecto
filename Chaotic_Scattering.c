#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "cabeceras.h"

#define Distance(x, y) (sqrt((x) * (x) + (y) * (y)))
#define M 1 //masa de la particula
#define R sqrt(9) // define una region efectiva del potencial de radio R.

// Variables globales
double h = 1e-2;  
double phi , t = 0; //phi:angulo de dispersion, t:tiempo dentro de la región R.

//==============================================================================
//Prototipos
void PathParticule(double t0, double x0, double y0, double vx_0, double vy_0,char *fileName);
void ScatteringVariables(double t0, double x0, double y0, double vx_0, double vy_0);
double Velx(double totalEnergy, double b , double *x0);
double getXPosition(double totalEnergy, double b);
//==============================================================================
//Funcion principal
int main(int argc, char const *argv[]){
    double t0 = 0, x0, vx_0, vy_0 = 0;  //condiciones iniciales
    double totalEnergy = 0.1 * exp(-2);

    //==========================================================================
    //Se calculan 4 trayectorias con parametros de impacto similares para ver el
    //caracter caotico del sistema.
    double b = -0.42;

    for (int i = 0; i < 4; i++){
        char fileName[20];

        sprintf(fileName, "resultados/Trayectoria_%d.txt",i);
        vx_0 = Velx(totalEnergy, b, &x0);
        PathParticule(t0, x0, b, vx_0, vy_0, fileName);
        b += 1e-4;
    }
    //==========================================================================
    // se calcula phi y t para varios valores de b 
    FILE *archivo = fopen("resultados/S_variables.txt", "w");

    fprintf(archivo, "# b phi t \n");
    for (b = -.6; b < -.1; b += 2e-4){
        //cada ciclo corresponde a un parametro de impacto(b) distinto.
        t = 0; 
        vx_0 = Velx(totalEnergy, b, &x0);
        ScatteringVariables(t0, x0, b, vx_0, vy_0);
        fprintf(archivo, "%lf %lf %lf \n", b, phi, t); 
    }
    fclose(archivo); 
    //==========================================================================
    
    return 0;
}
//==============================================================================
void PathParticule(double t0, double x0, double y0, double vx_0, double vy_0, char *fileName){
    /* Esta funcion evoluciona el estado de la particula y escribe en el archivo
    "fileName" los datos correspondientes a la posicion en cada instante con su 
    respectiva velocidad*/
    FILE *archivo;
    archivo = fopen(fileName, "w");

    fprintf(archivo, "# t x y vx vy\n");
    fprintf(archivo, "%lf %lf %lf %lf %lf \n", t0, x0, y0, vx_0, vy_0);

    while(Distance(x0, y0) > R){
        Solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, h);
        t0 += h;       
        fprintf(archivo, "%lf %lf %lf %lf% lf \n", t0, x0, y0, vx_0, vy_0);
    }
    while(Distance(x0, y0) <= R){
            Solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, h);
            t0 += h;       
            fprintf(archivo, "%lf %lf %lf %lf% lf \n", t0, x0, y0, vx_0, vy_0);
    }        

    fclose(archivo);
}
//==============================================================================
void ScatteringVariables(double t0, double x0, double y0, double vx_0, double vy_0){
    /* Esta funcion evoluciona el estado de un particula a partir de las 
    ecuaciones diferencuales del sistema Dx, Dy, Dv_x, Dv_y, utilizando Solver
    para calcular las variables phi y t.*/
    
    while(Distance(x0, y0) > R){
        /* Mientras la particula este fuera del radio efectivo del potencial(R)
        simplemente se evoluciona el sistema. */
        Solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, h);
        t0 += h;       
   }

    while(Distance(x0, y0) <= R){
        /* Mientras la particula este dentro del radio efectivo del potencial
        evoluciona el sistema y calcula el tiempo que le toma salir de esta
        region (t). */
        Solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, h);
        t0 += h;
        t += h;      
   }
   // Una vez que haya salido del radio efectivo del potencial se calcula phi
   phi = atan(y0/x0);
}
//==============================================================================
//Potencial
double V(double x, double y){
    return x * x * y * y * exp(-(x * x) - (y * y));
}
//==============================================================================
double getXPosition(double totalEnergy, double b){
    /*Esta funcion se utiliza para encontrar el x0 adecuado, tal que, no se tome
    un estado inicial con una energía mayor a totalEnergy, esto produciria 
    velocidades imaginarias.*/
    srand(time(NULL));
    return sqrt(totalEnergy) / (b * rand()) - 2;
}
//==============================================================================
double Velx(double totalEnergy, double b, double *x0){
    /*Esta funcion calcula la velocidad a patir de la ligadura del problema que 
    surge al imponer conservacion de la energia. A su vez, inicializa x0 con 
    getXPosition*/
    *x0 = getXPosition(totalEnergy, b);
    double v = 2 * (totalEnergy - V(*x0, b)) * 1/M;
    return sqrt(v);
}

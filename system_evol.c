#include "cabeceras/allvars.h"

double dt = 1e-2;
double phi, t; //phi:angulo de dispersion, t:tiempo dentro de la región R.

void path_particule(double t0, double x0, double y0, double vx_0, double vy_0, char *fileName){
    /* Esta funcion evoluciona el estado de la particula y escribe en el archivo
    "fileName" los datos correspondientes a la posicion en cada instante con su 
    respectiva velocidad*/
    FILE *archivo;
    archivo = fopen(fileName, "w");

    fprintf(archivo, "# t x y z vx vy\n");
    fprintf(archivo, "%lf %lf %lf %lf %lf %lf \n", t0, x0, y0, 0.0, vx_0, vy_0);

    while(Distance(x0, y0) > R){
        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, dt);
        t0 += dt;       
        fprintf(archivo, "%lf %lf %lf %lf %lf %lf \n", t0, x0, y0, 0.0, vx_0, vy_0);
    }
    while(Distance(x0, y0) <= R){
            solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, dt);
            t0 += dt;       
            fprintf(archivo, "%lf %lf %lf %lf %lf %lf \n", t0, x0, y0, 0.0, vx_0, vy_0);
    }        

    fclose(archivo);
}
//==============================================================================
void scattering_variables(double t0, double x0, double y0, double vx_0, double vy_0){
    /* Esta funcion evoluciona el estado de un particula a partir de las 
    ecuaciones diferencuales del sistema Dx, Dy, Dv_x, Dv_y, utilizando solver
    para calcular las variables phi y t.*/
    
    while(Distance(x0, y0) > R){
        /* Mientras la particula este fuera del radio efectivo del potencial(R)
        simplemente se evoluciona el sistema. */
        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, dt);
        t0 += dt;       
   }

    while(Distance(x0, y0) <= R){
        /* Mientras la particula este dentro del radio efectivo del potencial
        evoluciona el sistema y calcula el tiempo que le toma salir de esta
        region (t). */
        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, dt);
        t0 += dt;
        t += dt;      
   }
   // Una vez que haya salido del radio efectivo del potencial se calcula phi
   phi = atan(y0/x0);
}
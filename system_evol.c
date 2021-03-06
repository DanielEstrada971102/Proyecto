#include "headers/allvars.h"

double dt = 1e-2;
double phi, t; //phi:angulo de dispersion, t:tiempo dentro de la región R.

void path_particle(double Iconditions[], char *fileName){
    /* Esta funcion evoluciona el estado de la particula y escribe en el archivo
    "fileName" los datos correspondientes a la posicion en cada instante con su 
    respectiva velocidad*/

    double t0 = Iconditions[T];     //
    double x0 = Iconditions[X];     //
    double y0 = Iconditions[Y];     //--> Condiciones iniciales
    double vx_0 = Iconditions[VX];  //
    double vy_0 = Iconditions[VY];  //
    double E0 = Iconditions[En] * exp(-2);
    double E = E0;

    FILE *archivo; 
    archivo = fopen(fileName, "w");

    fprintf(archivo, "# t x y z vx vy E\n");
    fprintf(archivo, "%lf %lf %lf %lf %lf %.2e \n", t0, x0, y0, vx_0, vy_0, E -E0);

    while(Distance(x0, y0) > R){
        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, dt);
        t0 += dt;
        E = getEnergy(x0, y0, vx_0, vy_0);       
        fprintf(archivo, "%lf %lf %lf %lf %lf %.2e \n", t0, x0, y0, vx_0, vy_0, E - E0);
    }
    while(Distance(x0, y0) <= R){
        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, dt);
        t0 += dt;
        E = getEnergy(x0, y0, vx_0, vy_0);       
        fprintf(archivo, "%lf %lf %lf %lf %lf %.2e\n", t0, x0, y0, vx_0, vy_0, E - E0);
    }        

    fclose(archivo);
}
//==============================================================================
void scattering_variables(double Iconditions[]){
    /* Esta funcion evoluciona el estado de un particula a partir de las 
    ecuaciones diferencuales del sistema Dx, Dy, Dv_x, Dv_y utilizando solver.
    Esto para calcular las variables phi y t.*/
    double t0 = Iconditions[T];     //
    double x0 = Iconditions[X];     //
    double y0 = Iconditions[Y];     //--> Condiciones iniciales
    double vx_0 = Iconditions[VX];  //
    double vy_0 = Iconditions[VY];  //

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
        t += dt; // se cuanta el tiempo dentro de la region      
   }
   // Una vez que haya salido del radio efectivo del potencial se calcula phi
   phi = atan(y0/x0);
}
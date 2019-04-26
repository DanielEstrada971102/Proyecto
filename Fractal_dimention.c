#include "cabeceras/allvars.h"

void fractal_dimention(double eps, int *N, int *Nc, double t0, double x0, double y0, double vx_0, double vy_0, double E){

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

void liapunov_exponent(double t0, double x0, double y0, double vx_0, double vy_0, double E){
    double dx1, dy1, dr1, dr0 = 2e-2,  lambda;
    double x1, y1, vx1_0, vy1_0;
    double normalizacion;
    int cont=0;

    while(Distance(x0, y0) > R){
        /* Mientras la particula este fuera del radio efectivo del potencial(R)
        simplemente se evoluciona el sistema. */
        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, dt);
        t0 += dt;       
    }

    x1 = x0;
    y1 = y0 + dr0;
    vy1_0 = vy_0; 
    vx1_0 = velx(E, y1, x1); 
    
    while(Distance(x0, y0) <= R){
        /* Mientras la particula este dentro del radio efectivo del potencial
        evoluciona el sistema y calcula el tiempo que le toma salir de esta
        region (t). */
        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, dt);
        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x1, &y1, &vx1_0, &vy1_0, dt);
        t0 += dt;
        //printf("x0 = %lf x1 = %lf\n", x0, x1);
        dx1 = x1 - x0;
        dy1 = y1 - y0;

        dr1 = sqrt(dx1 * dx1 + dy1 * dy1);
        //printf("%lf\n", dr1);
        x1 = x0 + (dr1 / dr0) * dx1;
        y1 = y0 + (dr1 / dr0) * dy1;

        cont++;
        normalizacion += (dr1 / dr0);
        dr0 = dr1;     
    }
    //printf("%lf %d \n", normalizacion, cont);
    lambda = normalizacion / (dt*(cont-1));

    printf("exponente de Liapunov ---> %lf\n", lambda);
    
}
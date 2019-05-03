/*
    - solver aplica el metodo de integración RK4 para un sistema de
    ecuaciones diferenciales de primer grado dado de la forma:

    x' = f1(t, x, y, u, v)
    y' = f2(t, x, y, u, v)
    u' = f3(t, x, y, u, v)
    v' = f2(t, x, y, u, v)

    El metodo resuelve x(t_i+1), y(t_i+1), u(t_i+1), v(t_i+1) en pasos de tiempo
    dados por h, a partir de las condiciones iniciales x(t_i) = p1, y(t_i) = p2,
    u(t_i) = p3, v(t_i) = p4.

    Si se quiere resolver para a <= t <= b, se realiza un ciclo para ejecutar la 
    funció en pasos de h.
    Como los valores son pasados por referencia, es necesario almacenar el 
    resultado en cada paso pues al siguiente estos se sobrescriben.

    - Las ecuaciones diferenciales del sistema estan dadas por:

                    dr/dt = v & d²r/dt² = - grad(V)
    
    donde V = x²y²exp(-x²-y²). 
*/
#include "cabeceras/allvars.h"

//==============================================================================
//RK4
void solver(double (*f1)(double, double, double, double, double),
            double (*f2)(double, double, double, double, double),
            double (*f3)(double, double, double, double, double),
            double (*f4)(double, double, double, double, double),
            double *t, double *p1, double *p2, double *p3, double *p4, double h)
{
    double k11, k12, k13, k14, k21, k22, k23, k24, k31, k32, k33, k34, k41, k42, k43, k44;
    

    k11 = h * (*f1)(*t, *p1, *p2, *p3, *p4);
    k12 = h * (*f2)(*t, *p1, *p2, *p3, *p4);
    k13 = h * (*f3)(*t, *p1, *p2, *p3, *p4);
    k14 = h * (*f4)(*t, *p1, *p2, *p3, *p4);

    k21 = h * (*f1)(*t + .5 * h, *p1 + .5 * k11, *p2 + .5 * k12,
               *p3 + 0.5 * k13, *p4 + 0.5 * k14);
    k22 = h * (*f2)(*t + .5 * h, *p1 + .5 * k11, *p2 + .5 * k12,
               *p3 + 0.5 * k13, *p4 + 0.5 * k14);
    k23 = h * (*f3)(*t + .5 * h, *p1 + .5 * k11, *p2 + .5 * k12,
               *p3 + 0.5 * k13, *p4 + 0.5 * k14);
    k24 = h * (*f4)(*t + .5 * h, *p1 + .5 * k11, *p2 + .5 * k12,
               *p3 + 0.5 * k13, *p4 + 0.5 * k14);

    k31 = h * (*f1)(*t + 0.5 * h, *p1 + 0.5 * k21, *p2 + 0.5 * k22,
                    *p3 + 0.5 * k23, *p4 + 0.5 * k24);
    k32 = h * (*f2)(*t + 0.5 * h, *p1 + 0.5 * k21, *p2 + 0.5 * k22,
                    *p3 + 0.5 * k23, *p4 + 0.5 * k24);
    k33 = h * (*f3)(*t + 0.5 * h, *p1 + 0.5 * k21, *p2 + 0.5 * k22,
                    *p3 + 0.5 * k23, *p4 + 0.5 * k24);
    k34 = h * (*f4)(*t + 0.5 * h, *p1 + 0.5 * k21, *p2 + 0.5 * k22,
                    *p3 + 0.5 * k23, *p4 + 0.5 * k24);

    k41 = h * (*f1)(*t + h, *p1 + k31, *p2 + k32, *p3 + k33, *p4 + k34);
    k42 = h * (*f2)(*t + h, *p1 + k31, *p2 + k32, *p3 + k33, *p4 + k34);
    k43 = h * (*f3)(*t + h, *p1 + k31, *p2 + k32, *p3 + k33, *p4 + k34);
    k44 = h * (*f4)(*t + h, *p1 + k31, *p2 + k32, *p3 + k33, *p4 + k34); 

    *p1 = *p1 + (k11 + 2. * k21 + 2. * k31 + k41) / 6.;
    *p2 = *p2 + (k12 + 2. * k22 + 2. * k32 + k42) / 6.;
    *p3 = *p3 + (k13 + 2. * k23 + 2. * k33 + k43) / 6.;
    *p4 = *p4 + (k14 + 2. * k24 + 2. * k34 + k44) / 6.;
}
//==============================================================================
//Ecuaciones del sistema
double Dx(double t, double x, double y , double vx, double vy) 
{
    return vx;
}
double Dy(double t, double x, double y , double vx, double vy)
{
    return vy;
}
double Dv_x(double t, double x, double y , double vx, double vy) 
{    
    double x2, y2;
    x2 = x * x;
    y2 = y * y;
    return 2 * x * y2 * exp(-x2 - y2) * (x2 - 1) * 1/M;
}
double Dv_y(double t, double x, double y , double vx, double vy)
{   
    double x2, y2; 
    x2 = x * x;
    y2 = y * y;
    return 2 * y * x2 * exp(-x2 - y2) * (y2 - 1) * 1/M;
}
//==============================================================================
//Potencial
double V(double x, double y){
    return x * x * y * y * exp(-(x * x) - (y * y));
}
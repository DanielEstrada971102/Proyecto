/*
    Este archivo contiene los prototipos de:
    - La funcion solver, definida en el archivo "solver.c" que aplica el metodo
    de integracion RK4.
*/

void solver(double (*f1)(double, double, double, double, double),
            double (*f2)(double, double, double, double, double),
            double (*f3)(double, double, double, double, double),
            double (*f4)(double, double, double, double, double),
            double *t, double *p1, double *p2, double *p3, double *p4, double h);
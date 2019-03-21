/*
    Este archivo contiene los prototipos de:
    - La funcion solver, definida en el archivo "solver.c" que aplica el metodo
    de integracion RK4. Además contiene los prototipos de las ecuaciones diferenciales
    del sistema.
*/

// Ecuaciones
double Dx(double t, double x, double y, double v_x, double v_y);
double Dy(double t, double x, double y, double v_x, double v_y);
double Dv_x(double t, double x, double y, double v_x, double v_y);
double Dv_y(double t, double x, double y, double v_x, double v_y);
double V(double x, double y);
//RK4
void solver(double (*f1)(double, double, double, double, double),
            double (*f2)(double, double, double, double, double),
            double (*f3)(double, double, double, double, double),
            double (*f4)(double, double, double, double, double),
            double *t, double *p1, double *p2, double *p3, double *p4, double h);

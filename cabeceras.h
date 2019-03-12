/*
    Este archivo contiene los prototipos de:
    - La funcion solver, definida en el archivo "RK4.c"
    - Las funciones Dx, Dy, Dv_x, Dv_y, definidas en el archivo "Ecuaciones.c"
    correspode a las ecuaciones que seran integradas a partir de solver.
*/

double Dx(double t, double x, double y, double v_x, double v_y);
double Dy(double t, double x, double y, double v_x, double v_y);
double Dv_x(double t, double x, double y, double v_x, double v_y);
double Dv_y(double t, double x, double y, double v_x, double v_y);
void Solver(double (*f1)(double, double, double, double, double),
            double (*f2)(double, double, double, double, double),
            double (*f3)(double, double, double, double, double),
            double (*f4)(double, double, double, double, double),
            double *t, double *p1, double *p2, double *p3, double *p4, double h);
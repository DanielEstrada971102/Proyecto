/*
    Este archivo contiene los prototipos de:
    - Las funciones Dx, Dy, Dv_x, Dv_y, definidas en el archivo "ecuaciones.c"
    correspode a las ecuaciones que seran integradas a partir de solver.
*/

double Dx(double t, double x, double y, double v_x, double v_y);
double Dy(double t, double x, double y, double v_x, double v_y);
double Dv_x(double t, double x, double y, double v_x, double v_y);
double Dv_y(double t, double x, double y, double v_x, double v_y);

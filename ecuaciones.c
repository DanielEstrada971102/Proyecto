//Ecuaciones diferenciales 
# include <math.h>
#define M 1 //masa de la particula
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


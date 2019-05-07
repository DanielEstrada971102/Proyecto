// prototipos de "chaotic_variables.c"
void fractal_dimention(double eps, int *N, int *Nc, double Iconditions[], double E);
double lyapunov_exponent(double Iconditions[], double E, double d_0, int n);
int nIrregular_Points(double Iconditions[], double E, double bmin, double bmax, double db, double dphi);
int get_irregulars_points(double Iconditions[], double E, double bmin, double bmax, double db, double dphi, double b[]);
double lyapunov_exponent2(double Iconditions[],double E, double d_0, double a);
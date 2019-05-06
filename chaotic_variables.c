#include "cabeceras/allvars.h"

void fractal_dimention(double eps, int *N, int *Nc, double Iconditions[], double E){

    double phi1, phi2;
    double b = -.6;
    int i = 0, j = 0; // i es un contador del numero de parametros de impacto y
    // j es un contador del numero de parametros para el cual es caotico.
    Iconditions[Y] = b;
    Iconditions[VX] = velx(E, b, Iconditions[X]);
    scattering_variables(Iconditions);
    while(b < -.1){
        //cada ciclo corresponde a un parametro de impacto(b) distinto. 
        i ++;
        phi1 = phi;
        b+= eps;
        Iconditions[Y] = b;
        Iconditions[VX] = velx(E, b, Iconditions[X]);
        scattering_variables(Iconditions);
        phi2 = phi;

        if (abs(phi2 - phi1) > .2)
            j++;
    }
    *N = i;
    *Nc = j;
}
//==============================================================================
double lyapunov_exponent(double Iconditions[],double E, double d_0, int n){
    /*Esta funcion hace el calculo del exponente de lyapunov para un par de
    trayectorias se paradas una distancia d0, la curtva dada por las condiciones 
    iniciales "Iconditions" es en este caso la "fidutial trajectory". El calculo 
    lo hace con "n" iteraciones */
    double t0 = Iconditions[T];     //
    double x0 = Iconditions[X];     //
    double y0 = Iconditions[Y];     //--> Condiciones iniciales
    double vx_0 = Iconditions[VX];  //
    double vy_0 = Iconditions[VY];  //

    // variables para el calculo.
    double dx1, dy1, dr1, dr0 = d_0, lambda;
    double x1, y1, vx1_0, vy1_0;
    double sum = 0;
    int i = 0;

    // Se evoluciona el sistema hasta que este en la region del potencial
    while(Distance(x0, y0) > (R-0.2)){

        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, dt);
        t0 += dt;       
    }

    // se establecen las condiciones iniciales de la segunda trayectoria separa d0
    x1 = x0;
    y1 = y0 + dr0;
    vy1_0 = vy_0; 
    vx1_0 = velx(E, y1, x1);

    for (i; i < n; i++){
        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, dt);
        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x1, &y1, &vx1_0, &vy1_0, dt);
        t0 += dt;

        dx1 = x1 - x0;
        dy1 = y1 - y0;
        dr1 = sqrt(dx1 * dx1 + dy1 * dy1);

        // se redefinene para que en cada paso las trayecotrias siempre esten separadas d0
        x1 = x0 + (dr0 / dr1) * dx1;
        y1 = y0 + (dr0 / dr1) * dy1;

        sum += log2(dr1 / dr0);
    }

    lambda = sum / (dt*(i-1));

    return lambda;   
}
//==============================================================================
int nPuntos_Irregulares(double Iconditions[], double E, double bmin, double bmax, double db, double dphi){
    /*Esta funcion calcula cuantos de los parametros de impactos en el intevalo
    [bmin, bmax] son irregulares(caoticos), los b se estudian en intervalos de db
    y la condicion para que sea o no caotico un punto es que los angulos de dispersion
    respectivos difieran en dphi.*/
    int nP_Irreg = 0;
    double phi1, phi2;

    Iconditions[Y] = bmin;
    Iconditions[VX] = velx(E, bmin, Iconditions[X]);
    
    scattering_variables(Iconditions);

    for (double b = bmin + db; b < bmax; b += db){
        //cada ciclo corresponde a un parametro de impacto(b) distinto.
        phi1 = phi;
        
        Iconditions[Y] = b;
        Iconditions[VX] = velx(E, b, Iconditions[X]);

        scattering_variables(Iconditions);
        
        phi2 = phi;

        if (abs(phi2 - phi1) > dphi)
            nP_Irreg++;
    }
    
    return nP_Irreg; 
}
//==============================================================================
int get_puntos_Irregulares(double Iconditions[], double E, double bmin, double bmax, double db, double dphi, double p[]){
    /*Esta funcion barre el intervalo de paramatros de impacto [bmin, bmax] y 
    almacena en el arreglo "p" los que sean caoticos.*/
    double phi1, phi2;
    int i = 0;
    
    Iconditions[Y] = bmin;
    Iconditions[VX] = velx(E, bmin, Iconditions[X]);

    scattering_variables(Iconditions);

    for (double b = bmin + db; b < bmax; b += db){
        //cada ciclo corresponde a un parametro de impacto(b) distinto.
        phi1 = phi;

        Iconditions[Y] = b;
        Iconditions[VX] = velx(E, b, Iconditions[X]);
        
        scattering_variables(Iconditions);
        
        phi2 = phi;

        if (abs(phi2 - phi1) > .2){
            p[i] = b;
            i++;
        }
    }
    return 0; 
}

double lyapunov_exponent2(double Iconditions[],double E, double d_0, double a){
    double t0 = Iconditions[T];     //
    double x0 = Iconditions[X];     //
    double y0 = Iconditions[Y];     //--> Condiciones iniciales
    double vx_0 = Iconditions[VX];  //
    double vy_0 = Iconditions[VY];  //

    // variables para el calculo.
    double dx, dy, dr, lambda;//dr0 = d_0
    double x1, y1, vx1_0, vy1_0;
    int i = 0, n = 1000;
    t = 0;

    // Se evoluciona el sistema hasta que este en la region del potencial
    while(Distance(x0, y0) > (R-0.2)){

        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, dt);
        t0 += dt;       
    }

    // se establecen las condiciones iniciales de la segunda trayectoria separa d0
    x1 = x0;
    y1 = y0 + d_0;
    vy1_0 = vy_0; 
    vx1_0 = velx(E, y1, x1);

    while(1 && i != n){
        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x0, &y0, &vx_0, &vy_0, dt);
        solver(Dx, Dy, Dv_x, Dv_y, &t0, &x1, &y1, &vx1_0, &vy1_0, dt);
        t = t0;
        dx = x1 - x0;
        dy = y1 - y0;
        dr = sqrt(dx * dx + dy * dy);

        if (dr > a){
            return t;
        }
        
        t0 += dt;
    }

    return 0;   
} 
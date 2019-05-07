#include "headers/allvars.h"

//Funcion principal
int main(int argc, char const *argv[]){
    int option;
    double b, bmin, bmax, db;
    double Iconditions[6];
    char comentario = '#';
    char *nombreParametro[6], sys[30];
    double maxEnergy;              
    double totalEnergy;    

    nombreParametro[0] = "t0";
    nombreParametro[1] = "x0";
    nombreParametro[2] = "y0";
    nombreParametro[3] = "vx0"; 
    nombreParametro[4] = "vy0";
    nombreParametro[5] = "E";
    
    // Se establecen las condiciones iniciales a partir dela archivo de parametros.
    read_Iconditions(nombreParametro, "parametros.dat", comentario, Iconditions);
                                    
    maxEnergy = M * exp(-2);        
    totalEnergy = Iconditions[En] * maxEnergy; 
    
    // Opciones que el usuario puede elegir====================================
    printf("Press:\n");
    printf("1. For calculating four trajectories with similars impact parameters.\n");
    printf("2. For calculating the scattering angle(phi) and the escape time(t) as function of the impact parameter (b).\n");
    printf("3. For calculating the number of irregular points depending on the initial energy of the system.\n");
    //printf("4. For calculating the fractal dimention.\n");
    printf("4. For calculating de Liapunov exponet.\n");
    printf("- Press any other key for not execute nothing.\n");
    scanf("%d", &option);
    //=========================================================================
    //Se calculan 4 trayectorias con parametros de impacto similares para ver el
    //caracter caotico del sistema.
    if (option == 1){    
        printf("Enter an impact parameter (b): \n");
        scanf("%lf", &b); 

        for (int i = 0; i < 4; i++){
            char fileName[40];

            sprintf(fileName, "results/Trayectoria_%d.txt",i);
        
            Iconditions[Y] = b;
            Iconditions[VX] = velx(totalEnergy, b, Iconditions[X]);
            
            path_particle(Iconditions, fileName);
            b += 1e-4;
        }
        sprintf(sys, "python graphics.py %d %.4lf %.4lf %.4lf %.4lf %.2lf", option, b, b + 1e-4, b + 2e-4, b + 3e-4, Iconditions[En]);
        system(sys);
    }
    //==========================================================================
    // se calcula phi y t para b en [bmin : bmax] en pasos db
    if(option == 2){
        printf("Enter bmin, bmax and db: \n");
        scanf("%lf %lf %lf", &bmin, &bmax, &db);

        char fileName2[] = "results/S_variables.txt";

        FILE *archivo = fopen(fileName2, "w");

        fprintf(archivo, "# b phi t \n");
        for (b = bmin; b < bmax; b += db){
            //cada ciclo corresponde a un parametro de impacto(b) distinto.
            t = 0; 
            
            Iconditions[Y] = b;
            Iconditions[VX]= velx(totalEnergy, b, Iconditions[X]);
            scattering_variables(Iconditions);

            fprintf(archivo, "%lf %lf %lf \n", b, phi, t); 
        }

        fclose(archivo);
        sprintf(sys, "python graphics.py %d %.2lf", option, Iconditions[En]);
        system(sys);
    }
    //==========================================================================
    // Se calcula el numero de puntos irregulares(caoticos) para energias del 
    // sistema en en el intervalo [0, 2*E_maxima]
    if(option == 3){
        int nP_Irreg;

        char fileName2[] = "results/nPuntos_energy.txt";
        FILE *archivo = fopen(fileName2, "w");

        printf("Enter bmin, bmax and db: \n");
        scanf("%lf %lf %lf", &bmin, &bmax, &db);

        fprintf(archivo, "# E nIrregular_Points \n");
        
        for (double E = 0; E < 2 * maxEnergy; E += .01 * maxEnergy){
            nP_Irreg = nIrregular_Points(Iconditions, E, bmin, bmax, db, .2);
            fprintf(archivo, "%lf %d \n", E/maxEnergy, nP_Irreg);            
        }
        
        fclose(archivo);
        sprintf(sys, "python graphics.py %d", option);
        system(sys);
    }
    //==========================================================================        
    // Se calcula la dimension fractal_dimention

    // Este metodo fue conjeturado en un articulo por lo tanto no se presenta en 
    // los results finales del proyecto, sin embargo, no se elimina del codigo
    // para una posible corroboracion futura.

    if(option == 5){
        int k = 0;
        double c0, c1, cov00, cov01, cov11, sumq; //variables para gsl
        double logEPS[50];
        double logF[50];
        double D;

        for (double eps = 1e-5; eps < 1e-2; eps+= 2e-4){
            int N = 0, Nc = 0;
            logEPS[k] = log10(eps);
            fractal_dimention(eps, &N, &Nc, Iconditions, totalEnergy);
            logF[k] = log10( (double) N / Nc);
            k++ ;
        }
        gsl_fit_linear(logEPS, 1, logF, 1, 50, &c0, &c1, &cov00, &cov01, &cov11, &sumq);

        D = 1 - c1;
        printf("La dimensión fractal es %lf \n", D);

    }
    //==========================================================================
    // Se culcula el exponente de liapunov para diferentes valores de b.

    // Este metodo si esta verificado y esta basado en libros de texto, sin embargo,
    // para el sistema que se esta trabjando presenta fallas por no tener atractores.
    // como en el caso anterior no se elimina del codigo pues el algoritmo esta 
    // bien programado.

    if (option == 6){   
        printf("Enter bmin, bmax and db: \n");
        scanf("%lf %lf %lf", &bmin, &bmax, &db);
        double lambda;
        int n = nIrregular_Points(Iconditions, totalEnergy, bmin, bmax, db, .2);
        double b[n];

        get_irregulars_points(Iconditions, totalEnergy, bmin, bmax, db, .2, b);
        
        for (int i = 0; i < n; i++){
            Iconditions[Y] = b[i];
            Iconditions[VX] = velx(totalEnergy, b[i], Iconditions[X]);
            lambda = lyapunov_exponent(Iconditions, totalEnergy, 2e-2, 1000);
            printf("b = %lf, Lambda = %lf\n", b[i], lambda);
        }   
    }
    //==========================================================================
    // Se culcula el exponente de liapunov para diferentes valores de b con el segundo metodo.
    //Este es el metodo utilizado para presentar en el resultado final del proyecto.
    if (option == 4){   
        printf("Enter bmin, bmax y db: \n");
        scanf("%lf %lf %lf", &bmin, &bmax, &db);
        double th, a = 1e-3, d0 = 2e-6;
        int n = nIrregular_Points(Iconditions, totalEnergy, bmin, bmax, db, .2);
        double b[n];
        double lambda = 0;    

        get_irregulars_points(Iconditions, totalEnergy, bmin, bmax, db, .2, b);
        
        for (int i = 0; i < n; i++){
            Iconditions[Y] = b[i];
            Iconditions[VX] = velx(totalEnergy, b[i], Iconditions[X]);
            th = lyapunov_exponent2(Iconditions, totalEnergy, d0, a);
            lambda += 1/th * log(a / d0);
        }

        printf("Exponente de lyapunov = %.3lf\n", lambda / n);
    }


    return 0;
}



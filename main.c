#include "cabeceras/allvars.h"

//Funcion principal
int main(int argc, char const *argv[]){
    int option;
    printf("Press:\n");
    printf("1. For calculate four trajectories with similars impact parameters.\n");
    printf("2. For calculate the scattering angle(phi) and the escape time(t) in function of the impact parameter (b).\n");
    printf("3. For calculate the scattering angle and the escape time in function of the impact parameter for several values of initial energy.\n");
    printf("4. For calculate the fractal dimention.\n");
    printf("5. For calculate de Liapunov exponet.\n");
    printf("- Press any other key for not execute nothing.\n");
    scanf("%d", &option);
        
    double t0 = 0, x0 = -5 * R, b = -0.5, vx_0, vy_0 = 0;  //condiciones iniciales
    double maxEnergy = M * exp(-2);
    double totalEnergy = 0.26 * maxEnergy;



    //Se calculan 4 trayectorias con parametros de impacto similares para ver el
    //caracter caotico del sistema.
    if (option == 1){    
        for (int i = 0; i < 4; i++){
            char fileName[40];

            sprintf(fileName, "resultados/Trayectoria_%d.txt",i);
            //x0 = getXPosition(totalEnergy, b);
            vx_0 = velx(totalEnergy, b, x0);
            path_particule(t0, x0, b, vx_0, vy_0, fileName);
            b += 1e-4;
        }
    }
    //==========================================================================
    // se calcula phi y t para b en [-.6 : -.1]
    if(option == 2){
        char fileName2[] = "resultados/S_variables.txt";

        FILE *archivo = fopen(fileName2, "w");

        fprintf(archivo, "# b phi t \n");
        for (b = -.6; b < -.1; b += 2e-5){
            //cada ciclo corresponde a un parametro de impacto(b) distinto.
            t = 0; 
            //x0 = getXPosition(totalEnergy, b);
            vx_0 = velx(totalEnergy, b, x0);
            scattering_variables(t0, x0, b, vx_0, vy_0);
            fprintf(archivo, "%lf %lf %lf \n", b, phi, t); 
        }

        fclose(archivo);
    }
    //==========================================================================
    // se calcula phi y t para b en [-.6 : -.1] vaiando la energia del sistema
    if (option == 3){
        double E;
        for (int i=1; i<=20 ; i+=2){
            E = i* .1 * maxEnergy;
            char fileName3[40];

            sprintf(fileName3, "resultados/S_variables_E=%.2lf.txt",E);

            FILE *archivo = fopen(fileName3, "w");

            fprintf(archivo, "# b phi t \n");
            for (b = -1; b < -.1; b += 2e-4){
                //cada ciclo corresponde a un parametro de impacto(b) distinto.
                t = 0; 
                //x0 = getXPosition(E, b);
                vx_0 = velx(E, b, x0);
                scattering_variables(t0, x0, b, vx_0, vy_0);
                fprintf(archivo, "%lf %lf %lf \n", b, phi, t); 
            }

            fclose(archivo); 
        }
    }
    // Se calcula la dimension fractal
    if(option == 4){
        int k = 0;
        double c0, c1, cov00, cov01, cov11, sumq; //variables para gsl
        double logEPS[50];
        double logF[50];
        double D;

        for (double eps = 1e-5; eps < 1e-2; eps+= 2e-4){
            int N = 0, Nc = 0;
            logEPS[k] = log10(eps);
            fractal_dimention(eps, &N, &Nc, t0, x0, b, vx_0, vy_0, totalEnergy);
            logF[k] = log10( (double) N / Nc);
            k++ ;
        }
        gsl_fit_linear(logEPS, 1, logF, 1, 50, &c0, &c1, &cov00, &cov01, &cov11, &sumq);

        D = 1 - c1;
        printf("La dimensión fractal es %lf \n", D);

    }

    if (option == 5)
    {   
        for (double b = -.6; b < -.1; b += 2e-2)
        {
            printf("%lf\n", b);
            vx_0 = velx(totalEnergy, b, x0);
            liapunov_exponent(t0, x0, b, vx_0, vy_0, totalEnergy);
        }
        
    }

    return 0;
}

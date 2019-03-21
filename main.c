#include "cabeceras/allvars.h"

//Funcion principal
int main(int argc, char const *argv[]){
    int option;
    printf("Press 1 for calculate the trajectories or 2 for calculate phi & T vs b. Press any key for execute everything.\n");
    scanf("%d", &option);

    double t0 = 0, x0, vx_0, vy_0 = 0;  //condiciones iniciales
    double maxEnergy = exp(-2);

    //Se calculan 4 trayectorias con parametros de impacto similares para ver el
    //caracter caotico del sistema.
    double b = -0.42;
    
    for (int i = 0; i < 4; i++){
        if(option == 2) 
            break;
        char fileName[20];

        sprintf(fileName, "resultados/Trayectoria_%d.txt",i);
        x0 = getXPosition(0.1 * maxEnergy, b);
        vx_0 = velx(0.1 * maxEnergy, b, x0);
        path_particule(t0, x0, b, vx_0, vy_0, fileName);
        b += 1e-4;
    }
    //==========================================================================
    // se calcula phi y t para varios valores de b }
    double E;
    for (int i=1; i<11 ; i+=2){
        E = i*.1*exp(-2);
        if(option == 1) 
            break;
        char fileName2[40];

        sprintf(fileName2, "resultados/S_variables_E=%.2lf.txt",E);

        FILE *archivo = fopen(fileName2, "w");

        fprintf(archivo, "# b phi t \n");
        for (b = -.6; b < -.1; b += 2e-4){
            //cada ciclo corresponde a un parametro de impacto(b) distinto.
            t = 0; 
            x0 = getXPosition(E, b);
            vx_0 = velx(E, b, x0);
            scattering_variables(t0, x0, b, vx_0, vy_0);
            fprintf(archivo, "%lf %lf %lf \n", b, phi, t); 
        }

        fclose(archivo); 
    }
    return 0;
}

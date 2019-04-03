#include "cabeceras/allvars.h"

//Funcion principal
int main(int argc, char const *argv[]){
    int option;
    printf("Press:\n");
    printf("1. For calculate four trajectories with similars impact parameters.\n");
    printf("2. For calculate the scattering angle(phi) and the escape time(t) in function of the impact parameter (b).\n");
    printf("3. For calculate the scattering angle and the escape time in function of the impact parameter for several values of initial energy.\n");
    printf("- Press any other key for execute everything.\n");
    scanf("%d", &option);

    double t0 = 0, x0, vx_0, vy_0 = 0;  //condiciones iniciales
    double maxEnergy = exp(-2);
    double totalEnergy = .26 * maxEnergy;

    //Se calculan 4 trayectorias con parametros de impacto similares para ver el
    //caracter caotico del sistema.
    double b = -0.42;
    
    for (int i = 0; i < 4; i++){
        if(option == 2 || option == 3) 
            break;
        char fileName[40];

        sprintf(fileName, "resultados/Trayectoria_%d.txt",i);
        x0 = getXPosition(totalEnergy, b);
        vx_0 = velx(totalEnergy, b, x0);
        path_particule(t0, x0, b, vx_0, vy_0, fileName);
        b += 1e-4;
    }
    //==========================================================================
    // se calcula phi y t para b en [-.6 : -.1]
    if(option == 2){
        char fileName2[] = "resultados/S_variables.txt";

        FILE *archivo = fopen(fileName2, "w");

        fprintf(archivo, "# b phi t \n");
        for (b = -.6; b < -.1; b += 2e-4){
            //cada ciclo corresponde a un parametro de impacto(b) distinto.
            t = 0; 
            x0 = getXPosition(totalEnergy, b);
            vx_0 = velx(totalEnergy, b, x0);
            scattering_variables(t0, x0, b, vx_0, vy_0);
            fprintf(archivo, "%lf %lf %lf \n", b, phi, t); 
        }

        fclose(archivo);
    }
    //==========================================================================
    // se calcula phi y t para b en [-.6 : -.1] vaiando la energia del sistema
    double E;
    for (int i=1; i<=13 ; i+=3){
        E = i* .1 * maxEnergy;
        if(option == 1 || option == 2) 
            break;
        char fileName3[40];

        sprintf(fileName3, "resultados/S_variables_E=%.2lf.txt",E);

        FILE *archivo = fopen(fileName3, "w");

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

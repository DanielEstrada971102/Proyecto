#include "cabeceras/allvars.h"

//==============================================================================
double velx(double totalEnergy, double b, double x0){
    /*Esta funcion calcula la velocidad a patir de la ligadura del problema que 
    surge al imponer conservacion de la energia. */
    return sqrt( 2 * (totalEnergy - V(x0, b)) * 1/M);
}
//==============================================================================
double getEnergy(double x, double y, double vx, double vy){
    /*Esta función calcula la energía total de la particula*/
    double v,E;
    v = sqrt(vx *vx + vy * vy);
    E = M * V(x, y) + .5 * M * v * v;  

    return E;
}
//==============================================================================
void read_Iconditions(char *nombreParametro[6], char *filename, char comentario, double *Iconditions){
    /*Esta funcion lee el archivo de parametros "filename" el cual contiene las
    condicines inciales del sistema y las almacena en "Iconditions"*/
    int nLineasArchivo = 0;
    char c;
    // se cuenta el numero de lineas del archivo
    FILE *fInfile=fopen(filename, "r");
    int i, j;
    
    while( (c=fgetc(fInfile)) != EOF ){
        if( c == '\n' )
            nLineasArchivo++;
    }
    // en D se almacena todo el contenido del archivo
    char D[nLineasArchivo][1000];
    int ignorar[nLineasArchivo];

    rewind(fInfile);

    for( i=0; i<nLineasArchivo; i++ ){
        j = ignorar[i] = 0;

        // detecta las lineas en blanco y las que debe ignorarse
        if( (c = fgetc(fInfile)) == '\n'  ){
            ignorar[i] = 1;
            D[i][j] = c;
            continue;
        }
        else{
            D[i][j++] = c;
            // se ignora las lineas que inicien con el simbolo de comentario y el EOF
            if( (c == comentario) || (c == EOF) )
            ignorar[i] = 1;

            while( (c = fgetc(fInfile)) != '\n' )
                D[i][j++] = c;
        }

        D[i][j] = '\0';
    }
    // se estrae la informacion de las lineas que no se van a ignorar.
    for (i = 0; i < nLineasArchivo; i++){
        if(ignorar[i] == 0){
            char string1[300], string2[300], dummy[300];
            sscanf(D[i], "%s %s %s", string1, string2, dummy);

            for (j = 0; j < 6; j++){
                if (strcmp(string1, nombreParametro[j]) == 0)
                    break;
            }
            Iconditions[j] = atof(string2);
        }
    }
}

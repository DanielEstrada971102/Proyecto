# Proyecto

#########################################################################################################################
#########################################################################################################################
#####                                                                                                               #####
##### Para compilar, desde la terminal hay que ubicarse en el directorio del código y ejecutar "make", para limpiar #####
##### los archivos se ejecuta "make clean", para correr el código hay que asegurarse de que exista una carpeta      #####
##### con el nombre "results" en el mismo directorio del código pues todas las salidas del programa se guardan      #####
##### en esta carpeta.                                                                                              #####
#########################################################################################################################
#########################################################################################################################

Cada módulo está compuesto por dos archivos, los archivos .h contienen los prototipos de las funciones 
que se definen luego en los archivos .c

  MODULOS:
    - initial_conditions: Este modulo contiene la rutina que a partir de un archivo de parametros asigna las 
    condiciones iniciales del sistema, además contiene una funcion para calcular la velocidad inicial 
    dependiendo del valor de energia inicial que quiera garantizarse y otra para calcular la energía en cualquier t.

    - solver: aca se encuentra la rutina que aplica el metodo de integracion RK4 para evolucionar el estado de sistema,
    el metodo Rk4 se aplica al sistema de ecuacion definido en el mismo modulo(Dx, Dy, Dvx, Dvy).

    - system_evol: En este modulo se programa la rutina que contruye la trayectoria de la particula y además otra
    que calcula las variables de dispersion phi y t_e.
    
    - chaotic_variables: Este modulo contiene los metodos y funciones para hacer calculo de las variables 
    caoticas del sistema. En el se encuentran funciones para calcular por ejemplo el exponente de lyapunov,
    la dimensión fractal y el numero de puntos caoticos en el sistema.

    - main: es el archivo principal del programa. Al iniciarse se establecen las condiciones del sistema a partir de
     un archivo de parametros, luego despliega un menú con cuatro opciones: 1. Calcular
     cuatro trayectorias con parametros de impacto similares. 2. Calcular el ángulo de dispersión y el
     tiempo que la partícula permanece dentro del potencial en funcion del parámetro de impacto.
     3. Calcular numero de puntos irregulares del sistema en funcion de la energia inicial suministrada. 4. Calcular 
     el exponente de lyapunov del sistema.

  CONDICIONES INICIALES:
    - Las condiciones iniciales del sistema pueden ser modificadas desde el archivo "parametros.dat"
  
  SALIDAS:
    - todos los resultados de las tres primeras opciones mostradas al ejecutar el programa se retornar en un archivo a 
    la carpeta "results", el programa esta codificado para tomar estos archivos y realizar las correspondientes graficas 
    a partir de scripts de python. La ultima opción del programa retorna el valor del exponente de lyapunov en pantalla.
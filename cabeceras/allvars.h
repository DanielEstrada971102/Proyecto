#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//#include<ctype.h>
#include<string.h>
#include <gsl/gsl_fit.h>

#include "system_evol.h"
#include "initial_conditions.h"
#include "solver.h"
#include "chaotic_variables.h"

#define Distance(x, y) (sqrt((x) * (x) + (y) * (y)))
#define M 1 //masa de la particula
#define R sqrt(9) // define una region efectiva del potencial de radio R.
#define T 0
#define X 1
#define Y 2
#define VX 3
#define VY 4
#define En 5


extern double dt, t, phi; //declaradas en system_evol.c

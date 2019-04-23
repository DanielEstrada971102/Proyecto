#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_fit.h>

#include "system_evol.h"
#include "initial_conditions.h"
#include "solver.h"
#include "Fractal_dimention.h"

#define Distance(x, y) (sqrt((x) * (x) + (y) * (y)))
#define M 1 //masa de la particula
#define R sqrt(9) // define una region efectiva del potencial de radio R.

extern double dt, t, phi; //declaradas en system_evol.c

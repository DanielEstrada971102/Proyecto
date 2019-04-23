CC = gcc
GFLAGS=-I. -Wall 
LFLAGS= -lgsl -lgslcblas -lm
OBJS= main.o initial_conditions.o solver.o system_evol.o Fractal_dimention.o
EXE= chaoticScattering.out

compiler: $(OBJS)
	$(CC) $(GFLAGS) $(OBJS) $(LFLAGS) -o $(EXE)
	rm $(OBJS)
clean:
	rm *.out resultados/*.txt

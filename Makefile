
cc = gcc
GFLAGS=-I. -Wall 
LFLAGS= -lm
OBJS= main.o initial_conditions.o solver.o system_evol.o
EXE= chaoticScattering.out

compiler: $(OBJS)
	$(CC) $(GFLAGS) $(OBJS) $(LFLAGS) -o $(EXE)
	rm $(OBJS)
clean:
	rm *.out resultados/*.txt

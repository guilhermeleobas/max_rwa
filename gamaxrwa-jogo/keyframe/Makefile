CC = c++ -Wall -static
OBJS = chronometer.o bibrand.o mutation.o crossover.o random.o biased.o ga.o

keyFrame.a: $(OBJS)
	ar rc libfw.a $(OBJS)

chronometer.o: chronometer.h chronometer.cc
	$(CC) -c chronometer.cc

bibrand.o: bibrand.h bibrand.cc
	$(CC) -c bibrand.cc

mutation.o: mutation.h mutation.cc
	$(CC) -c mutation.cc

crossover.o: crossover.h crossover.cc bibrand.o
	$(CC) -c crossover.cc

random.o: random.h random.cc mutation.o bibrand.o
	$(CC) -c random.cc

biased.o: biased.h biased.cc crossover.o bibrand.o
	$(CC) -c biased.cc

ga.o: ga.h ga.cc biased.o random.o crossover.o mutation.o evaluator.h
	$(CC) -c ga.cc

clean:
	rm *.o *.a *~

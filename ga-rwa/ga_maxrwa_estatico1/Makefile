CC = c++ -Wall  #-pg  -O3

LIBS = -L ../keyframe -l fw
OBJS = graph.o instance.o solution.o binrwa.o

prog: $(OBJS) ../keyframe/libfw.a
	$(CC) $(OBJS) main.cc -o rwa $(LIBS)

graph.o: graph.h graph.cc
	$(CC) -c graph.cc

instance.o: instance.h instance.cc graph.o
	$(CC) -c instance.cc

solution.o: solution.h solution.cc instance.o
	$(CC) -c solution.cc

binrwa.o: binrwa.h binrwa.cc instance.o solution.o quicksort.h
	$(CC) -c binrwa.cc

clean:
	rm *.o rwa *~ -f

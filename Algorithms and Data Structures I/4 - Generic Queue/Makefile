objects = queue.o main.o

stack : $(objects)
	gcc -o queue $(objects)


queue.o : queue.h
main.o  : queue.h

clean : 
	rm *.o 
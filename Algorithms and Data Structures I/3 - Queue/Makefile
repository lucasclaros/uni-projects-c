objects = stack.o main.o

stack : $(objects)
	gcc -o stack $(objects)


stack.o : stack.h
main.o  : stack.h

clean : 
	rm *.o 
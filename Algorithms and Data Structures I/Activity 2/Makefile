name = ex2
headers = primeNumbers.h list.h
files = primeNumbers.c main.c list.c
objects = primeNumbers.o main.o list.o

$(headers): $(objects)

all : $(objects)
	gcc -c $(files) -g
	gcc -o $(name) $(objects) -g

run : all
	./$(name)

zip : 
	zip -r $(name) $(headers) $(files) Makefile
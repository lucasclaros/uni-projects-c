name = ex9
headers = list.h bignum.h
files = main.c list.c bignum.c
objects = main.o list.o bignum.o

$(headers): $(objects)

all : $(objects)
	gcc -c $(files) -g
	gcc -o $(name) $(objects) -g

run : all
	./$(name)

zip : 
	zip -r $(name) $(headers) $(files) Makefile
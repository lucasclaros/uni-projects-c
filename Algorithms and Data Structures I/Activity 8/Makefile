name = ex8
headers = list.h listPoly.h
files = main.c list.c listPoly.c
objects = main.o list.o listPoly.o

$(headers): $(objects)

all : $(objects)
	gcc -c $(files) -g
	gcc -o $(name) $(objects) -g

run : all
	./$(name)

zip : 
	zip -r $(name) $(headers) $(files) Makefile
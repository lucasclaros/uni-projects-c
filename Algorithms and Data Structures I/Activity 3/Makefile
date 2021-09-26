name = ex3
headers = queue.h commands.h
files = commands.c main.c queue.c
objects = commands.o main.o queue.o

$(headers): $(objects)

all : $(objects)
	gcc -c $(files) -g
	gcc -o $(name) $(objects) -g

run : all
	./$(name)

zip : 
	zip -r $(name) $(headers) $(files) Makefile
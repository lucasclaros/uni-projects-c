name = ex3
headers = list.h commands.h 
files = main.c list.c commands.c
objects = main.o list.o commands.o

$(headers): $(objects)

all : $(objects)
	gcc -c $(files) -g
	gcc -o $(name) $(objects) -g

run : all
	./$(name)

zip : 
	zip -r $(name) $(headers) $(files) Makefile
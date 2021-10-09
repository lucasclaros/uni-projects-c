name = ex5
headers = stack.h commands.h
files = main.c stack.c commands.c
objects = main.o stack.o commands.o

$(headers): $(objects)

all : $(objects)
	gcc -c $(files) -g
	gcc -o $(name) $(objects) -g

run : all
	./$(name)

zip : 
	zip -r $(name) $(headers) $(files) Makefile
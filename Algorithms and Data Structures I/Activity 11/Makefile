name = ac11
headers = bst.h commands.h
files = main.c bst.c commands.c
objects = main.o bst.o commands.o

$(headers): $(objects)

all : $(objects)
	gcc -c $(files) -g
	gcc -o $(name) $(objects) -g

run : all
	./$(name)

zip : 
	zip -r $(name) $(headers) $(files) Makefile
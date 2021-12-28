name = pj2
headers = treap.h commands.h
files = main.c treap.c commands.c
objects = main.o treap.o commands.o

$(headers): $(objects)

all : $(objects)
	gcc -c $(files) -g
	gcc -o $(name) $(objects) -g

run : all
	./$(name)

zip : 
	zip -r $(name) $(headers) $(files) Makefile
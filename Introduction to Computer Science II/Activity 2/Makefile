name = ac2
headers = commands.h
files = main.c commands.c
objects = main.o commands.o

$(headers): $(objects)

all : $(objects)
	gcc -c $(files) -g -lm
	gcc -o $(name) $(objects) -g -lm

run : all
	./$(name)

zip : 
	zip -r $(name) $(headers) $(files) Makefile
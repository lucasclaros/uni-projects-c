name = ex7
headers = skipList.h commands.h
files = main.c skipList.c commands.c
objects = main.o skipList.o commands.o

$(headers): $(objects)

all : $(objects)
	gcc -c $(files) -g
	gcc -o $(name) $(objects) -g

run : all
	./$(name)

zip : 
	zip -r $(name) $(headers) $(files) Makefile
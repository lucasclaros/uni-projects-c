name = ex4
objects = main.o commands.o queue.o
files = main.c commands.c queue.c

commands.h : main.o commands.o
queue.h : main.o queue.o

files:
	gcc -c -Wall $(files) -g

all : files $(objects)
	gcc -o $(name) $(objects) -g

run : all
	./$(name)
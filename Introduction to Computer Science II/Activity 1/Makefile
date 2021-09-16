name = main
headers = minesweeper.h
objects = minesweeper.o main.o

$(headers): $(objects)

all : $(objects)
	gcc -o $(name) $(objects)
run : all
	./$(name)
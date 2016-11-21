CC=g++
CFLAGS=-c -Wall

all: dfs

dfs: main.o CommandLine.o Draw.o
	$(CC) main.o CommandLine.o Draw.o -o dfs

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

CommandLine.o: CommandLine.cpp
	$(CC) $(CFLAGS) CommandLine.cpp

Draw.o: Draw.cpp
	$(CC) $(CFLAGS) Draw.cpp

clean:
	rm *.o *.~ *~ dfs

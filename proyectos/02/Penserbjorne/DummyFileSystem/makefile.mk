CC=g++
CFLAGS=-c -Wall -std=c++11

all: dfs

dfs: main.o CommandLine.o DummyFileSystem.o Draw.o Colors.o
	$(CC) main.o CommandLine.o DummyFileSystem.o Draw.o Colors.o -o dfs

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

CommandLine.o: CommandLine.cpp
	$(CC) $(CFLAGS) CommandLine.cpp

DummyFileSystem.o: DummyFileSystem.cpp
		$(CC) $(CFLAGS) DummyFileSystem.cpp

Draw.o: Draw.cpp
	$(CC) $(CFLAGS) Draw.cpp

Colors.o: Colors.cpp
		$(CC) $(CFLAGS) Colors.cpp

clean:
	rm *.o *.~ *~ dfs

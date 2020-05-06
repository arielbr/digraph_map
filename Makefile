#Makefile

#Define CC and CLAGS
CC=g++
CGLAS=-std=c99 -pedantic -Wall -Wextra

#Link all files
digraphAnalyzer:digraphAnalyzer.o digraph.o
	$(CC) -o digraphAnalyzer digraphAnalyzer.o digraph.o

#Compile digraphAnalyzer.cpp to create digraphAnalyzer.o
digraphAnalyzer.o: digraphAnalyzer.cpp digraph.h
	$(CC) $(CFLAGS) -c digraphAnalyzer.cpp

#Compile digraph.cpp to create digraph.o
digraph.o: digraph.cpp digraph.h
	$(CC) $(CFLAGS) -c digraph.cpp

#Remove all object files and executables to start over
clean:
	rm -f *.o digraphAnalyzer

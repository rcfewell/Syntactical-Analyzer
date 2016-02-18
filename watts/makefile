p1.out: Project1.o LexicalAnalyzer.o SetLimits.o
	g++ -o p1.out Project1.o LexicalAnalyzer.o SetLimits.o

Project1.o: Project1.cpp LexicalAnalyzer.h 
	g++ -c Project1.cpp -g

lexicalAnalyzer.o: LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -c LexicalAnalyzer.cpp -g

SetLimits.o: SetLimits.cpp SetLimits.h
	g++ -c SetLimits.cpp

clean:	
	rm *.o p1.out

run: ./p1.out ../test1.in ./p1.out ../test2.in
	clear
	./p1.out ../test1.in
	./p1.out ../test2.in


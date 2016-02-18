P2.out: Project2.o lex.o syn.o SetLimits.o
	g++ -o P2.out Project2.o lex.o syn.o SetLimits.o

Project2.o: Project2.cpp lex.h syn.h
	g++ -c Project2.cpp -g

lex.o: lex.cpp lex.h
	g++ -c lex.cpp -g

syn.o: syn.h syn.cpp lex.h
	g++ -c syn.cpp -g

SetLimits.o: SetLimits.cpp SetLimits.h
	g++ -c SetLimits.cpp

clean:	
	rm *.o P2.out

run: ./P2.out test.in ./P2.out test1.in
	clear
	./P2.out test.in
	./P2.out test1.in

submit: Project2.cpp syn.h syn.cpp lex.h lex.cpp SetLimits.h SetLimits.cpp
	rm -rf fewellP2
	mkdir fewellP2
	cp Project2.cpp fewellP2
	cp syn.h fewellP2
	cp syn.cpp fewellP2
	cp lex.h fewellP2
	cp lex.cpp fewellP2
	cp SetLimits.h fewellP2
	cp SetLimits.cpp fewellP2
	cp makefile fewellP2
	tar -czvf fewellP2.tgz fewellP2
	cp fewellP2.tgz ~tiawatts/cs460drop


library: main.o LinkedList.o Tokenizer.o
	g++ main.o LinkedList.o -o library

main.o: main.cpp
	g++ -c main.cpp

LinkedList.o: LinkedList.cpp LinkedList.h
	g++ -c LinkedList.cpp

Tokenizer.o: Tokenizer.cpp Tokenizer.h
	g++ -c Tokenizer.cpp

clean:
	rm *.o library
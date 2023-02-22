output: main.o flighthashtable.o flightticket.o mylist.o
	g++ main.o flighthashtable.o flightticket.o mylist.o -o output
	
main.o:	main.cpp flighthashtable.cpp flightticket.cpp mylist.cpp
	g++ -c main.cpp
	
flighthashtable.o: flightticket.h flighthashtable.h mylist.h flightticket.cpp flighthashtable.cpp mylist.cpp
	g++ -c flighthashtable.cpp
	
flightticket.o: flightticket.h flightticket.cpp
	g++ -c flightticket.cpp
	
mylist.o: mylist.h flighthashtable.h mylist.cpp flighthashtable.cpp flightticket.h flightticket.cpp
	g++ -c mylist.cpp
	
clean:
	rm *.o output



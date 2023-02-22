output: main.o myvector.o contactbst.o contact.o
	g++ main.o myvector.o contactbst.o contact.o -o output
	
main.o:	main.cpp myvector.cpp contactbst.cpp contact.cpp
	g++ -c main.cpp
	
contactbst.o: contactbst.h contact.h myvector.h contactbst.cpp myvector.cpp contact.cpp
	g++ -c contactbst.cpp
	
contact.o: contact.h contact.cpp
	g++ -c contact.cpp
	
myvector.o: myvector.h contact.h myvector.cpp
	g++ -c myvector.cpp
	
clean:
	rm *.o output


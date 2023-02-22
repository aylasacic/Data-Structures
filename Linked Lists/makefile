output: main.o DoublyLinkedList.o Admin.o Member.o FitnessClass.o
	g++ DoublyLinkedList.o main.o Admin.o Member.o FitnessClass.o -o output
	
main.o:	main.cpp DoublyLinkedList.h User.h Admin.h Member.h FitnessClass.h
	g++ -c main.cpp
	
DoublyLinkedList.o: Admin.h User.h Member.h DoublyLinkedList.h DoublyLinkedList.cpp FitnessClass.h
	g++ -c DoublyLinkedList.cpp
	
Admin.o: User.h Admin.h Admin.cpp
	g++ -c Admin.cpp
	
Member.o: User.h Member.h Member.cpp
	g++ -c Member.cpp
	
FitnessClass.o: SinglyLinkedList.h FitnessClass.h FitnessClass.cpp
	g++ -c FitnessClass.cpp
	
clean: 
	rm *.o output

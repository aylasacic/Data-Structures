output: main.o Admin.o Member.o FitnessClass.o
	g++ main.o Admin.o Member.o FitnessClass.o -o output
main.o: main.cpp Admin.h Member.h FitnessClass.h
	g++ -c main.cpp
Admin.o: Admin.h Admin.cpp
	g++ -c Admin.cpp
Member.o: Member.h Member.cpp
	g++ -c Member.cpp
FitnessClass.o: FitnessClass.h FitnessClass.cpp
	g++ -c FitnessClass.cpp

clean:
	rm *.o output
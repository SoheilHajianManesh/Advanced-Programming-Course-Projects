CC := g++

main: main.o Library.o magazine.o reference.o book.o document.o prof.o student.o person.o consts.o
	$(CC) main.o Library.o magazine.o reference.o book.o document.o prof.o student.o person.o consts.o -o main

main.o: main.cpp Library.hpp Library.cpp
	$(CC) -c main.cpp -o main.o

consts.o: consts.cpp consts.hpp
	$(CC) -c consts.cpp -o consts.o

person.o:person.hpp person.cpp document.hpp
	$(CC) -c person.cpp -o person.o

document.o: document.hpp document.cpp
	$(CC) -c document.cpp -o document.o

student.o: student.hpp student.cpp person.hpp consts.hpp
	$(CC) -c student.cpp -o student.o

prof.o: prof.hpp prof.cpp person.hpp consts.hpp
	$(CC) -c prof.cpp -o prof.o

book.o: book.hpp book.cpp document.hpp consts.hpp consts.hpp
	$(CC) -c book.cpp	-o	book.o

magazine.o: magazine.hpp magazine.cpp document.hpp consts.hpp
	$(CC) -c magazine.cpp -o magazine.o

reference.o: reference.hpp reference.cpp document.hpp consts.hpp
	$(CC) -c reference.cpp -o reference.o

Library.o: Library.hpp Library.cpp  document.hpp person.hpp student.hpp prof.hpp magazine.hpp book.hpp reference.hpp 
	$(CC) -c Library.cpp -o Library.o

.PHONY: clean

clean:
	rm *.o
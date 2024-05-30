CC := g++

utaxi.out: main.o person.o passenger.o trip.o location.o interface.o inputhandler.o driver.o const.o exceptions.o
	$(CC) main.o trip.o person.o passenger.o location.o interface.o inputhandler.o driver.o const.o exceptions.o -o utaxi.out

main.o: main.cpp inputhandler.hpp
	$(CC) -c -g main.cpp -o main.o

exceptions.o:exceptions.cpp exceptions.hpp
	$(CC) -c -g exceptions.cpp -o exceptions.o

consts.o: const.cpp const.hpp
	$(CC) -c -g const.cpp -o const.o

person.o:person.hpp person.cpp trip.hpp exceptions.hpp
	$(CC) -c -g person.cpp -o person.o

passenger.o: passenger.hpp passenger.cpp person.hpp const.hpp trip.hpp exceptions.hpp
	$(CC) -c -g passenger.cpp -o passenger.o

driver.o: driver.hpp driver.cpp person.hpp const.hpp trip.hpp exceptions.hpp
	$(CC) -c -g driver.cpp -o driver.o

trip.o: trip.hpp trip.cpp location.hpp const.hpp person.hpp passenger.hpp driver.hpp exceptions.hpp
	$(CC) -c -g trip.cpp -o trip.o

location.o: location.hpp location.cpp exceptions.hpp
	$(CC) -c -g location.cpp -o location.o

interface.o: interface.hpp interface.cpp const.hpp driver.hpp passenger.hpp person.hpp trip.hpp location.hpp exceptions.hpp
	$(CC) -c -g interface.cpp -o interface.o

inputhandler.o: inputhandler.hpp inputhandler.cpp const.hpp location.hpp interface.hpp exceptions.hpp
	$(CC) -c -g inputhandler.cpp -o inputhandler.o

.PHONY: clean

clean:
	rm *.o
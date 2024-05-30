CC = g++
FLAGS = -std=c++11 -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
COMPILE_FLAGS = $(FLAGS) -c -g


starwars.out: main.o inputhandler.o game.o ship.o bullet.o enemy.o result.o consts.o rsdl.o
	$(CC) main.o inputhandler.o game.o ship.o bullet.o enemy.o result.o consts.o rsdl.cpp $(FLAGS) -o star_wars.out

main.o: main.cpp inputhandler.hpp
	$(CC) $(COMPILE_FLAGS) main.cpp -o main.o

consts.o:consts.hpp consts.cpp 
	$(CC) $(COMPILE_FLAGS) consts.cpp -o consts.o

result.o: result.hpp result.cpp consts.hpp
	$(CC) $(COMPILE_FLAGS) result.cpp -o result.o

bullet.o: bullet.hpp bullet.cpp consts.hpp
	$(CC) $(COMPILE_FLAGS) bullet.cpp -o bullet.o

ship.o: ship.hpp ship.cpp bullet.hpp consts.hpp
	$(CC) $(COMPILE_FLAGS) ship.cpp -o ship.o

enemy.o: enemy.hpp enemy.cpp ship.hpp bullet.hpp consts.hpp
	$(CC)	$(COMPILE_FLAGS)	enemy.cpp	-o	enemy.o

game.o: game.hpp game.cpp enemy.hpp ship.hpp result.hpp consts.hpp
		$(CC) $(COMPILE_FLAGS) game.cpp -o game.o

inputhandler.o: inputhandler.hpp inputhandler.cpp game.hpp enemy.hpp ship.hpp result.hpp consts.hpp
		$(CC) $(COMPILE_FLAGS) inputhandler.cpp -o inputhandler.o

.PHONY: clean

clean:
	rm *.o
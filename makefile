#Makefile

snake_game: main.o error-handling.o random.o snake.o
	g++ obj/main.o obj/error-handling.o obj/random.o obj/snake.o -o snake_game -lpthread

main.o: src/main.cpp
	g++ src/main.cpp -o obj/main.o -c -lpthread

error-handling.o: src/error-handling.cpp
	g++ src/error-handling.cpp -o obj/error-handling.o -c

random.o: src/random.cpp
	g++ src/random.cpp -o obj/random.o -c

snake.o: src/snake.cpp
	g++ src/snake.cpp -o obj/snake.o -c

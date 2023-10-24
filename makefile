COMPILE=g++ -c *.cpp
LINK=g++ *.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
EXECUTE=./sfml-app
define REMOVE
rm main.o
rm board.o
rm piece.o
rm sfml-app
rm validMoves.o
rm input.o
rm ai.o
rm open.o
endef

all:
	$(COMPILE)
	$(LINK)
	$(EXECUTE)
	$(REMOVE)
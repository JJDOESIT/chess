COMPILE=g++ -c *.cpp
LINK=g++ *.o -o chess.exe -lsfml-graphics -lsfml-window -lsfml-system
EXECUTE=./chess.exe
define REMOVE
rm main.o
rm board.o
rm piece.o
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

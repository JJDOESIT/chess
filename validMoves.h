#include "piece.h"
#include "board.h"

#include <iostream>
#include <vector>
#include <string>

#ifndef VALIDMOVES
#define VALIDMOVES

class ValidMoves
{
public:
    bool checkBoundary(int x, int y);
    void printValidMoves(Piece *board[8][8], int x, int y);
    void getPawn(Piece *board[8][8], int x, int y);
    void getRook(Piece *board[8][8], int x, int y);
    void getKing(Piece *board[8][8], int x, int y);
};

#endif

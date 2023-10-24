#include "validMoves.h"
#include <chrono>
#include <thread>

#ifndef OPEN
#define OPEN

class Open
{
private:
    ValidMoves checkValidMoves;
    const int skewValue = 90;

public:
    std::vector<int> randomOpening(Board *board, Piece *boardPtr[8][8], int randomNumber);
    void addMove(int pieceType, int row, int col, int value, bool continueOpening, std::vector<int> &matrixData);

    std::vector<int> royLopez(Board *board, Piece *boardPtr[8][8]);
    std::vector<int> italian(Board *board, Piece *boardPtr[8][8]);
    std::vector<int> scotchGame(Board *board, Piece *boardPtr[8][8]);
    std::vector<int> londonSystem(Board *board, Piece *boardPtr[8][8]);
};

#endif
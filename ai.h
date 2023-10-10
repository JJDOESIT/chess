#include "board.h"
#include "validMoves.h"
#include <vector>
#include "piece.h"

#ifndef AIALGORITHM
#define AIALGORITHM

class AI
{
public:
    std::vector<int> calculateBestMove(Board *board, Piece *boardCopy[8][8], ValidMoves *checkValidMoves, int depth);
    void copyArray(Piece *copyFrom[8][8], Piece *copyTo[8][8]);
    void deleteArray(Piece *array[8][8]);
    int rankBoard(Piece *boardPtr[8][8], int color, bool negate = false);
};

#endif
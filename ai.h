#include "validMoves.h"

#ifndef AIALGORITHM
#define AIALGORITHM

class AI
{

public:
    std::vector<int> calculateBestMove(Board *board,
                                       ValidMoves *checkValidMoves,
                                       int depth, int maximizingColor,
                                       int alpha,
                                       int beta);

    void rankBoard(Piece *boardPtr[8][8], int maximizingColor, int &whiteScore, int &blackScore);
};

#endif
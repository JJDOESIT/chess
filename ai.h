#include "board.h"
#include "validMoves.h"
#include <vector>
#include "piece.h"

#ifndef AIALGORITHM
#define AIALGORITHM

class AI
{
public:
    std::vector<int> calculateBestMove(Board *board,
                                       Piece *boardCopy[8][8],
                                       ValidMoves *checkValidMoves,
                                       int depth, int maximizingColor,
                                       int alpha,
                                       int beta, int &count);

    void rankBoard(Piece *boardPtr[8][8], int maximizingColor, int &whiteScore, int &blackScore);

    void whitePawnMatrix(int row, int col, int &score);
    void blackPawnMatrix(int row, int col, int &score);

    void knightMatrix(int row, int col, int &score);

    void whiteBishopMatrix(int row, int col, int &score);
    void blackBishopMatrix(int row, int col, int &score);

    void whiteRookMatrix(int row, int col, int &score);
    void blackRookMatrix(int row, int col, int &score);

    void whiteQueenMatrix(int row, int col, int &score);
    void blackQueenMatrix(int row, int col, int &score);

    void kingMatrix(int row, int col, int &score);
};

#endif
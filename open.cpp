#include "open.h"

bool Open::randomOpening(Board *board, Piece *boardPtr[8][8], int randomNumber)
{
    switch (randomNumber)
    {
    case 0:
        return royLopez(board, boardPtr);
        break;
    default:
        return false;
    }
}

bool Open::royLopez(Board *board, Piece *boardPtr[8][8])
{
    static int currentMove = 0;

    if (currentMove > 2)
    {
        return false;
    }

    std::vector<std::vector<std::vector<int>>> openingMoves = {{{1, 4}, {3, 4}}, {{0, 6}, {2, 5}}, {{0, 5}, {4, 1}}};

    Piece *boardCopy[8][8];

    board->copyArray(boardPtr, boardCopy);

    if (isMoveValid(board, boardCopy, currentMove, openingMoves))
    {
        board->movePiece(boardPtr,
                         openingMoves[currentMove][0][0],
                         openingMoves[currentMove][0][1],
                         openingMoves[currentMove][1][0],
                         openingMoves[currentMove][1][1], false);
        currentMove++;
        return true;
    }
    return false;
}

bool Open::isMoveValid(Board *board, Piece *boardPtr[8][8], int currentMove, std::vector<std::vector<std::vector<int>>> openingMoves)
{
    std::vector<std::vector<int>> dummyMoves;
    bool pieceIsThreatened;

    board->movePiece(boardPtr,
                     openingMoves[currentMove][0][0],
                     openingMoves[currentMove][0][1],
                     openingMoves[currentMove][1][0],
                     openingMoves[currentMove][1][1], false);

    for (int i = 0; i <= currentMove; i++)
    {
        checkValidMoves.isKingInCheck(boardPtr,
                                      openingMoves[i][1][0],
                                      openingMoves[i][1][1], pieceColor::WHITE, dummyMoves, pieceIsThreatened);
        if (pieceIsThreatened)
        {
            return false;
        }
    }
    return true;
}
#include "open.h"

bool Open::randomOpening(Board *board, Piece *boardPtr[8][8], int randomNumber)
{
    switch (randomNumber)
    {
    case 0:
        return royLopez(board, boardPtr);
    }
}

bool Open::royLopez(Board *board, Piece *boardPtr[8][8])
{
    static int currentMove = 0;

    if (currentMove > 2)
    {
        return false;
    }

    Piece *boardCopy[8][8];
    std::vector<std::vector<int>> dummyMoves;
    static std::vector<std::vector<int>> possibleThreatenedPieces;
    bool pieceIsThreatened;

    board->copyArray(boardPtr, boardCopy);

    switch (currentMove)
    {
    case 0:
        board->movePiece(boardCopy, 1, 4, 3, 4, true);
        possibleThreatenedPieces.push_back(std::vector<int>{3, 4});

        for (auto move : possibleThreatenedPieces)
        {
            checkValidMoves.isKingInCheck(boardPtr, move[0], move[1], pieceColor::WHITE, dummyMoves, pieceIsThreatened);
            if (pieceIsThreatened)
            {
                return false;
            }
        }

        board->movePiece(boardPtr, 1, 4, 3, 4, false);
        break;
    case 1:
        board->movePiece(boardCopy, 0, 6, 2, 5, true);
        possibleThreatenedPieces.push_back(std::vector<int>{2, 5});

        for (auto move : possibleThreatenedPieces)
        {
            checkValidMoves.isKingInCheck(boardPtr, move[0], move[1], pieceColor::WHITE, dummyMoves, pieceIsThreatened);
            if (pieceIsThreatened)
            {
                return false;
            }
        }

        board->movePiece(boardPtr, 0, 6, 2, 5, false);
        break;
    case 2:
        board->movePiece(boardCopy, 0, 5, 4, 1, true);
        possibleThreatenedPieces.push_back(std::vector<int>{4, 1});

        for (auto move : possibleThreatenedPieces)
        {
            checkValidMoves.isKingInCheck(boardPtr, move[0], move[1], pieceColor::WHITE, dummyMoves, pieceIsThreatened);
            if (pieceIsThreatened)
            {
                return false;
            }
        }

        board->movePiece(boardPtr, 0, 5, 4, 1, false);
        break;
    }
    currentMove++;
    return true;
}
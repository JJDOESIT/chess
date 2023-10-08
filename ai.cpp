#include "ai.h"

int AI::calculateBestMove(Board board, ValidMoves *checkValidMoves, int depth)
{
    Board boardCopy = board;
    boardCopy.swapBuffer[0] = 0;
    boardCopy.swapBuffer[1] = 1;
    boardCopy.movePiece(5, 5);
    boardCopy.switchTurn();
}

// Copy data from one board to another
void AI::copyArray(Piece *copyFrom[8][8], Piece *copyTo[8][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            copyTo[row][col] = copyFrom[row][col];
        }
    }
}

// Rank a board state
void AI::rankBoard(Piece *board[8][8], int &rank, int color, bool negate)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (color == *board[row][col]->getPieceColor())
            {
                int type = *board[row][col]->getPieceType();
                if (type == pieceType::PAWN)
                {
                    rank += 10;
                }
                else if (type == pieceType::KNIGHT)
                {
                    rank += 30;
                }
                else if (type == pieceType::BISHOP)
                {
                    rank += 50;
                }
                else if (type == pieceType::ROOK)
                {
                    rank += 70;
                }
                else if (type == pieceType::QUEEN)
                {
                    rank += 150;
                }
            }
        }
    }

    if (negate)
    {
        rank = rank * -1;
    }
}

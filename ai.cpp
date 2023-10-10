#include "ai.h"

std::vector<int> AI::calculateBestMove(Board *board,
                                       Piece *boardCopy[8][8],
                                       ValidMoves *checkValidMoves,
                                       int depth)
{

    if (depth == 0)
    {
        int rank = rankBoard(boardCopy, pieceColor::BLACK);
        return std::vector<int>{-1, -1, -1, -1, rank};
    }

    std::vector<std::vector<std::vector<int>>> allPossibleMoves;
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (*boardCopy[row][col]->getPieceColor() == pieceColor::WHITE)
            {
                checkValidMoves->getValidMoves(board, boardCopy, row, col, NULL, &allPossibleMoves);
            }
        }
    }

    int rank, minRank = 999;

    int bestMoveEndPositionX = -1;
    int bestMoveEndPositionY = -1;
    int bestMoveStartXPosition = -1;
    int bestMoveStartYPosition = -1;

    for (auto move : allPossibleMoves)
    {
        int startX = move[0][0];
        int startY = move[0][1];
        int endX = move[1][0];
        int endY = move[1][1];

        Piece *freshBoard[8][8];
        copyArray(boardCopy, freshBoard);

        board->movePiece(freshBoard, startX, startY, endX, endY, true);

        std::vector<int> moveData = calculateBestMove(board, freshBoard, checkValidMoves, depth - 1);
        int rank = moveData[4];

        if (rank <= minRank)
        {
            bestMoveEndPositionX = endX;
            bestMoveEndPositionY = endY;
            bestMoveStartXPosition = startX;
            bestMoveStartYPosition = startY;
            minRank = rank;
        }

        deleteArray(freshBoard);
    }
    return std::vector<int>{bestMoveStartXPosition,
                            bestMoveStartYPosition,
                            bestMoveEndPositionX,
                            bestMoveEndPositionY,
                            minRank};
}

// Copy data from one board to another
void AI::copyArray(Piece *copyFrom[8][8], Piece *copyTo[8][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Piece *newPiece = new Piece(*copyFrom[row][col]);
            copyTo[row][col] = newPiece;
        }
    }
}

// Deconstruct board state
void AI::deleteArray(Piece *array[8][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            delete array[row][col];
        }
    }
}

// Rank a board state
int AI::rankBoard(Piece *boardPtr[8][8], int color, bool negate)
{
    int rank = 0;
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (color == *boardPtr[row][col]->getPieceColor())
            {
                int type = *boardPtr[row][col]->getPieceType();
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
    return rank;
}

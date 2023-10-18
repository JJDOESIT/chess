#include "ai.h"

std::vector<int> AI::calculateBestMove(Board *board,
                                       Piece *boardCopy[8][8],
                                       ValidMoves *checkValidMoves,
                                       int depth,
                                       int maximizingColor, int alpha, int beta)
{

    // If the break case depth = 0 is reached
    if (depth == 0)
    {
        int whiteScore = 0, blackScore = 0;
        int rank;
        rankBoard(boardCopy, maximizingColor, whiteScore, blackScore);

        // If the maximizing color is white, calculate a hopefully positive score
        if (maximizingColor == pieceColor::WHITE)
        {
            rank = whiteScore - blackScore;
        }
        // Else calculate a hopefully negative score
        else
        {
            rank = blackScore - whiteScore;
        }
        return std::vector<int>{-1, -1, -1, -1, rank};
    }

    std::vector<std::vector<std::vector<int>>> allPossibleMoves;
    std::vector<int> moveData;
    int minRank = 9999, maxRank = -9999;
    int rank;

    // Loop through the board to find the kings position
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            // If the piece is a king and its color matches the current current player
            if (*board->board[row][col]->getPieceType() == pieceType::KING && *board->board[row][col]->getPieceColor() == board->turn)
            {
                // Check if the king is in check
                checkValidMoves->isKingInCheck(board->board, row, col, board->turn, checkMoves, check);
                // Get possible moves for the piece
                getPossibleMoves(window, board, checkValidMoves, moves, checkMoves, check);
            }
        }
    }

    // Loop through the board
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            // If the piece color equals the maximizing color
            if (*boardCopy[row][col]->getPieceColor() == maximizingColor)
            {
                // Check if the
                bool check;
                std::vector<std::vector<int>> checkMoves;
                checkValidMoves->isKingInCheck(boardCopy, row, col, maximizingColor, checkMoves, check);

                // Add the move to the valid moves list
                checkValidMoves->getValidMoves(board, boardCopy, row, col, checkMoves, check, NULL, &allPossibleMoves);
            }
        }
    }

    // Initilize variables to hold the most viable move
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

        int startType = *boardCopy[startX][startY]->getPieceType();
        int endType = *boardCopy[endX][endY]->getPieceType();

        int startColor = *boardCopy[startX][startY]->getPieceColor();
        int endColor = *boardCopy[endX][endY]->getPieceColor();

        board->movePiece(boardCopy, startX, startY, endX, endY, true);

        if (maximizingColor == pieceColor::WHITE)
        {
            moveData = calculateBestMove(board, boardCopy, checkValidMoves, depth - 1, pieceColor::BLACK, alpha, beta);
        }
        else
        {
            moveData = calculateBestMove(board, boardCopy, checkValidMoves, depth - 1, pieceColor::WHITE, alpha, beta);
        }

        board->undoMove(boardCopy, startX, startY, endX, endY, startType, endType, startColor, endColor);

        if (maximizingColor == pieceColor::WHITE)
        {

            rank = moveData[4];

            if (rank >= maxRank)
            {
                bestMoveEndPositionX = endX;
                bestMoveEndPositionY = endY;
                bestMoveStartXPosition = startX;
                bestMoveStartYPosition = startY;
                maxRank = rank;
            }
            if (maxRank > alpha)
            {
                alpha = rank;
            }
        }

        else
        {
            rank = moveData[4];

            if (rank <= minRank)
            {
                bestMoveEndPositionX = endX;
                bestMoveEndPositionY = endY;
                bestMoveStartXPosition = startX;
                bestMoveStartYPosition = startY;
                minRank = rank;
            }
            if (minRank < beta)
            {
                beta = rank;
            }
        }

        // If alpha is greater than beta, break the recursive for loop
        if (alpha > beta)
        {
            break;
        }
    }

    // If the maximizing color is white, return maximum rank
    if (maximizingColor == pieceColor::WHITE)
    {
        return std::vector<int>{bestMoveStartXPosition,
                                bestMoveStartYPosition,
                                bestMoveEndPositionX,
                                bestMoveEndPositionY,
                                maxRank};
    }
    // Else return minimum rank
    else
    {
        return std::vector<int>{bestMoveStartXPosition,
                                bestMoveStartYPosition,
                                bestMoveEndPositionX,
                                bestMoveEndPositionY,
                                minRank};
    }
}

// Rank a board state
void AI::rankBoard(Piece *boardPtr[8][8], int maximizingColor, int &whiteScore, int &blackScore)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            int type = *boardPtr[row][col]->getPieceType();
            int color = *boardPtr[row][col]->getPieceColor();
            switch (type)
            {
            case pieceType::PAWN:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += 100;
                    whitePawnMatrix(row, col, whiteScore);
                    break;
                case pieceColor::BLACK:
                    blackScore += 100;
                    blackPawnMatrix(row, col, blackScore);
                    break;
                }
                break;
            case pieceType::KNIGHT:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += 320;
                    knightMatrix(row, col, whiteScore);
                    break;
                case pieceColor::BLACK:
                    blackScore += 320;
                    knightMatrix(row, col, blackScore);
                    break;
                }
                break;
            case pieceType::BISHOP:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += 330;
                    whiteBishopMatrix(row, col, whiteScore);
                    break;
                case pieceColor::BLACK:
                    blackScore += 330;
                    blackBishopMatrix(row, col, blackScore);
                    break;
                }
                break;
            case pieceType::ROOK:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += 500;
                    whiteRookMatrix(row, col, whiteScore);
                    break;
                case pieceColor::BLACK:
                    blackScore += 500;
                    blackRookMatrix(row, col, blackScore);
                    break;
                }
                break;
            case pieceType::QUEEN:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += 900;
                    whiteQueenMatrix(row, col, whiteScore);
                    break;
                case pieceColor::BLACK:
                    blackScore += 900;
                    blackQueenMatrix(row, col, blackScore);
                    break;
                }
                break;
            }
        }
    }
}

// Influence white pawns moves
void AI::whitePawnMatrix(int row, int col, int &score)
{
    int whitePawnMatrix[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {5, 10, 10, -20, -20, 10, 10, 5},
        {5, 0, -10, 0, 0, -10, 0, 5},
        {0, 0, 0, 20, 20, 0, 0, 0},
        {5, 5, 10, 25, 25, 10, 5, 5},
        {10, 10, 20, 30, 30, 20, 10, 10},
        {50, 50, 50, 50, 50, 50, 50, 50},
        {0, 0, 0, 0, 0, 0, 0, 0}};

    score += whitePawnMatrix[row][col];
}

// Influence black pawns moves
void AI::blackPawnMatrix(int row, int col, int &score)
{
    int blackPawnMatrix[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {50, 50, 50, 50, 50, 50, 50, 50},
        {10, 10, 20, 30, 30, 20, 10, 10},
        {5, 5, 10, 25, 25, 10, 5, 5},
        {0, 0, 0, 20, 20, 0, 0, 0},
        {5, 0, -10, 0, 0, -10, 0, 5},
        {5, 10, 10, -20, -20, 10, 10, 5},
        {0, 0, 0, 0, 0, 0, 0, 0}};

    score += blackPawnMatrix[row][col];
}

// Influence knights moves
void AI::knightMatrix(int row, int col, int &score)
{
    int knightMatrix[8][8] = {
        {50, -40, -30, -30, -30, -30, -40, -50},
        {-40, -20, 0, 0, 0, 0, -20, -40},
        {-30, 0, 10, 15, 15, 10, 0, -30},
        {-30, 5, 15, 20, 20, 15, 5, -30},
        {-30, 0, 15, 20, 20, 15, 0, -30},
        {-30, 5, 10, 15, 15, 10, 5, -30},
        {-40, -20, 0, 5, 5, 0, -20, -40},
        {-50, -40, -30, -30, -30, -30, -40, -50}};

    score += knightMatrix[row][col];
}

// Influence white bishops moves
void AI::whiteBishopMatrix(int row, int col, int &score)
{
    int whiteBishopMatrix[8][8] = {
        {-20, -10, -10, -10, -10, -10, -10, -20},
        {-10, 5, 0, 0, 0, 0, 5, -10},
        {-10, 10, 10, 10, 10, 10, 10, -10},
        {-10, 0, 10, 10, 10, 10, 0, -10},
        {-10, 5, 5, 10, 10, 5, 5, -10},
        {-10, 0, 5, 10, 10, 5, 0, -10},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-20, -10, -10, -10, -10, -10, -10, -20},
    };

    score += whiteBishopMatrix[row][col];
}

// Influence black bishops moves
void AI::blackBishopMatrix(int row, int col, int &score)
{
    int blackBishopMatrix[8][8] = {
        {-20, -10, -10, -10, -10, -10, -10, -20},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-10, 0, 5, 10, 10, 5, 0, -10},
        {-10, 5, 5, 10, 10, 5, 5, -10},
        {-10, 0, 10, 10, 10, 10, 0, -10},
        {-10, 10, 10, 10, 10, 10, 10, -10},
        {-10, 5, 0, 0, 0, 0, 5, -10},
        {-20, -10, -10, -10, -10, -10, -10, -20},
    };

    score += blackBishopMatrix[row][col];
}

// Influence white rooks moves
void AI::whiteRookMatrix(int row, int col, int &score)
{
    int whiteRookMatrix[8][8] = {
        {0, 10, 0, 5, 5, 0, 10, 0},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {5, 10, 10, 10, 10, 10, 10, 5},
        {0, 0, 0, 0, 0, 0, 0, 0}};

    score += whiteRookMatrix[row][col];
}

// Influence black rooks moves
void AI::blackRookMatrix(int row, int col, int &score)
{
    int blackRookMatrix[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {5, 10, 10, 10, 10, 10, 10, 5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {0, 10, 0, 5, 5, 0, 10, 0}};

    score += blackRookMatrix[row][col];
}

// Influence white queens moves
void AI::whiteQueenMatrix(int row, int col, int &score)
{
    int whiteQueenMatrix[8][8] = {
        {-20, -10, -10, -5, -5, -10, -10, -20},
        {-10, 0, 5, 0, 0, 0, 0, -10},
        {-10, 5, 5, 5, 5, 5, 0, -10},
        {0, 0, 5, 5, 5, 5, 0, -5},
        {-5, 0, 5, 5, 5, 5, 0, -5},
        {-10, 0, 5, 5, 5, 5, 0, -10},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-20, -10, -10, -5, -5, -10, -10, -20}};

    score += whiteQueenMatrix[row][col];
}

// Influence black queens moves
void AI::blackQueenMatrix(int row, int col, int &score)
{
    int blackQueenMatrix[8][8] = {
        {-20, -10, -10, -5, -5, -10, -10, -20},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-10, 0, 5, 5, 5, 5, 0, -10},
        {-5, 0, 5, 5, 5, 5, 0, -5},
        {0, 0, 5, 5, 5, 5, 0, -5},
        {-10, 5, 5, 5, 5, 5, 0, -10},
        {-10, 0, 5, 0, 0, 0, 0, -10},
        {-20, -10, -10, -5, -5, -10, -10, -20}};

    score += blackQueenMatrix[row][col];
}

// Influence kings moves
void AI::kingMatrix(int row, int col, int &score)
{
    int kingMatrix[8][8] = {
        {3, 4, 2, 0, 0, 2, 4, 3},
        {3, 3, 0, 0, 0, 0, 3, 3},
        {-2, -3, -3, -3, -3, -3, -3, -2},
        {-3, -4, -4, -4, -4, -4, -4, -3},
        {-4, -5, -5, -6, -6, -5, -5, -4},
        {-4, -5, -5, -6, -6, -5, -5, -4},
        {-4, -5, -5, -6, -6, -5, -5, -4},
        {-4, -5, -5, -6, -6, -5, -5, -4}};

    score += kingMatrix[row][col];
}
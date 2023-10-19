#include "ai.h"
#include "pieceMobilityMatrices.h"

std::vector<int> AI::calculateBestMove(Board *board,
                                       Piece *boardCopy[8][8],
                                       ValidMoves *checkValidMoves,
                                       int depth,
                                       int maximizingColor, int alpha, int beta, int &count)
{
    // std::cout << count << std::endl;
    count += 1;
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

    bool check = false;
    std::vector<std::vector<int>> checkMoves;

    // Loop through the board to find the kings position
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            // If the piece is a king and its color matches the current current player
            if (*board->board[row][col]->getPieceType() == pieceType::KING && *board->board[row][col]->getPieceColor() == maximizingColor)
            {
                // Check if the king is in check
                checkValidMoves->isKingInCheck(boardCopy, row, col, maximizingColor, checkMoves, check);
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
            moveData = calculateBestMove(board, boardCopy, checkValidMoves, depth - 1, pieceColor::BLACK, alpha, beta, count);
        }
        else
        {
            moveData = calculateBestMove(board, boardCopy, checkValidMoves, depth - 1, pieceColor::WHITE, alpha, beta, count);
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
                    whiteScore += matrices::whitePawnMatrix[row][col];
                    break;
                case pieceColor::BLACK:
                    blackScore += 100;
                    blackScore += matrices::blackPawnMatrix[row][col];
                    break;
                }
                break;
            case pieceType::KNIGHT:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += 320;
                    whiteScore += matrices::knightMatrix[row][col];
                    break;
                case pieceColor::BLACK:
                    blackScore += 320;
                    blackScore += matrices::knightMatrix[row][col];
                    break;
                }
                break;
            case pieceType::BISHOP:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += 330;
                    whiteScore += matrices::whiteBishopMatrix[row][col];
                    break;
                case pieceColor::BLACK:
                    blackScore += 330;
                    blackScore += matrices::blackBishopMatrix[row][col];
                    break;
                }
                break;
            case pieceType::ROOK:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += 500;
                    whiteScore += matrices::whiteRookMatrix[row][col];
                    break;
                case pieceColor::BLACK:
                    blackScore += 500;
                    blackScore += matrices::blackRookMatrix[row][col];
                    break;
                }
                break;
            case pieceType::QUEEN:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += 900;
                    whiteScore += matrices::whiteQueenMatrix[row][col];
                    break;
                case pieceColor::BLACK:
                    blackScore += 900;
                    blackScore += matrices::blackQueenMatrix[row][col];
                    break;
                }
                break;
            }
        }
    }
}

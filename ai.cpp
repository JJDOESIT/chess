#include "ai.h"
#include "pieceMobilityMatrices.h"
#include "globalValues.h"

std::vector<int> AI::calculateBestMove(Board *board,
                                       ValidMoves *checkValidMoves,
                                       int depth,
                                       int maximizingColor, int alpha, int beta)
{
    // If the break case depth = 0 is reached
    if (depth == 0)
    {
        int whiteScore = 0, blackScore = 0;
        int rank;
        rankBoard(board->board, maximizingColor, whiteScore, blackScore);

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

    // Check if the king is in check
    if (maximizingColor == pieceColor::WHITE)
    {
        checkValidMoves->isKingInCheck(board->board, board->positionOfWhiteKing[0], board->positionOfWhiteKing[1], maximizingColor, checkMoves, check);
    }
    else
    {
        checkValidMoves->isKingInCheck(board->board, board->positionOfBlackKing[0], board->positionOfBlackKing[1], maximizingColor, checkMoves, check);
    }

    // Loop through the board
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            // If the piece color equals the maximizing color
            if (*board->board[row][col]->getPieceColor() == maximizingColor)
            {
                // Add the move to the valid moves list
                checkValidMoves->getValidMoves(board, board->board, row, col, checkMoves, check, NULL, &allPossibleMoves);
            }
        }
    }

    // Initilize variables to hold the most viable move
    int bestMoveEndPositionX = -1;
    int bestMoveEndPositionY = -1;
    int bestMoveStartXPosition = -1;
    int bestMoveStartYPosition = -1;

    // Loop through every single move each piece can make
    for (auto move : allPossibleMoves)
    {
        int startX = move[0][0];
        int startY = move[0][1];
        int endX = move[1][0];
        int endY = move[1][1];

        int startType = *board->board[startX][startY]->getPieceType();
        int endType = *board->board[endX][endY]->getPieceType();

        int startColor = *board->board[startX][startY]->getPieceColor();
        int endColor = *board->board[endX][endY]->getPieceColor();

        // Check if the possible move is a passant capture
        bool passant = checkValidMoves->isThisMoveEnPassant(board->board, startX, startY, endX, endY);

        // Check if the possible is a castle
        bool castle = (startType == pieceType::KING && endType == pieceType::ROOK && startColor == endColor);

        bool promotion = false;

        // Move the piece
        board->movePiece(board->board, startX, startY, endX, endY, true);

        // Recursive call switching to the opposite color
        if (maximizingColor == pieceColor::WHITE)
        {
            moveData = calculateBestMove(board, checkValidMoves, depth - 1, pieceColor::BLACK, alpha, beta);
        }
        else
        {
            moveData = calculateBestMove(board, checkValidMoves, depth - 1, pieceColor::WHITE, alpha, beta);
        }

        if (startType == pieceType::PAWN && startType != *board->board[endX][endY]->getPieceType())
        {
            promotion = true;
        }

        // Undo the move
        board->undoMove(board->board, startX, startY, endX, endY, startType, endType, startColor, endColor, passant, castle, promotion);

        // If the current turn is white
        if (maximizingColor == pieceColor::WHITE)
        {
            rank = moveData[4];

            // Find the highest rank of all the board states
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

        // If the current turn is black
        else
        {
            rank = moveData[4];

            // Find the lowest rank of all the board states
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
                    whiteScore += global::pawnValue;
                    whiteScore += matrices::whitePawnMatrix[row][col];
                    break;
                case pieceColor::BLACK:
                    blackScore += global::pawnValue;
                    blackScore += matrices::blackPawnMatrix[row][col];
                    break;
                }
                break;
            case pieceType::KNIGHT:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += global::knightValue;
                    whiteScore += matrices::knightMatrix[row][col];
                    break;
                case pieceColor::BLACK:
                    blackScore += global::knightValue;
                    blackScore += matrices::knightMatrix[row][col];
                    break;
                }
                break;
            case pieceType::BISHOP:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += global::bishopValue;
                    whiteScore += matrices::whiteBishopMatrix[row][col];
                    break;
                case pieceColor::BLACK:
                    blackScore += global::bishopValue;
                    blackScore += matrices::blackBishopMatrix[row][col];
                    break;
                }
                break;
            case pieceType::ROOK:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += global::rookValue;
                    whiteScore += matrices::whiteRookMatrix[row][col];
                    break;
                case pieceColor::BLACK:
                    blackScore += global::rookValue;
                    blackScore += matrices::blackRookMatrix[row][col];
                    break;
                }
                break;
            case pieceType::QUEEN:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += global::queenValue;
                    whiteScore += matrices::whiteQueenMatrix[row][col];
                    break;
                case pieceColor::BLACK:
                    blackScore += global::queenValue;
                    blackScore += matrices::blackQueenMatrix[row][col];
                    break;
                }
                break;

            case pieceType::KING:
                switch (color)
                {
                case pieceColor::WHITE:
                    whiteScore += matrices::whiteKingMatrix[row][col];
                    break;
                case pieceColor::BLACK:
                    blackScore += matrices::blackKingMatrix[row][col];
                    break;
                }
                break;
            }
        }
    }
}

#include "validMoves.h"

// Check for out of bound error
bool ValidMoves::checkBoundary(int x, int y)
{
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

// Get valid moves
void ValidMoves::getValidMoves(Board *board,
                               Piece *boardPtr[8][8], int x, int y,
                               std::vector<std::vector<int>> *moves,
                               std::vector<std::vector<std::vector<int>>> *allPossibleMoves)
{
    int type = *boardPtr[x][y]->getPieceType();
    boardPtr[x][y]->getValidMoves()->clear();
    if (type == pieceType::ROOK)
    {
        getRook(boardPtr, x, y);
    }
    else if (type == pieceType::PAWN)
    {
        getPawn(board, boardPtr, x, y, allPossibleMoves);
    }
    else if (type == pieceType::KING)
    {
        getKing(boardPtr, x, y);
    }
    else if (type == pieceType::QUEEN)
    {
        getQueen(boardPtr, x, y);
    }
    else if (type == pieceType::BISHOP)
    {
        getBishop(boardPtr, x, y);
    }
    else if (type == pieceType::KNIGHT)
    {
        getKnight(boardPtr, x, y);
    }

    board->swapBuffer[0] = x;
    board->swapBuffer[1] = y;

    // If the move list is not passed in as an argument, dont add piece moves to move list
    if (moves != NULL)
    {
        *moves = *boardPtr[x][y]->getValidMoves();
        if (moves->size() > 0)
        {
            board->mode = playerMode::VIEW;
        }
    }
}

// Print out valid moves
void ValidMoves::printValidMoves(Piece *board[8][8], int x, int y)
{
    std::vector<std::vector<int>> *validMovePtr = board[x][y]->getValidMoves();
    for (auto move : *validMovePtr)
    {
        std::cout << "(";
        for (auto position : move)
        {
            std::cout << position << ",";
        }
        std::cout << ") ";
    }
}

// Get possible moves for pawn
void ValidMoves::getPawn(Board *board, Piece *boardPtr[8][8], int x, int y, std::vector<std::vector<std::vector<int>>> *allPossibleMoves)
{
    int color = *boardPtr[x][y]->getPieceColor();
    std::vector<std::vector<int>> possibleMoves;
    std::vector<std::vector<int>> passantMoves = {{0, -1}, {0, 1}};

    // If the pawn is black ...
    if (color == pieceColor::BLACK)
    {
        possibleMoves = {{-1, 0}, {-1, -1}, {-1, 1}};

        // Check to see if the pawn can move two spaces
        if (!*boardPtr[x][y]->getHasMoved())
        {
            if (*boardPtr[x - 1][y]->getPieceType() == pieceType::NONE)
            {
                possibleMoves.push_back(std::vector<int>{-2, 0});
            }
        }
    }

    // If the pawn is white ...
    else if (color == pieceColor::WHITE)
    {
        possibleMoves = {{1, 0}, {1, -1}, {1, 1}};

        // Check to see if the pawn can move two space
        if (!*boardPtr[x][y]->getHasMoved())
        {
            if (*boardPtr[x + 1][y]->getPieceType() == pieceType::NONE)
            {
                possibleMoves.push_back(std::vector<int>{2, 0});
            }
        }
    }

    // Check to see if the pawn can move forward, or diagonal
    for (auto move : possibleMoves)
    {
        if (checkBoundary(x + move[0], y + move[1]))
        {
            int nextColor = *boardPtr[x + move[0]][y + move[1]]->getPieceColor();
            if (move[1] == 0)
            {
                if (nextColor == pieceColor::NONE)
                {
                    boardPtr[x][y]->addMove(x + move[0], y + move[1]);
                }
            }
            else
            {
                if (nextColor != color && nextColor != pieceColor::NONE)
                {
                    boardPtr[x][y]->addMove(x + move[0], y + move[1]);
                }
            }
        }
    }

    std::vector<int> *lastMovedPiecePtr;

    // Fetch the position of the last moved piece depending on whose turn it is
    if (*board->getCurrentTurn() == playerTurn::WHITE)
    {
        lastMovedPiecePtr = board->getpositionOfLastMovedBlackPiece();
    }
    else
    {
        lastMovedPiecePtr = board->getpositionOfLastMovedWhitePiece();
    }

    // Check if passant is a valid move
    for (auto move : passantMoves)
    {
        int futureX = move[0];
        int futureY = move[1];

        // Check if the coords are within range
        if (checkBoundary(x + futureX, y + futureY))
        {
            // Check if the piece next to the pawn is a pawn
            if (*boardPtr[x + futureX][y + futureY]->getPieceType() == pieceType::PAWN)
            {
                // Check if the pawn next to the pawn was the last most played piece
                if (x + futureX == lastMovedPiecePtr->at(0) && y + futureY == lastMovedPiecePtr->at(1))
                {
                    // Check if the pawn has only moved once
                    if (*boardPtr[x][y + futureY]->getMoveCounter() == 1)
                    {
                        int xDirection;
                        int xValue;

                        // Check if the pawn is black or white
                        if (*boardPtr[x][y]->getPieceColor() == pieceColor::BLACK)
                        {
                            xDirection = -1;
                            xValue = 3;
                        }
                        else
                        {
                            xDirection = 1;
                            xValue = 4;
                        }
                        if (x == xValue)
                        {
                            if (*boardPtr[x + xDirection][y]->getPieceType() == pieceType::NONE)
                            {
                                boardPtr[x][y]->addMove(x + xDirection, y + futureY);
                            }
                        }
                    }
                }
            }
        }
    }

    if (allPossibleMoves != NULL)
    {
        std::vector<std::vector<int>> validMovesPtr = *board->board[x][y]->getValidMoves();
        for (auto move : validMovesPtr)
        {
            allPossibleMoves->push_back(std::vector<std::vector<int>>{{x, y}, {move[0], move[1]}});
        }
    }
}

// Get possible moves for rook
void ValidMoves::getRook(Piece *board[8][8], int x, int y)
{
    std::vector<std::vector<int>> possibleMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    calculateLinearMoves(board, possibleMoves, x, y);
}

// Get possible moves for knight
void ValidMoves::getKnight(Piece *board[8][8], int x, int y)
{
    std::vector<std::vector<int>> possibleMoves = {{2, 1}, {2, -1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {1, -2}, {-1, -2}};
    calculateSingleMoves(board, possibleMoves, x, y);
}

// Get possible moves for bishop
void ValidMoves::getBishop(Piece *board[8][8], int x, int y)
{
    std::vector<std::vector<int>> possibleMoves = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    calculateLinearMoves(board, possibleMoves, x, y);
}

// Get possible moves for king
void ValidMoves::getKing(Piece *board[8][8], int x, int y)
{
    // Possible moves for a king to move
    std::vector<std::vector<int>> possibleMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    calculateSingleMoves(board, possibleMoves, x, y);
}

// Get possible moves for queen
void ValidMoves::getQueen(Piece *board[8][8], int x, int y)
{
    std::vector<std::vector<int>> possibleMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    calculateLinearMoves(board, possibleMoves, x, y);
}

// Calculates the possible moves in a single direction in a directions provided
void ValidMoves::calculateLinearMoves(Piece *board[8][8], std::vector<std::vector<int>> possibleMoves, int originalX, int originalY)
{
    // Struct to hold position and next possible move
    struct pieceStruct
    {
        std::vector<int> position;
        std::vector<int> move;
    };

    // The stack
    std::vector<pieceStruct> stack;

    for (auto move : possibleMoves)
    {
        int x = move[0];
        int y = move[1];

        if (checkBoundary(originalX + x, originalY + y))
        {
            pieceStruct pieceData;

            pieceData.position = std::vector<int>{originalX + x, originalY + y};
            pieceData.move = std::vector<int>{x, y};

            int color = *board[originalX + x][originalY + y]->getPieceColor();
            if (color == pieceColor::NONE)
            {
                stack.push_back(pieceData);
                board[originalX][originalY]->addMove(originalX + x, originalY + y);
            }
            else if (color != *board[originalX][originalY]->getPieceColor())
            {
                board[originalX][originalY]->addMove(originalX + x, originalY + y);
            }
        }
    }
    // While the stack is not empty
    while (stack.size() > 0)
    {
        pieceStruct move = stack.back();
        stack.pop_back();

        int x = move.position[0];
        int y = move.position[1];

        int futureX = move.move[0];
        int futureY = move.move[1];

        if (checkBoundary(x + futureX, y + futureY))
        {
            int color = *board[originalX][originalY]->getPieceColor();
            int futureColor = *board[x + futureX][y + futureY]->getPieceColor();
            if (futureColor == pieceColor::NONE)
            {
                move.position[0] = x + futureX;
                move.position[1] = y + futureY;
                stack.push_back(move);
                board[originalX][originalY]->addMove(x + futureX, y + futureY);
            }
            else if (color != futureColor)
            {
                board[originalX][originalY]->addMove(x + futureX, y + futureY);
            }
        }
    }
}

// Calculate possible moves given a set vector of moves
void ValidMoves::calculateSingleMoves(Piece *board[8][8], std::vector<std::vector<int>> possibleMoves, int x, int y)
{
    for (auto move : possibleMoves)
    {
        if (checkBoundary(x + move[0], y + move[1]))
        {
            if (*board[x + move[0]][y + move[1]]->getPieceColor() != *board[x][y]->getPieceColor())
            {
                board[x][y]->addMove(x + move[0], y + move[1]);
            }
        }
    }
}
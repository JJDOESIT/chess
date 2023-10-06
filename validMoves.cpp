#include "validMoves.h"

// Check for out of bound error
bool ValidMoves::checkBoundary(int x, int y)
{
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
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
void ValidMoves::getPawn(Piece *board[8][8], int x, int y)
{
    std::vector<std::vector<int>> *validMovePtr = board[x][y]->getValidMoves();
    validMovePtr->clear();

    // Get possible moves for white pawns
    if (*board[x][y]->getPieceColor() == pieceColor(WHITE))
    {
        if (checkBoundary(x + 1, y))
        {
            if (*board[x + 1][y]->getPieceType() == pieceType(NONE))
            {
                validMovePtr->push_back(std::vector<int>{x + 1, y});
            }
        }
        if (checkBoundary(x + 1, y + 1))
        {
            if (*board[x + 1][y + 1]->getPieceColor() == pieceColor(BLACK))
            {
                validMovePtr->push_back(std::vector<int>{x + 1, y + 1});
            }
        }
        if (checkBoundary(x + 1, y - 1))
        {
            if (*board[x + 1][y - 1]->getPieceColor() == pieceColor(BLACK))
            {
                validMovePtr->push_back(std::vector<int>{x + 1, y - 1});
            }
        }
    }

    // Get possible moves for black pawns
    if (*board[x][y]->getPieceColor() == pieceColor(BLACK))
    {
        if (checkBoundary(x - 1, y))
        {
            int type = *board[x - 1][y]->getPieceType();
            if (type == pieceType(NONE))
            {
                validMovePtr->push_back(std::vector<int>{x - 1, y});
            }
        }
        if (checkBoundary(x - 1, y + 1))
        {
            if (*board[x - 1][y + 1]->getPieceColor() == pieceColor(WHITE))
            {
                validMovePtr->push_back(std::vector<int>{x - 1, y + 1});
            }
        }
        if (checkBoundary(x - 1, y - 1))
        {
            if (*board[x - 1][y - 1]->getPieceColor() == pieceColor(WHITE))
            {
                validMovePtr->push_back(std::vector<int>{x - 1, y - 1});
            }
        }
    }
}

// Get possible moves for rook
void ValidMoves::getRook(Piece *board[8][8], int x, int y)
{
    // Clear the current valid moves
    std::vector<std::vector<int>> *validMovePtr = board[x][y]->getValidMoves();
    validMovePtr->clear();

    // Save the original x and y value
    int originalX = x;
    int originalY = y;

    // Possible directions for a rook to move
    std::vector<std::vector<int>> possibleMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // Hold a rooks position and direction
    struct rookStruct
    {
        std::vector<int> position;
        std::string direction;
    };

    // The stack
    std::vector<rookStruct> stack;

    // Get first four possible moves first and add them to the stack if neccessary
    for (auto move : possibleMoves)
    {
        int x = move[0];
        int y = move[1];

        if (checkBoundary(originalX + x, originalY + y))
        {
            int color = *board[originalX + x][originalY + y]->getPieceColor();
            rookStruct rookData;
            rookData.position = std::vector<int>{originalX + x, originalY + y};
            if (x == 1 && y == 0)
            {
                rookData.direction = "down";
            }
            if (x == -1 && y == 0)
            {
                rookData.direction = "up";
            }
            if (x == 0 && y == 1)
            {
                rookData.direction = "right";
            }
            if (x == 0 && y == -1)
            {
                rookData.direction = "left";
            }
            if (color == pieceColor(NEITHER))
            {
                stack.push_back(rookData);
                board[originalX][originalY]->addMove(originalX + x, originalY + y);
            }
            else if (color != *board[originalX][originalY]->getPieceColor())
            {
                board[originalX][originalY]->addMove(originalX + x, originalY + y);
            }
        }
    }

    // While the stack is not empty, continue finding moves
    while (stack.size() > 0)
    {
        rookStruct move = stack.back();
        stack.pop_back();

        int x = move.position[0];
        int y = move.position[1];

        if (move.direction == "down")
        {
            x = x + 1;
        }
        else if (move.direction == "up")
        {
            x = x - 1;
        }
        else if (move.direction == "right")
        {
            y = y + 1;
        }
        else if (move.direction == "left")
        {
            y = y - 1;
        }

        if (checkBoundary(x, y))
        {
            int color = *board[x][y]->getPieceColor();
            if (color == pieceColor(NEITHER))
            {
                move.position = std::vector<int>{x, y};
                stack.push_back(move);
                board[originalX][originalY]->addMove(x, y);
            }
            else if (color != *board[originalX][originalY]->getPieceColor())
            {
                board[originalX][originalY]->addMove(x, y);
            }
        }
    }
}
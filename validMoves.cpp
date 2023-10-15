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
    int color = *boardPtr[x][y]->getPieceColor();
    boardPtr[x][y]->getValidMoves()->clear();

    switch (type)
    {
    case (pieceType::ROOK):
        getRook(boardPtr, x, y);
        break;
    case (pieceType::PAWN):
        getPawn(board, boardPtr, x, y);
        break;
    case (pieceType::KING):
        getKing(boardPtr, x, y);
        break;
    case (pieceType::QUEEN):
        getQueen(boardPtr, x, y);
        break;
    case (pieceType::BISHOP):
        getBishop(boardPtr, x, y);
        break;
    case (pieceType::KNIGHT):
        getKnight(boardPtr, x, y);
        break;
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

    // If allPossibleMoves is passed as a parameter, populate it with the exisitng values in valid moves
    if (allPossibleMoves != NULL)
    {
        std::vector<std::vector<int>> validMovesPtr = *boardPtr[x][y]->getValidMoves();
        for (auto move : validMovesPtr)
        {
            allPossibleMoves->push_back(std::vector<std::vector<int>>{{x, y}, {move[0], move[1]}});
        }
    }

    // Alter possible moves based on if king is in check
    if (color == pieceColor::WHITE)
    {
        if (board->whiteKingInCheck)
        {
            moves->clear();
            std::vector<std::vector<int>> validMovesPtr = *boardPtr[x][y]->getValidMoves();

            for (std::vector<int> pieceMove : validMovesPtr)
            {
                int pieceX = pieceMove[0];
                int pieceY = pieceMove[1];
                for (std::vector<int> boardMove : board->whiteCheckMovesList)
                {
                    int boardX = boardMove[0];
                    int boardY = boardMove[1];

                    if (pieceX == boardX && pieceY == boardY)
                    {
                        std::cout << "YES" << std::endl;
                        boardPtr[x][y]->addMove(pieceX, pieceY);
                        moves->push_back(std::vector<int>{pieceX, pieceY});
                    }
                }
            }
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
void ValidMoves::getPawn(Board *board, Piece *boardPtr[8][8], int x, int y)
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
            if (*boardPtr[x - 1][y]->getPieceType() == pieceType::NONE && *boardPtr[x - 1][y]->getPieceType() != pieceType::KING)
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
            if (*boardPtr[x + 1][y]->getPieceType() == pieceType::NONE && *boardPtr[x + 1][y]->getPieceType() != pieceType::KING)
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
            int nextType = *boardPtr[x + move[0]][y + move[1]]->getPieceType();
            if (move[1] == 0)
            {
                // If the possible move is an empty cell
                if (nextColor == pieceColor::NONE)
                {
                    // Move forward
                    boardPtr[x][y]->addMove(x + move[0], y + move[1]);
                }
            }
            else
            {
                // If the possible move is not the same color as the moving piece, and the possible move is not an empty cell or a king
                if (nextColor != color && nextColor != pieceColor::NONE && nextType != pieceType::KING)
                {
                    // Move diagonal
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
    // Loop through each move in the possibleMoves list
    for (std::vector<int> move : possibleMoves)
    {
        int tempX = originalX;
        int tempY = originalY;
        int originalColor = *board[originalX][originalY]->getPieceColor();
        bool continueSearching = true;

        // While continueSearching is true
        while (continueSearching)
        {
            // Check for out-of-bounds error
            if (checkBoundary(tempX + move[0], tempY + move[1]))
            {
                // If the next move is an empty cell
                if (*board[tempX + move[0]][tempY + move[1]]->getPieceColor() == pieceColor::NONE)
                {
                    // Add move to the pieces valid move list and update the position
                    board[originalX][originalY]->addMove(tempX + move[0], tempY + move[1]);
                    tempX += move[0];
                    tempY += move[1];
                }
                // Else if the move color is equal to the original piece color or is equal to a king
                else if (*board[tempX + move[0]][tempY + move[1]]->getPieceColor() == originalColor || *board[tempX + move[0]][tempY + move[1]]->getPieceType() == pieceType::KING)
                {
                    continueSearching = false;
                }
                // Else if the move color is not equal to the original piece color
                else
                {
                    board[originalX][originalY]->addMove(tempX + move[0], tempY + move[1]);
                    continueSearching = false;
                }
            }
            else
            {
                continueSearching = false;
            }
        }
    }
}

// Calculate possible moves given a set vector of moves
void ValidMoves::calculateSingleMoves(Piece *board[8][8], std::vector<std::vector<int>> possibleMoves, int x, int y)
{
    for (std::vector<int> move : possibleMoves)
    {
        if (checkBoundary(x + move[0], y + move[1]))
        {
            // If the possible move color is not the same as the moving color and the possible move is not a king
            if (*board[x + move[0]][y + move[1]]->getPieceColor() != *board[x][y]->getPieceColor() && *board[x + move[0]][y + move[1]]->getPieceType() != pieceType::KING)
            {
                board[x][y]->addMove(x + move[0], y + move[1]);
            }
        }
    }
}

void ValidMoves::isKingInCheck(Board *board, Piece *boardPtr[8][8])
{
    std::vector<std::vector<int>> blackCheckMoves;
    std::vector<std::vector<int>> whiteCheckMoves;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (*boardPtr[row][col]->getPieceType() == pieceType::KING)
            {

                int originalX = row;
                int originalY = col;
                int color = *boardPtr[row][col]->getPieceColor();

                // Check if a king is in check by a pawn
                std::vector<std::vector<int>> possiblePawnMoves;

                if (color == pieceColor::WHITE)
                {
                    possiblePawnMoves = {{1, 1}, {1, -1}};
                }
                else
                {
                    possiblePawnMoves = {{-1, 1}, {-1, -1}};
                }
                for (std::vector<int> move : possiblePawnMoves)
                {
                    if (checkBoundary(originalX + move[0], originalY + move[1]))
                    {
                        if (*boardPtr[originalX + move[0]][originalY + move[1]]->getPieceColor() != color && *boardPtr[originalX + move[0]][originalY + move[1]]->getPieceType() == pieceType::PAWN)
                        {
                            if (color == pieceColor::WHITE)
                            {
                                whiteCheckMoves.push_back(std::vector<int>{originalX + move[0], originalY + move[1]});
                            }
                            else
                            {
                                blackCheckMoves.push_back(std::vector<int>{originalX + move[0], originalY + move[1]});
                            }
                        }
                    }
                }

                // Check if a king is in check by a rook, bishop, or queen
                std::vector<std::vector<int>> possibleQueenMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
                std::vector<std::vector<int>> possibleRookMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

                if (color == pieceColor::WHITE)
                {
                    checkLinearMoves(boardPtr, possibleRookMoves, originalX, originalY, pieceType::ROOK, whiteCheckMoves);
                    checkLinearMoves(boardPtr, possibleQueenMoves, originalX, originalY, pieceType::QUEEN, whiteCheckMoves);
                }
                else
                {
                    checkLinearMoves(boardPtr, possibleRookMoves, originalX, originalY, pieceType::ROOK, blackCheckMoves);
                    checkLinearMoves(boardPtr, possibleQueenMoves, originalX, originalY, pieceType::QUEEN, blackCheckMoves);
                }
            }
        }
    }

    if (blackCheckMoves.size() > 0)
    {
        board->blackCheckMovesList = blackCheckMoves;
        board->blackKingInCheck = true;
    }
    else
    {
        board->blackCheckMovesList.clear();
        board->blackKingInCheck = false;
    }
    if (whiteCheckMoves.size() > 0)
    {
        board->whiteCheckMovesList = whiteCheckMoves;
        board->whiteKingInCheck = true;
    }
    else
    {
        board->whiteCheckMovesList.clear();
        board->whiteKingInCheck = false;
    }
}

void ValidMoves::checkLinearMoves(Piece *board[8][8], std::vector<std::vector<int>> possibleMoves, int x, int y, int type, std::vector<std::vector<int>> &finalXRayPath)
{

    for (std::vector<int> move : possibleMoves)
    {
        int tempX = x;
        int tempY = y;
        bool continueSearching = true;
        std::vector<std::vector<int>> tempXRayPath;
        while (continueSearching)
        {
            if (checkBoundary(tempX + move[0], tempY + move[1]))
            {
                // If the next move is an empty cell
                if (*board[tempX + move[0]][tempY + move[1]]->getPieceColor() == pieceColor::NONE)
                {
                    tempXRayPath.push_back(std::vector<int>{tempX + move[0], tempY + move[1]});
                    tempX += move[0];
                    tempY += move[1];
                }
                // Else if the next move is an opposite color than the king and is equals the correct type
                else if (*board[tempX + move[0]][tempY + move[1]]->getPieceColor() != *board[x][y]->getPieceColor() && *board[tempX + move[0]][tempY + move[1]]->getPieceType() == type)
                {
                    tempXRayPath.push_back(std::vector<int>{tempX + move[0], tempY + move[1]});
                    finalXRayPath = tempXRayPath;
                    continueSearching = false;
                }
                else
                {
                    continueSearching = false;
                }
            }
            else
            {
                continueSearching = false;
            }
        }
    }
}
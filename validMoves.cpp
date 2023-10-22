#include "validMoves.h"

// Check for out of bound error
bool ValidMoves::checkBoundary(int x, int y)
{
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

// Get valid moves
void ValidMoves::getValidMoves(Board *board,
                               Piece *boardPtr[8][8], int x, int y,
                               std::vector<std::vector<int>> &checkMoves,
                               bool &isInCheck,
                               std::vector<std::vector<int>> *moves,
                               std::vector<std::vector<std::vector<int>>> *allPossibleMoves)
{
    int type = *boardPtr[x][y]->getPieceType();
    int color = *boardPtr[x][y]->getPieceColor();
    boardPtr[x][y]->getValidMoves()->clear();

    switch (type)
    {
    case (pieceType::ROOK):
        getRook(board, boardPtr, x, y);
        break;
    case (pieceType::PAWN):
        getPawn(board, boardPtr, x, y);
        break;
    case (pieceType::KING):
        getKing(boardPtr, x, y);
        checkCastle(board, boardPtr, x, y);
        break;
    case (pieceType::QUEEN):
        getQueen(board, boardPtr, x, y);
        break;
    case (pieceType::BISHOP):
        getBishop(board, boardPtr, x, y);
        break;
    case (pieceType::KNIGHT):
        getKnight(board, boardPtr, x, y);
        break;
    }

    board->swapBuffer[0] = x;
    board->swapBuffer[1] = y;

    // Alter possible moves based on if king is in check
    if (isInCheck)
    {
        // Create a copy of the pieces valid moves list
        std::vector<std::vector<int>> validMoves = *boardPtr[x][y]->getValidMoves();

        // If the selected piece is a king
        if (*boardPtr[x][y]->getPieceType() == pieceType::KING)
        {
            getKing(boardPtr, x, y);
        }
        else
        {
            compareTwoMovesLists(boardPtr, x, y, validMoves, checkMoves);
        }
    }

    detectPinnedPieces(boardPtr, color, x, y);

    // If the move list is not passed in as an argument, dont add piece moves to move list
    if (moves != NULL)
    {
        // Set the drawable moves to the pieces valid moves
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
}

// Given two lists of moves, only add the move if it is present in both lists
void ValidMoves::compareTwoMovesLists(Piece *boardPtr[8][8], int x, int y, std::vector<std::vector<int>> moveListOne, std::vector<std::vector<int>> moveListTwo)
{

    // Clear the pieces valid moves list
    boardPtr[x][y]->getValidMoves()->clear();

    // Loop through each move in the pieces move list
    for (std::vector<int> moveOne : moveListOne)
    {
        int moveOneX = moveOne[0];
        int moveOneY = moveOne[1];

        // Loop through each move in the board-check move list
        for (std::vector<int> moveTwo : moveListTwo)
        {
            int moveTwoX = moveTwo[0];
            int moveTwoY = moveTwo[1];

            // If the positions are equal
            if (moveOneX == moveTwoX && moveOneY == moveTwoY)
            {
                boardPtr[x][y]->addMove(moveOneX, moveOneY);
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
        if (*boardPtr[x][y]->getMoveCounter() == 0)
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
        if (*boardPtr[x][y]->getMoveCounter() == 0)
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
                        // Check if the attacking pawn is in the correct spot
                        if (x == xValue)
                        {
                            boardPtr[x][y]->addMove(x + xDirection, y + futureY);
                        }
                    }
                }
            }
        }
    }
}

// Get possible moves for rook
void ValidMoves::getRook(Board *board, Piece *boardPtr[8][8], int x, int y)
{
    std::vector<std::vector<int>> possibleMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    calculateLinearMoves(board, boardPtr, possibleMoves, x, y);
}

// Get possible moves for knight
void ValidMoves::getKnight(Board *board, Piece *boardPtr[8][8], int x, int y)
{
    std::vector<std::vector<int>> possibleMoves = {{2, 1}, {2, -1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {1, -2}, {-1, -2}};
    calculateSingleMoves(boardPtr, possibleMoves, x, y);
}

// Get possible moves for bishop
void ValidMoves::getBishop(Board *board, Piece *boardPtr[8][8], int x, int y)
{
    std::vector<std::vector<int>> possibleMoves = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    calculateLinearMoves(board, boardPtr, possibleMoves, x, y);
}

// Get possible moves for king
void ValidMoves::getKing(Piece *boardPtr[8][8], int x, int y)
{
    // Clear the pieces valid moves list
    boardPtr[x][y]->getValidMoves()->clear();

    // Possible moves for a king to move
    std::vector<std::vector<int>> possibleMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

    // Loop through possible moves
    for (std::vector<int> move : possibleMoves)
    {
        // Check for out of bounds error
        if (checkBoundary(x + move[0], y + move[1]))
        {
            // If the possible move color is not the same as the moving color and the possible move is not a king
            if (*boardPtr[x + move[0]][y + move[1]]->getPieceColor() != *boardPtr[x][y]->getPieceColor() && *boardPtr[x + move[0]][y + move[1]]->getPieceType() != pieceType::KING)
            {
                // Check to see if the next move would put the king in check
                bool check;
                std::vector<std::vector<int>> checkMoves;

                isKingInCheck(boardPtr, x + move[0], y + move[1], *boardPtr[x][y]->getPieceColor(), checkMoves, check);

                // If it's safe, add the move to the kings list of valid moves
                if (!check)
                {
                    boardPtr[x][y]->addMove(x + move[0], y + move[1]);
                }
            }
        }
    }
}

// Get possible moves for queen
void ValidMoves::getQueen(Board *board, Piece *boardPtr[8][8], int x, int y)
{
    std::vector<std::vector<int>> possibleMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    calculateLinearMoves(board, boardPtr, possibleMoves, x, y);
}

// Check if the move just played was a passant capture
bool ValidMoves::isThisMoveEnPassant(Piece *boardPtr[8][8], int startX, int startY, int endX, int endY)
{
    int startColor = *boardPtr[startX][startY]->getPieceColor();
    int startType = *boardPtr[startX][startY]->getPieceType();

    int endColor = *boardPtr[endX][endY]->getPieceColor();
    int endType = *boardPtr[endX][endY]->getPieceType();

    if (startType == pieceType::PAWN)
    {
        if (endType == pieceType::NONE)
        {
            if (startY != endY)
            {
                return true;
            }
        }
    }
    return false;
};

// Check if a king can castle
void ValidMoves::checkCastle(Board *board, Piece *boardPtr[8][8], int x, int y)
{
    bool continueSearch = false;
    int kingColor = *boardPtr[x][y]->getPieceColor();

    if (kingColor == pieceColor::WHITE)
    {
        if (!board->hasWhiteCastled)
        {
            continueSearch = true;
        }
    }
    else if (!board->hasBlackCastled)
    {
        continueSearch = true;
    }

    if (continueSearch)
    {
        bool check;
        std::vector<std::vector<int>> dummyMoves;
        if (*boardPtr[x][y]->getMoveCounter() == 0)
        {
            // Check if king can castle with right rook
            if (*boardPtr[x][y + 1]->getPieceType() == pieceType::NONE)
            {
                // Check if the king would pass through check
                isKingInCheck(boardPtr, x, y + 1, kingColor, dummyMoves, check);
                if (!check)
                {
                    // Check if the square is empty
                    if (*boardPtr[x][y + 2]->getPieceType() == pieceType::NONE)
                    {
                        // Check if the king would pass through check
                        isKingInCheck(boardPtr, x, y + 2, kingColor, dummyMoves, check);
                        if (!check)
                        {
                            // Check if the corner square is a rook and that it hasn't moved
                            if (*boardPtr[x][y + 3]->getPieceType() == pieceType::ROOK)
                            {
                                if (*boardPtr[x][y + 3]->getMoveCounter() == 0)
                                {
                                    boardPtr[x][y]->addMove(x, y + 3);
                                }
                            }
                        }
                    }
                }
            }
            // Check if king can castle with left rook
            if (*boardPtr[x][y - 1]->getPieceType() == pieceType::NONE)
            {
                // Check if the king would pass through check
                isKingInCheck(boardPtr, x, y - 1, kingColor, dummyMoves, check);
                if (!check)
                {
                    // Check if the square is empty
                    if (*boardPtr[x][y - 2]->getPieceType() == pieceType::NONE)
                    {
                        // Check if the king would pass through check
                        isKingInCheck(boardPtr, x, y - 2, kingColor, dummyMoves, check);
                        if (!check)
                        {
                            // Check if the square is empty
                            if (*boardPtr[x][y - 3]->getPieceType() == pieceType::NONE)
                            {
                                // Check if the king would pass through check
                                isKingInCheck(boardPtr, x, y - 3, kingColor, dummyMoves, check);
                                if (!check)
                                {
                                    // Check if the corner square is a rook and that it hasn't moved
                                    if (*boardPtr[x][y - 4]->getPieceType() == pieceType::ROOK)
                                    {
                                        if (*boardPtr[x][y - 4]->getMoveCounter() == 0)
                                        {
                                            boardPtr[x][y]->addMove(x, y - 4);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Calculates the possible moves in a single direction in a directions provided
void ValidMoves::calculateLinearMoves(Board *board, Piece *boardPtr[8][8], std::vector<std::vector<int>> possibleMoves, int originalX, int originalY)
{
    // Loop through each move in the possibleMoves list
    for (std::vector<int> move : possibleMoves)
    {
        int tempX = originalX;
        int tempY = originalY;
        int originalColor = *boardPtr[originalX][originalY]->getPieceColor();
        bool continueSearching = true;

        // While continueSearching is true
        while (continueSearching)
        {
            // Check for out-of-bounds error
            if (checkBoundary(tempX + move[0], tempY + move[1]))
            {

                // If the next move is an empty cell
                if (*boardPtr[tempX + move[0]][tempY + move[1]]->getPieceColor() == pieceColor::NONE)
                {
                    // Add move to the pieces valid move list and update the position
                    boardPtr[originalX][originalY]->addMove(tempX + move[0], tempY + move[1]);
                    tempX += move[0];
                    tempY += move[1];
                }
                // Else if the move color is equal to the original piece color or is equal to a king
                else if (*boardPtr[tempX + move[0]][tempY + move[1]]->getPieceColor() == originalColor || *boardPtr[tempX + move[0]][tempY + move[1]]->getPieceType() == pieceType::KING)
                {
                    continueSearching = false;
                }
                // Else if the move color is not equal to the original piece color
                else
                {
                    boardPtr[originalX][originalY]->addMove(tempX + move[0], tempY + move[1]);
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

// See if the king is in check based on the perspective of the king
void ValidMoves::isKingInCheck(Piece *boardPtr[8][8], int kingX, int kingY, int kingColor, std::vector<std::vector<int>> &checkMoves, bool &isInCheck)
{
    checkMoves.clear();

    // Detect if a king is in check by a pawn
    detectCheckFromPawn(boardPtr, kingX, kingY, kingColor, checkMoves);

    // Check if a king is in check by a rook, bishop, or queen
    std::vector<std::vector<int>> possibleRookAndQueenMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::vector<std::vector<int>> possibleBishopAndQueenMoves = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    detectCheckFromLinearPieces(boardPtr, possibleRookAndQueenMoves, kingX, kingY, kingColor, pieceType::ROOK, checkMoves);
    detectCheckFromLinearPieces(boardPtr, possibleBishopAndQueenMoves, kingX, kingY, kingColor, pieceType::BISHOP, checkMoves);

    std::vector<std::vector<int>> possibleKnightMoves = {{2, 1}, {2, -1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {1, -2}, {-1, -2}};
    std::vector<std::vector<int>> possibleKingMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    detectCheckFromSingularPieces(boardPtr, possibleKnightMoves, kingX, kingY, kingColor, pieceType::KNIGHT, checkMoves);
    detectCheckFromSingularPieces(boardPtr, possibleKingMoves, kingX, kingY, kingColor, pieceType::KING, checkMoves);

    if (checkMoves.size() > 0)
    {
        isInCheck = true;
    }
    else
    {
        isInCheck = false;
    }
}

void ValidMoves::detectCheckFromPawn(Piece *boardPtr[8][8], int kingX, int kingY, int kingColor, std::vector<std::vector<int>> &checkMoves)
{
    // Check if a king is in check by a pawn
    std::vector<std::vector<int>> possiblePawnMoves;

    // Possible spaces where a white pawn could take a black king
    if (kingColor == pieceColor::WHITE)
    {
        possiblePawnMoves = {{1, 1}, {1, -1}};
    }
    // Possible spaces where a black pawn could take a white king
    else
    {
        possiblePawnMoves = {{-1, 1}, {-1, -1}};
    }
    for (std::vector<int> move : possiblePawnMoves)
    {
        if (checkBoundary(kingX + move[0], kingY + move[1]))
        {
            // If the space is the opposite color of the king and is a pawn
            if (*boardPtr[kingX + move[0]][kingY + move[1]]->getPieceColor() != kingColor && *boardPtr[kingX + move[0]][kingY + move[1]]->getPieceType() == pieceType::PAWN)
            {
                checkMoves.push_back(std::vector<int>{kingX + move[0], kingY + move[1]});
            }
        }
    }
}

void ValidMoves::detectCheckFromLinearPieces(Piece *board[8][8], std::vector<std::vector<int>> possibleMoves, int kingX, int kingY, int kingColor, int type, std::vector<std::vector<int>> &finalXRayPath)
{
    for (std::vector<int> move : possibleMoves)
    {
        int tempX = kingX;
        int tempY = kingY;
        bool continueSearching = true;
        std::vector<std::vector<int>> tempXRayPath;

        while (continueSearching)
        {
            if (checkBoundary(tempX + move[0], tempY + move[1]))
            {
                int futureType = *board[tempX + move[0]][tempY + move[1]]->getPieceType();
                int futureColor = *board[tempX + move[0]][tempY + move[1]]->getPieceColor();
                // If the next move is an empty cell
                if (futureColor == pieceColor::NONE ||
                    (futureType == pieceType::KING && futureColor == kingColor))
                {
                    tempXRayPath.push_back(std::vector<int>{tempX + move[0], tempY + move[1]});
                    tempX += move[0];
                    tempY += move[1];
                }
                // Else if the next move is an opposite color than the king and is equals the correct type
                else if (futureColor != kingColor && (futureType == type || futureType == pieceType::QUEEN))
                {
                    tempXRayPath.push_back(std::vector<int>{tempX + move[0], tempY + move[1]});

                    for (auto move : tempXRayPath)
                    {
                        finalXRayPath.push_back(std::vector<int>{move[0], move[1]});
                    }

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

void ValidMoves::detectCheckFromSingularPieces(Piece *boardPtr[8][8], std::vector<std::vector<int>> possibleMoves, int kingX, int kingY, int kingColor, int type, std::vector<std::vector<int>> &checkMoves)
{
    for (std::vector<int> move : possibleMoves)
    {
        if (checkBoundary(kingX + move[0], kingY + move[1]))
        {
            // If the space is the opposite color of the king and is a pawn
            if (*boardPtr[kingX + move[0]][kingY + move[1]]->getPieceColor() != kingColor && *boardPtr[kingX + move[0]][kingY + move[1]]->getPieceType() == type)
            {
                checkMoves.push_back(std::vector<int>{kingX + move[0], kingY + move[1]});
            }
        }
    }
}

// For each rook, bishop, and queen of the opposite turns color, check if they pin any pieces
void ValidMoves::detectPinnedPieces(Piece *boardPtr[8][8], int color, int x, int y)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            // If the piece color is opposite of the current turns color
            if (*boardPtr[row][col]->getPieceColor() != color)
            {
                if (*boardPtr[row][col]->getPieceType() == pieceType::ROOK)
                {
                    std::vector<std::vector<int>> possibleRookMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
                    linearPiecePin(boardPtr, possibleRookMoves, row, col, x, y);
                }
                else if (*boardPtr[row][col]->getPieceType() == pieceType::QUEEN)
                {
                    std::vector<std::vector<int>> possibleQueenMoves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
                    linearPiecePin(boardPtr, possibleQueenMoves, row, col, x, y);
                }
                else if (*boardPtr[row][col]->getPieceType() == pieceType::BISHOP)
                {
                    std::vector<std::vector<int>> possibleBishopMoves = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
                    linearPiecePin(boardPtr, possibleBishopMoves, row, col, x, y);
                }
            }
        }
    }
}

// Cast a ray in all directions from the perspective of opposing rook, queen, and bishops
void ValidMoves::linearPiecePin(Piece *boardPtr[8][8], std::vector<std::vector<int>> possibleMoves, int pinnerX, int pinnerY, int pinnedPieceX, int pinnedPieceY)
{
    // Loop through each move in the possibleMoves list
    for (std::vector<int> move : possibleMoves)
    {
        int tempX = pinnerX;
        int tempY = pinnerY;
        int originalColor = *boardPtr[pinnerX][pinnerY]->getPieceColor();
        bool continueSearching = true;
        int pieceCountBetweenPinnerAndKing = 0;
        int pinnedPieceX;
        int pinnedPieceY;

        std::vector<std::vector<int>> pinnedPieceMoveList = {{pinnerX, pinnerY}};

        // While continueSearching is true
        while (continueSearching)
        {
            // Check for out-of-bounds error
            if (checkBoundary(tempX + move[0], tempY + move[1]))
            {

                // If the next move is an empty cell
                if (*boardPtr[tempX + move[0]][tempY + move[1]]->getPieceColor() == pieceColor::NONE)
                {
                    if (pieceCountBetweenPinnerAndKing != 1)
                    {
                        pinnedPieceMoveList.push_back(std::vector<int>{tempX + move[0], tempY + move[1]});
                    }
                    tempX += move[0];
                    tempY += move[1];
                }
                // Else if the move type is equal to a king
                else if (*boardPtr[tempX + move[0]][tempY + move[1]]->getPieceType() == pieceType::KING && *boardPtr[tempX + move[0]][tempY + move[1]]->getPieceColor() != originalColor)
                {
                    // If theres only one piece between the pinner and the king, then that piece is pinned
                    if (pieceCountBetweenPinnerAndKing == 1)
                    {
                        std::vector<std::vector<int>> *validMoves = boardPtr[pinnedPieceX][pinnedPieceY]->getValidMoves();

                        // Compare the moves list between the cast from the pinner and the pieces valid moves
                        if (pinnedPieceX == pinnedPieceX && pinnedPieceY == pinnedPieceY)
                        {
                            compareTwoMovesLists(boardPtr, pinnedPieceX, pinnedPieceY, *validMoves, pinnedPieceMoveList);
                        }
                    }
                    continueSearching = false;
                }
                // Else if the move color is equal to the original piece color
                else if (*boardPtr[tempX + move[0]][tempY + move[1]]->getPieceColor() == originalColor)
                {
                    continueSearching = false;
                }
                // Else if the move color is not equal to the original piece color
                else
                {
                    // Save the position of the pinned piece
                    if (pieceCountBetweenPinnerAndKing == 0)
                    {
                        pinnedPieceX = tempX + move[0];
                        pinnedPieceY = tempY + move[1];
                    }
                    tempX += move[0];
                    tempY += move[1];
                    pieceCountBetweenPinnerAndKing += 1;
                }
            }
            else
            {
                continueSearching = false;
            }
        }
    }
}
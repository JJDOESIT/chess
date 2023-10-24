#include "board.h"
#include "globalValues.h"

void Board::initilizeBoard()
{
    // White pieces
    board[0][0] = new Piece(pieceType::ROOK, pieceColor::WHITE, 0, 0, "./sprites/white_rook.png");
    board[0][1] = new Piece(pieceType::KNIGHT, pieceColor::WHITE, 0, 1, "./sprites/white_knight.png");
    board[0][2] = new Piece(pieceType::BISHOP, pieceColor::WHITE, 0, 2, "./sprites/white_bishop.png");
    board[0][5] = new Piece(pieceType::BISHOP, pieceColor::WHITE, 0, 5, "./sprites/white_bishop.png");
    board[0][6] = new Piece(pieceType::KNIGHT, pieceColor::WHITE, 0, 6, "./sprites/white_knight.png");
    board[0][7] = new Piece(pieceType::ROOK, pieceColor::WHITE, 0, 7, "./sprites/white_rook.png");
    board[0][3] = new Piece(pieceType::QUEEN, pieceColor::WHITE, 0, 3, "./sprites/white_queen.png");
    board[0][4] = new Piece(pieceType::KING, pieceColor::WHITE, 0, 4, "./sprites/white_king.png");

    board[1][0] = new Piece(pieceType::PAWN, pieceColor::WHITE, 1, 0, "./sprites/white_pawn.png");
    board[1][1] = new Piece(pieceType::PAWN, pieceColor::WHITE, 1, 1, "./sprites/white_pawn.png");
    board[1][2] = new Piece(pieceType::PAWN, pieceColor::WHITE, 1, 2, "./sprites/white_pawn.png");
    board[1][3] = new Piece(pieceType::PAWN, pieceColor::WHITE, 1, 3, "./sprites/white_pawn.png");
    board[1][4] = new Piece(pieceType::PAWN, pieceColor::WHITE, 1, 4, "./sprites/white_pawn.png");
    board[1][5] = new Piece(pieceType::PAWN, pieceColor::WHITE, 1, 5, "./sprites/white_pawn.png");
    board[1][6] = new Piece(pieceType::PAWN, pieceColor::WHITE, 1, 6, "./sprites/white_pawn.png");
    board[1][7] = new Piece(pieceType::PAWN, pieceColor::WHITE, 1, 7, "./sprites/white_pawn.png");

    // Create 4 rows of empty pieces
    for (int row = 2; row < 6; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            board[row][col] = new Piece(pieceType::NONE, pieceColor::NONE, row, col);
        }
    }

    // Black pieces
    board[7][0] = new Piece(pieceType::ROOK, pieceColor::BLACK, 7, 0, "./sprites/black_rook.png");
    board[7][1] = new Piece(pieceType::KNIGHT, pieceColor::BLACK, 7, 1, "./sprites/black_knight.png");
    board[7][2] = new Piece(pieceType::BISHOP, pieceColor::BLACK, 7, 2, "./sprites/black_bishop.png");
    board[7][5] = new Piece(pieceType::BISHOP, pieceColor::BLACK, 7, 5, "./sprites/black_bishop.png");
    board[7][6] = new Piece(pieceType::KNIGHT, pieceColor::BLACK, 7, 6, "./sprites/black_knight.png");
    board[7][7] = new Piece(pieceType::ROOK, pieceColor::BLACK, 7, 7, "./sprites/black_rook.png");
    board[7][3] = new Piece(pieceType::QUEEN, pieceColor::BLACK, 7, 3, "./sprites/black_queen.png");
    board[7][4] = new Piece(pieceType::KING, pieceColor::BLACK, 7, 4, "./sprites/black_king.png");

    board[6][0] = new Piece(pieceType::PAWN, pieceColor::BLACK, 6, 0, "./sprites/black_pawn.png");
    board[6][1] = new Piece(pieceType::PAWN, pieceColor::BLACK, 6, 1, "./sprites/black_pawn.png");
    board[6][2] = new Piece(pieceType::PAWN, pieceColor::BLACK, 6, 2, "./sprites/black_pawn.png");
    board[6][3] = new Piece(pieceType::PAWN, pieceColor::BLACK, 6, 3, "./sprites/black_pawn.png");
    board[6][4] = new Piece(pieceType::PAWN, pieceColor::BLACK, 6, 4, "./sprites/black_pawn.png");
    board[6][5] = new Piece(pieceType::PAWN, pieceColor::BLACK, 6, 5, "./sprites/black_pawn.png");
    board[6][6] = new Piece(pieceType::PAWN, pieceColor::BLACK, 6, 6, "./sprites/black_pawn.png");
    board[6][7] = new Piece(pieceType::PAWN, pieceColor::BLACK, 6, 7, "./sprites/black_pawn.png");
}

// Testing only: Place any piece on the board
void Board::overwritePiece(int type, int color, int x, int y)
{
    overwriteList.push_back(Piece(type, color, x, y));
    Piece *piecePtr = &overwriteList[0];
    board[x][y] = piecePtr;
}

// Set the position of the last moved white piece
void Board::setPositionOfLastMovedWhitePiece(int x, int y)
{
    positionOfLastMovedWhitePiece[0] = x;
    positionOfLastMovedWhitePiece[1] = y;
}

// Return a pointer to the position of the last moved white piece
std::vector<int> *Board::getpositionOfLastMovedWhitePiece()
{
    return &positionOfLastMovedWhitePiece;
}

// Set the position of the last moved black piece
void Board::setPositionOfLastMovedBlackPiece(int x, int y)
{
    positionOfLastMovedBlackPiece[0] = x;
    positionOfLastMovedBlackPiece[1] = y;
}

// Return a pointer to the position of the last moved black piece
std::vector<int> *Board::getpositionOfLastMovedBlackPiece()
{
    return &positionOfLastMovedBlackPiece;
}

// Set the position of the most recent piece moved
void Board::setPositionOfMostRecentPiece(int x, int y)
{
    positionOfMostRecentMove[0] = x;
    positionOfMostRecentMove[1] = y;
}

// Swap two pieces in the board
void Board::swapPieces(Piece *boardPtr[8][8], int x1, int y1, int x2, int y2)
{
    Piece *tempPiecePtr = boardPtr[x1][y1];
    boardPtr[x1][y1] = boardPtr[x2][y2];
    boardPtr[x2][y2] = tempPiecePtr;

    int *positionOne = boardPtr[x1][y1]->getPiecePosition();
    int *positionTwo = boardPtr[x2][y2]->getPiecePosition();

    int tempX = positionOne[0];
    int tempY = positionOne[1];

    boardPtr[x1][y1]->setPiecePosition(positionTwo[0], positionTwo[1]);
    boardPtr[x2][y2]->setPiecePosition(tempX, tempY);
}

// Take a piece and deconstruct it
void Board::takePiece(Piece *boardPtr[8][8], int attackingX, int attackingY, int defendingX, int defendingY, bool simulate)
{
    if (!simulate)
    {
        erasePiece(boardPtr, defendingX, defendingY);
    }
    clearPiece(boardPtr, defendingX, defendingY);
    swapPieces(boardPtr, attackingX, attackingY, defendingX, defendingY);
}

// Erase piece
void Board::erasePiece(Piece *boardPtr[8][8], int x, int y)
{
    boardPtr[x][y]->deleteTexture();
    boardPtr[x][x]->getValidMoves()->clear();
}

// Set piece type and color to null
void Board::clearPiece(Piece *boardPtr[8][8], int x, int y)
{
    boardPtr[x][y]->setPieceType(pieceType::NONE);
    boardPtr[x][y]->setPieceColor(pieceColor::NONE);
}

// Return a pointer to current turn
int *Board::getCurrentTurn()
{
    return &turn;
}

// Switch current turn
void Board::switchTurn()
{
    turn = !turn;
}

// Check to see if the move being taken is a passant take
void Board::checkForPassant(Piece *boardPtr[8][8], int x, int y, bool simulate)
{
    if (*boardPtr[x][y]->getPieceType() == pieceType::PAWN)
    {
        if (*boardPtr[x][y]->getPieceColor() == pieceColor::BLACK)
        {
            if (*boardPtr[x + 1][y]->getPieceType() == pieceType::PAWN)
            {
                if (!simulate)
                {
                    erasePiece(boardPtr, x + 1, y);
                }

                clearPiece(boardPtr, x + 1, y);
            }
        }
        // If the attacking pawn is white
        else if (*boardPtr[x][y]->getPieceColor() == pieceColor::WHITE)
        {
            // If the piece right below the pawn is another pawn
            if (*boardPtr[x - 1][y]->getPieceType() == pieceType::PAWN)
            {
                if (!simulate)
                {
                    // Clear piece and its data
                    erasePiece(boardPtr, x - 1, y);
                }
                // Set the pawn to an empty cell
                clearPiece(boardPtr, x - 1, y);
            }
        }
    }
}

// Check if a pawn should be promoted
void Board::checkPawnPromotion(Piece *boardPtr[8][8], int x, int y, bool simulate)
{
    if (*boardPtr[x][y]->getPieceColor() == pieceColor::WHITE)
    {
        if (x == 7)
        {
            promotePiece(boardPtr, x, y, pieceType::QUEEN, simulate);
        }
    }
    else
    {
        if (x == 0)
        {
            promotePiece(boardPtr, x, y, pieceType::QUEEN, simulate);
        }
    }
}

// Promote a piece into the given type
void Board::promotePiece(Piece *boardPtr[8][8], int x, int y, int type, bool simulate)
{
    boardPtr[x][y]->setPieceType(type);

    if (!simulate)
    {
        int color = *boardPtr[x][y]->getPieceColor();

        switch (type)
        {
        case (pieceType::ROOK):
            if (color == pieceColor::WHITE)
            {
                boardPtr[x][y]->setTexture("./sprites/white_rook.png");
            }
            else
            {
                boardPtr[x][y]->setTexture("./sprites/black_rook.png");
            }
            break;
        case (pieceType::BISHOP):
            if (color == pieceColor::WHITE)
            {
                boardPtr[x][y]->setTexture("./sprites/white_bishop.png");
            }
            else
            {
                boardPtr[x][y]->setTexture("./sprites/black_bishop.png");
            }
            break;
        case (pieceType::KNIGHT):
            if (color == pieceColor::WHITE)
            {
                boardPtr[x][y]->setTexture("./sprites/white_knight.png");
            }
            else
            {
                boardPtr[x][y]->setTexture("./sprites/black_knight.png");
            }
            break;
        case (pieceType::QUEEN):
            if (color == pieceColor::WHITE)
            {
                boardPtr[x][y]->setTexture("./sprites/white_queen.png");
            }
            else
            {
                boardPtr[x][y]->setTexture("./sprites/black_queen.png");
            }
            break;
        }
    }
}

// Castle a king and rook
void Board::castle(Piece *boardPtr[8][8], int attackingX, int attackingY, int defendingX, int defendingY, int &positionDifferential, bool simulate)
{
    if (defendingY == 0)
    {
        swapPieces(boardPtr, attackingX, attackingY, attackingX, attackingY - 2);
        swapPieces(boardPtr, defendingX, defendingY, defendingX, defendingY + 3);
        positionDifferential = 2;
    }
    else if (defendingY == 7)
    {
        swapPieces(boardPtr, attackingX, attackingY, attackingX, attackingY + 2);
        swapPieces(boardPtr, defendingX, defendingY, defendingX, defendingY - 2);
        positionDifferential = -1;
    }

    if (!simulate)
    {
        if (turn == playerTurn::WHITE)
        {
            hasWhiteCastled = true;
        }
        else
        {
            hasBlackCastled = true;
        }
    }
}

// Move piece
void Board::movePiece(Piece *boardPtr[8][8], int attackingX, int attackingY, int defendingX, int defendingY, bool simulate)
{
    // Increament the pieces total move count
    boardPtr[attackingX][attackingY]->increamentMoveCounter();

    int yPositionDifferential = 0;
    bool isCastle;

    // If the square a piece is moving too is empty, swap the two pointers
    if (*boardPtr[defendingX][defendingY]->getPieceType() == pieceType::NONE)
    {
        swapPieces(boardPtr, attackingX, attackingY, defendingX, defendingY);

        // If the attacking piece is a pawn, check if the attack was a passant move
        if (*boardPtr[defendingX][defendingY]->getPieceType() == pieceType::PAWN)
        {
            checkForPassant(boardPtr, defendingX, defendingY, simulate);
        }
    }
    // Else if the square has another piece on it, destory the piece and deconstruct its data
    else
    {
        // If the current move is a castle, castle the king and the rook
        if (*boardPtr[attackingX][attackingY]->getPieceType() == pieceType::KING &&
            *boardPtr[defendingX][defendingY]->getPieceType() == pieceType::ROOK &&
            *boardPtr[attackingX][attackingY]->getPieceColor() == *boardPtr[defendingX][defendingY]->getPieceColor())
        {
            boardPtr[defendingX][defendingY]->increamentMoveCounter();
            castle(boardPtr, attackingX, attackingY, defendingX, defendingY, yPositionDifferential, simulate);
        }
        // Else take the piece normally
        else
        {
            takePiece(boardPtr, attackingX, attackingY, defendingX, defendingY, simulate);
        }
    }

    if (*boardPtr[defendingX][defendingY]->getPieceType() == pieceType::PAWN)
    {
        checkPawnPromotion(boardPtr, defendingX, defendingY, simulate);
    }

    // Set the position of the last moved piece to its corresponding color
    if (!simulate)
    {
        if (*getCurrentTurn() == playerTurn::WHITE)
        {
            totalWhiteMoveCount += 1;
            setPositionOfLastMovedWhitePiece(defendingX, defendingY);
        }
        else
        {
            setPositionOfLastMovedBlackPiece(defendingX, defendingY);
        }
        setPositionOfMostRecentPiece(defendingX, defendingY + yPositionDifferential);
    }
}

// Move a piece and check if the new position is a valid move
void Board::movePieceWithCheck(sf::RenderWindow &window, Piece *boardPtr[8][8], std::vector<std::vector<int>> *moves, int x, int y)
{
    for (auto move : *moves)
    {
        if (move[0] == x && move[1] == y)
        {
            // Move piece
            movePiece(boardPtr, swapBuffer[0], swapBuffer[1], x, y, false);

            // Re-draw the board
            drawBoard(window);
            drawSprites(window);
            window.display();

            // Switch current turn
            switchTurn();
        }
    }
    // Swap modes and clear possible moves list
    mode = playerMode::NONE;
    moves->clear();
}

// Move piece without checking if the new position is a valid move
void Board::movePieceWithoutCheck(Piece *boardPtr[8][8], int attackingX, int attackingY, int defendingX, int defendingY, bool simulate)
{
    movePiece(boardPtr, attackingX, attackingY, defendingX, defendingY, simulate);
}

// Undo move (used in AI calculations)
void Board::undoMove(Piece *boardPtr[8][8], int positionOfAttackingX,
                     int positionOfAttackingY,
                     int positionOfDefendingX,
                     int positionOfDefendingY, int attackingType,
                     int defendingType,
                     int attackingColor,
                     int defendingColor,
                     bool isPassant,
                     bool isCastle,
                     bool isPromotion)
{
    // If the piece was not castled
    if (!isCastle)
    {
        // Swap the two pieces back
        swapPieces(boardPtr,
                   positionOfAttackingX,
                   positionOfAttackingY,
                   positionOfDefendingX,
                   positionOfDefendingY);

        // Restore the original data types of the pieces
        board[positionOfAttackingX][positionOfAttackingY]->setPieceType(attackingType);
        board[positionOfAttackingX][positionOfAttackingY]->setPieceColor(attackingColor);

        board[positionOfDefendingX][positionOfDefendingY]->setPieceType(defendingType);
        board[positionOfDefendingX][positionOfDefendingY]->setPieceColor(defendingColor);

        board[positionOfAttackingX][positionOfAttackingY]->decreamentMoveCounter();
    }

    // If the piece was castled
    else
    {
        if (positionOfDefendingY == 0)
        {
            swapPieces(boardPtr, positionOfAttackingX, positionOfAttackingY, positionOfAttackingX, positionOfAttackingY - 2);
            swapPieces(boardPtr, positionOfDefendingX, positionOfDefendingY, positionOfDefendingX, positionOfDefendingY + 3);
        }
        else if (positionOfDefendingY == 7)
        {
            swapPieces(boardPtr, positionOfAttackingX, positionOfAttackingY, positionOfAttackingX, positionOfAttackingY + 2);
            swapPieces(boardPtr, positionOfDefendingX, positionOfDefendingY, positionOfDefendingX, positionOfDefendingY - 2);
        }
        board[positionOfAttackingX][positionOfAttackingY]->decreamentMoveCounter();
        board[positionOfDefendingX][positionOfDefendingY]->decreamentMoveCounter();
    }

    // Used in the undo move section of the AI. If it sees that the AI did an En Passant Capture, then it will
    // not only undo the swapping of the two pieces, but restore the captured pawn
    if (isPassant)
    {
        if (attackingColor == pieceColor::WHITE)
        {
            boardPtr[positionOfDefendingX - 1][positionOfDefendingY]->setPieceColor(pieceColor::BLACK);
            boardPtr[positionOfDefendingX - 1][positionOfDefendingY]->setPieceType(pieceType::PAWN);
        }
    }

    // Turn the promoted piece back into a pawn
    if (isPromotion)
    {
        boardPtr[positionOfAttackingX][positionOfAttackingY]->setPieceType(pieceType::PAWN);
    }
}

// Copy data from one board to another
void Board::copyArray(Piece *copyFrom[8][8], Piece *copyTo[8][8])
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
void Board::deleteArray(Piece *array[8][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            delete array[row][col];
        }
    }
}

// Draw all sprites to the board
void Board::drawSprites(sf::RenderWindow &window)
{
    isPieceMoving = false;
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (*board[row][col]->getPieceType() != pieceType::NONE)
            {
                sf::Sprite sprite = *board[row][col]->getSprite();
                int *position = board[row][col]->getPiecePosition();

                float *positionBuffer = board[row][col]->getPiecePositionBuffer();

                if (positionBuffer[0] - position[0] <= -0.001)
                {
                    positionBuffer[0] += 0.125;
                    isPieceMoving = true;
                }
                else if (positionBuffer[0] - position[0] >= 0.001)
                {
                    positionBuffer[0] -= 0.125;
                    isPieceMoving = true;
                }
                if (positionBuffer[1] - position[1] <= -0.001)
                {
                    positionBuffer[1] += 0.125;
                    isPieceMoving = true;
                }
                else if (positionBuffer[1] - position[1] >= 0.001)
                {
                    positionBuffer[1] -= 0.125;
                    isPieceMoving = true;
                }

                sprite.setPosition(sf::Vector2f(positionBuffer[1] * global::squareSize, positionBuffer[0] * global::squareSize));
                window.draw(sprite);
            }
        }
    }

    // Draw a border around the most recently moved piece

    if (!isPieceMoving)
    {
        const int outlineThickness = 4;
        sf::RectangleShape lastMovedPiece;
        lastMovedPiece.setFillColor(sf::Color::Transparent);
        lastMovedPiece.setSize(sf::Vector2f(global::squareSize - (outlineThickness * 2), global::squareSize - (outlineThickness * 2)));
        lastMovedPiece.setPosition(sf::Vector2f((positionOfMostRecentMove[1] * global::squareSize) + outlineThickness, (positionOfMostRecentMove[0] * global::squareSize) + outlineThickness));
        lastMovedPiece.setOutlineThickness(outlineThickness);
        lastMovedPiece.setOutlineColor(sf::Color(255, 215, 0, 255));
        window.draw(lastMovedPiece);
    }
}

// Draw background tiles
void Board::drawBoard(sf::RenderWindow &window)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(global::squareSize, global::squareSize));
            rect.setPosition(sf::Vector2f(row * global::squareSize, col * global::squareSize));
            if ((row + col) % 2 == 0)
            {
                rect.setFillColor(sf::Color(238, 214, 176));
            }
            else
            {
                rect.setFillColor(sf::Color(184, 134, 97));
            }

            window.draw(rect);
        }
    }
}

// Draw all possible moves when a piece is clicked
void Board::drawPossibleMoves(sf::RenderWindow &window, std::vector<std::vector<int>> *moves)
{
    for (std::vector<int> i : *moves)
    {
        sf::RectangleShape possibleMove;
        possibleMove.setSize(sf::Vector2f(global::squareSize, global::squareSize));
        possibleMove.setPosition(i[1] * global::squareSize, i[0] * global::squareSize);
        possibleMove.setFillColor(sf::Color(255, 150, 150, 100));
        window.draw(possibleMove);
    }
}
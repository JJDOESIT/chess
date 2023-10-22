#include "board.h"
#include "globalValues.h"

void Board::initPieceList()
{
    // White pieces
    Piece white_rook_one(pieceType::ROOK, pieceColor::WHITE, 0, 0, "./sprites/white_rook.png");
    Piece white_knight_one(pieceType::KNIGHT, pieceColor::WHITE, 0, 1, "./sprites/white_knight.png");
    Piece white_bishop_one(pieceType::BISHOP, pieceColor::WHITE, 0, 2, "./sprites/white_bishop.png");
    Piece white_bishop_two(pieceType::BISHOP, pieceColor::WHITE, 0, 5, "./sprites/white_bishop.png");
    Piece white_knight_two(pieceType::KNIGHT, pieceColor::WHITE, 0, 6, "./sprites/white_knight.png");
    Piece white_rook_two(pieceType::ROOK, pieceColor::WHITE, 0, 7, "./sprites/white_rook.png");
    Piece white_queen(pieceType::QUEEN, pieceColor::WHITE, 0, 3, "./sprites/white_queen.png");
    Piece white_king(pieceType::KING, pieceColor::WHITE, 0, 4, "./sprites/white_king.png");

    Piece white_pawn_one(pieceType::PAWN, pieceColor::WHITE, 1, 0, "./sprites/white_pawn.png");
    Piece white_pawn_two(pieceType::PAWN, pieceColor::WHITE, 1, 1, "./sprites/white_pawn.png");
    Piece white_pawn_three(pieceType::PAWN, pieceColor::WHITE, 1, 2, "./sprites/white_pawn.png");
    Piece white_pawn_four(pieceType::PAWN, pieceColor::WHITE, 1, 3, "./sprites/white_pawn.png");
    Piece white_pawn_five(pieceType::PAWN, pieceColor::WHITE, 1, 4, "./sprites/white_pawn.png");
    Piece white_pawn_six(pieceType::PAWN, pieceColor::WHITE, 1, 5, "./sprites/white_pawn.png");
    Piece white_pawn_seven(pieceType::PAWN, pieceColor::WHITE, 1, 6, "./sprites/white_pawn.png");
    Piece white_pawn_eight(pieceType::PAWN, pieceColor::WHITE, 1, 7, "./sprites/white_pawn.png");

    // Add white pieces to piece list
    pieceList.push_back(white_rook_one);
    pieceList.push_back(white_knight_one);
    pieceList.push_back(white_bishop_one);
    pieceList.push_back(white_bishop_two);
    pieceList.push_back(white_knight_two);
    pieceList.push_back(white_rook_two);
    pieceList.push_back(white_queen);
    pieceList.push_back(white_king);
    pieceList.push_back(white_pawn_one);
    pieceList.push_back(white_pawn_two);
    pieceList.push_back(white_pawn_three);
    pieceList.push_back(white_pawn_four);
    pieceList.push_back(white_pawn_five);
    pieceList.push_back(white_pawn_six);
    pieceList.push_back(white_pawn_seven);
    pieceList.push_back(white_pawn_eight);

    // Create 4 rows of empty pieces
    for (int row = 2; row < 6; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            pieceList.push_back(Piece(pieceType::NONE, pieceColor::NONE, row, col));
        }
    }

    // Black pieces
    Piece black_rook_one(pieceType::ROOK, pieceColor::BLACK, 7, 0, "./sprites/black_rook.png");
    Piece black_knight_one(pieceType::KNIGHT, pieceColor::BLACK, 7, 1, "./sprites/black_knight.png");
    Piece black_bishop_one(pieceType::BISHOP, pieceColor::BLACK, 7, 2, "./sprites/black_bishop.png");
    Piece black_bishop_two(pieceType::BISHOP, pieceColor::BLACK, 7, 5, "./sprites/black_bishop.png");
    Piece black_knight_two(pieceType::KNIGHT, pieceColor::BLACK, 7, 6, "./sprites/black_knight.png");
    Piece black_rook_two(pieceType::ROOK, pieceColor::BLACK, 7, 7, "./sprites/black_rook.png");
    Piece black_queen(pieceType::QUEEN, pieceColor::BLACK, 7, 3, "./sprites/black_queen.png");
    Piece black_king(pieceType::KING, pieceColor::BLACK, 7, 4, "./sprites/black_king.png");

    Piece black_pawn_one(pieceType::PAWN, pieceColor::BLACK, 6, 0, "./sprites/black_pawn.png");
    Piece black_pawn_two(pieceType::PAWN, pieceColor::BLACK, 6, 1, "./sprites/black_pawn.png");
    Piece black_pawn_three(pieceType::PAWN, pieceColor::BLACK, 6, 2, "./sprites/black_pawn.png");
    Piece black_pawn_four(pieceType::PAWN, pieceColor::BLACK, 6, 3, "./sprites/black_pawn.png");
    Piece black_pawn_five(pieceType::PAWN, pieceColor::BLACK, 6, 4, "./sprites/black_pawn.png");
    Piece black_pawn_six(pieceType::PAWN, pieceColor::BLACK, 6, 5, "./sprites/black_pawn.png");
    Piece black_pawn_seven(pieceType::PAWN, pieceColor::BLACK, 6, 6, "./sprites/black_pawn.png");
    Piece black_pawn_eight(pieceType::PAWN, pieceColor::BLACK, 6, 7, "./sprites/black_pawn.png");

    // Add black pieces to piece list
    pieceList.push_back(black_rook_one);
    pieceList.push_back(black_knight_one);
    pieceList.push_back(black_bishop_one);
    pieceList.push_back(black_bishop_two);
    pieceList.push_back(black_knight_two);
    pieceList.push_back(black_rook_two);
    pieceList.push_back(black_queen);
    pieceList.push_back(black_king);
    pieceList.push_back(black_pawn_one);
    pieceList.push_back(black_pawn_two);
    pieceList.push_back(black_pawn_three);
    pieceList.push_back(black_pawn_four);
    pieceList.push_back(black_pawn_five);
    pieceList.push_back(black_pawn_six);
    pieceList.push_back(black_pawn_seven);
    pieceList.push_back(black_pawn_eight);
}

// Return a pointer to pieceList
std::vector<Piece> *Board::getPieceList()
{
    return &pieceList;
}

// Print the board to the console
void Board::printBoard(Piece *boardPtr[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int *type = boardPtr[i][j]->getPieceType();
            std::cout << *type;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Fill the board with pieces in the piece list
void Board::fillBoard()
{
    for (int i = 0; i < pieceList.size(); i++)
    {
        int *piecePosition = pieceList[i].getPiecePosition();
        Piece *piecePtr = &pieceList[i];
        board[piecePosition[0]][piecePosition[1]] = piecePtr;
    }
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
void Board::takePiece(Piece *boardPtr[8][8], int overwriteX, int overwriteY, int overwrittenX, int overwrittenY, bool simulate)
{
    if (!simulate)
    {
        erasePiece(boardPtr, overwrittenX, overwrittenY);
    }
    clearPiece(boardPtr, overwrittenX, overwrittenY);
    swapPieces(boardPtr, overwriteX, overwriteY, overwrittenX, overwrittenY);
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

// Castle a king and rook
void Board::castle(Piece *boardPtr[8][8], int overWriteX, int overWriteY, int overWrittenX, int overWrittenY, int &positionDifferential, bool simulate)
{
    if (overWrittenY == 0)
    {
        swapPieces(boardPtr, overWriteX, overWriteY, overWriteX, overWriteY - 2);
        swapPieces(boardPtr, overWrittenX, overWrittenY, overWrittenX, overWrittenY + 3);
        positionDifferential = 2;
    }
    else if (overWrittenY == 7)
    {
        swapPieces(boardPtr, overWriteX, overWriteY, overWriteX, overWriteY + 2);
        swapPieces(boardPtr, overWrittenX, overWrittenY, overWrittenX, overWrittenY - 2);
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
void Board::movePiece(Piece *boardPtr[8][8], int overWriteX, int overWriteY, int overWrittenX, int overWrittenY, bool simulate)
{
    int yPositionDifferential = 0;
    bool isCastle;

    // If the square a piece is moving too is empty, swap the two pointers
    if (*boardPtr[overWrittenX][overWrittenY]->getPieceType() == pieceType::NONE)
    {
        swapPieces(boardPtr, overWriteX, overWriteY, overWrittenX, overWrittenY);

        // If the attacking piece is a pawn, check if the attack was a passant move
        if (*boardPtr[overWrittenX][overWrittenY]->getPieceType() == pieceType::PAWN)
        {
            checkForPassant(boardPtr, overWrittenX, overWrittenY, simulate);
        }
    }
    // Else if the square has another piece on it, destory the piece and deconstruct its data
    else
    {
        isCastle = (*boardPtr[overWriteX][overWriteY]->getPieceType() == pieceType::KING &&
                    *boardPtr[overWrittenX][overWrittenY]->getPieceType() == pieceType::ROOK &&
                    *boardPtr[overWriteX][overWriteY]->getPieceColor() == *boardPtr[overWrittenX][overWrittenY]->getPieceColor());
        // If the current move is a castle, castle the king and the rook
        if (isCastle)
        {
            boardPtr[overWrittenX][overWrittenY]->increamentMoveCounter();
            boardPtr[overWriteX][overWriteY]->increamentMoveCounter();
            castle(boardPtr, overWriteX, overWriteY, overWrittenX, overWrittenY, yPositionDifferential, simulate);
        }
        // Else take the piece normally
        else
        {
            takePiece(boardPtr, overWriteX, overWriteY, overWrittenX, overWrittenY, simulate);
        }
    }

    // Increase the times the piece has moved by 1
    if (!isCastle)
        boardPtr[overWrittenX][overWrittenY]->increamentMoveCounter();

    // Set the position of the last moved piece to its corresponding color
    if (!simulate)
    {
        if (*getCurrentTurn() == playerTurn::WHITE)
        {
            totalWhiteMoveCount += 1;
            setPositionOfLastMovedWhitePiece(overWrittenX, overWrittenY);
        }
        else
        {
            setPositionOfLastMovedBlackPiece(overWrittenX, overWrittenY);
        }
        setPositionOfMostRecentPiece(overWrittenX, overWrittenY + yPositionDifferential);
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
void Board::movePieceWithoutCheck(Piece *boardPtr[8][8], int overWriteX, int overWriteY, int overWrittenX, int overWrittenY, bool simulate)
{
    movePiece(boardPtr, overWriteX, overWriteY, overWrittenX, overWrittenY, simulate);
}

// Undo move (used in AI calculations)
void Board::undoMove(Piece *boardPtr[8][8], int positionOfOverWriteX,
                     int positionOfOverWriteY,
                     int positionOfOverWrittenX,
                     int positionOfOverWrittenY, int overWriteType,
                     int overWrittenType,
                     int overWriteColor,
                     int overWrittenColor,
                     bool isPassant,
                     bool isCastle)
{

    if (!isCastle)
    {
        // Swap the two pieces back
        swapPieces(boardPtr,
                   positionOfOverWriteX,
                   positionOfOverWriteY,
                   positionOfOverWrittenX,
                   positionOfOverWrittenY);

        // Restore the original data types of the pieces
        board[positionOfOverWriteX][positionOfOverWriteY]->setPieceType(overWriteType);
        board[positionOfOverWriteX][positionOfOverWriteY]->setPieceColor(overWriteColor);

        board[positionOfOverWrittenX][positionOfOverWrittenY]->setPieceType(overWrittenType);
        board[positionOfOverWrittenX][positionOfOverWrittenY]->setPieceColor(overWrittenColor);

        board[positionOfOverWriteX][positionOfOverWriteY]->decreamentMoveCounter();
    }

    else
    {
        if (positionOfOverWrittenY == 0)
        {
            swapPieces(boardPtr, positionOfOverWriteX, positionOfOverWriteY, positionOfOverWriteX, positionOfOverWriteY - 2);
            swapPieces(boardPtr, positionOfOverWrittenX, positionOfOverWrittenY, positionOfOverWrittenX, positionOfOverWrittenY + 3);
        }
        else if (positionOfOverWrittenY == 7)
        {
            swapPieces(boardPtr, positionOfOverWriteX, positionOfOverWriteY, positionOfOverWriteX, positionOfOverWriteY + 2);
            swapPieces(boardPtr, positionOfOverWrittenX, positionOfOverWrittenY, positionOfOverWrittenX, positionOfOverWrittenY - 2);
        }
        board[positionOfOverWriteX][positionOfOverWriteY]->decreamentMoveCounter();
        board[positionOfOverWrittenX][positionOfOverWrittenY]->decreamentMoveCounter();
    }

    // Used in the undo move section of the AI. If it sees that the AI did an En Passant Capture, then it will
    // not only undo the swapping of the two pieces, but restore the captured pawn
    if (isPassant)
    {
        if (overWriteColor == pieceColor::WHITE)
        {
            boardPtr[positionOfOverWrittenX - 1][positionOfOverWrittenY]->setPieceColor(pieceColor::BLACK);
            boardPtr[positionOfOverWrittenX - 1][positionOfOverWrittenY]->setPieceType(pieceType::PAWN);
        }
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
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (*board[row][col]->getPieceType() != pieceType::NONE)
            {
                sf::Sprite sprite = *board[row][col]->getSprite();
                int *position = board[row][col]->getPiecePosition();
                sprite.setPosition(sf::Vector2f(position[1] * global::squareSize, position[0] * global::squareSize));
                window.draw(sprite);
            }
        }
    }

    // Draw a border around the
    const int outlineThickness = 4;
    sf::RectangleShape lastMovedPiece;
    lastMovedPiece.setFillColor(sf::Color::Transparent);
    lastMovedPiece.setSize(sf::Vector2f(global::squareSize - (outlineThickness * 2), global::squareSize - (outlineThickness * 2)));
    lastMovedPiece.setPosition(sf::Vector2f((positionOfMostRecentMove[1] * global::squareSize) + outlineThickness, (positionOfMostRecentMove[0] * global::squareSize) + outlineThickness));
    lastMovedPiece.setOutlineThickness(outlineThickness);
    lastMovedPiece.setOutlineColor(sf::Color(255, 215, 0, 255));
    window.draw(lastMovedPiece);
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
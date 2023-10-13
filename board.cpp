#include "board.h"

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
void Board::setpositionOfLastMovedWhitePiece(int x, int y)
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
void Board::setpositionOfLastMovedBlackPiece(int x, int y)
{
    positionOfLastMovedBlackPiece[0] = x;
    positionOfLastMovedBlackPiece[1] = y;
}

// Return a pointer to the position of the last moved black piece
std::vector<int> *Board::getpositionOfLastMovedBlackPiece()
{
    return &positionOfLastMovedBlackPiece;
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
        else if (*boardPtr[x][y]->getPieceColor() == pieceColor::WHITE)
        {
            if (*boardPtr[x - 1][y]->getPieceType() == pieceType::PAWN)
            {
                if (!simulate)
                {
                    erasePiece(boardPtr, x - 1, y);
                }
                clearPiece(boardPtr, x - 1, y);
            }
        }
    }
}

// Move piece
void Board::movePiece(Piece *boardPtr[8][8], int overWriteX, int overWriteY, int overWrittenX, int overWrittenY, bool simulate)
{

    // If the square a piece is moving too is empty, swap the two pointers
    if (*boardPtr[overWrittenX][overWrittenY]->getPieceType() == pieceType::NONE)
    {

        swapPieces(boardPtr, overWriteX, overWriteY, overWrittenX, overWrittenY);
        // checkForPassant(boardPtr, overWrittenX, overWrittenY, simulate);
    }
    // Else if the square has another piece on it, destory the piece and deconstruct its data
    else
    {

        takePiece(boardPtr, overWriteX, overWriteY, overWrittenX, overWrittenY, simulate);
    }

    // Set the position of the last moved piece to its corresponding color
    if (!simulate)
    {
        // Set hasMoved to be true
        if (!*boardPtr[overWrittenX][overWriteY]->getHasMoved())
        {
            boardPtr[overWrittenX][overWrittenY]->setHasMoved();
        }

        // Increase the times the piece has moved by 1
        boardPtr[overWrittenX][overWrittenY]->increamentMoveCounter();

        if (*getCurrentTurn() == playerTurn::WHITE)
        {
            setpositionOfLastMovedWhitePiece(overWrittenX, overWrittenY);
        }
        else
        {
            setpositionOfLastMovedBlackPiece(overWrittenX, overWrittenY);
        }
    }
}

// Move a piece and check if the new position is a valid move
void Board::movePieceWithCheck(Piece *boardPtr[8][8], std::vector<std::vector<int>> *moves, int x, int y)
{
    for (auto move : *moves)
    {
        if (move[0] == x && move[1] == y)
        {
            // Move piece
            movePiece(boardPtr, swapBuffer[0], swapBuffer[1], x, y, false);

            // Switch current turn
            switchTurn();
        }
    }
    // Swap modes
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
                     int overWrittenColor)
{
    swapPieces(boardPtr,
               positionOfOverWriteX,
               positionOfOverWriteY,
               positionOfOverWrittenX,
               positionOfOverWrittenY);

    board[positionOfOverWriteX][positionOfOverWriteY]->setPieceType(overWriteType);
    board[positionOfOverWriteX][positionOfOverWriteY]->setPieceColor(overWriteColor);

    board[positionOfOverWrittenX][positionOfOverWrittenY]->setPieceType(overWrittenType);
    board[positionOfOverWrittenX][positionOfOverWrittenY]->setPieceColor(overWrittenColor);
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

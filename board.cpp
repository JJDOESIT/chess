#include "board.h"
#include <iostream>

void Board::initPieceList()
{
    // White pieces
    Piece white_rook_one(pieceType(ROOK), pieceColor(WHITE), 0, 0, "./sprites/white_rook.png");
    Piece white_knight_one(pieceType(KNIGHT), pieceColor(WHITE), 0, 1, "./sprites/white_knight.png");
    Piece white_bishop_one(pieceType(BISHOP), pieceColor(WHITE), 0, 2, "./sprites/white_bishop.png");
    Piece white_bishop_two(pieceType(BISHOP), pieceColor(WHITE), 0, 5, "./sprites/white_bishop.png");
    Piece white_knight_two(pieceType(KNIGHT), pieceColor(WHITE), 0, 6, "./sprites/white_knight.png");
    Piece white_rook_two(pieceType(ROOK), pieceColor(WHITE), 0, 7, "./sprites/white_rook.png");
    Piece white_queen(pieceType(QUEEN), pieceColor(WHITE), 0, 3, "./sprites/white_queen.png");
    Piece white_king(pieceType(KING), pieceColor(WHITE), 0, 4, "./sprites/white_king.png");

    Piece white_pawn_one(pieceType(PAWN), pieceColor(WHITE), 1, 0, "./sprites/white_pawn.png");
    Piece white_pawn_two(pieceType(PAWN), pieceColor(WHITE), 1, 1, "./sprites/white_pawn.png");
    Piece white_pawn_three(pieceType(PAWN), pieceColor(WHITE), 1, 2, "./sprites/white_pawn.png");
    Piece white_pawn_four(pieceType(PAWN), pieceColor(WHITE), 1, 3, "./sprites/white_pawn.png");
    Piece white_pawn_five(pieceType(PAWN), pieceColor(WHITE), 1, 4, "./sprites/white_pawn.png");
    Piece white_pawn_six(pieceType(PAWN), pieceColor(WHITE), 1, 5, "./sprites/white_pawn.png");
    Piece white_pawn_seven(pieceType(PAWN), pieceColor(WHITE), 1, 6, "./sprites/white_pawn.png");
    Piece white_pawn_eight(pieceType(PAWN), pieceColor(WHITE), 1, 7, "./sprites/white_pawn.png");

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

    for (int row = 2; row < 6; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            pieceList.push_back(Piece(pieceType(NONE), pieceColor(NEITHER), row, col));
        }
    }

    for (int col = 0; col < BOARD_SIZE; col++)
    {
        pieceList.push_back(Piece(pieceType(PAWN), pieceColor(BLACK), BOARD_SIZE - 2, col));
    }

    // Black pieces
    Piece black_rook_one(pieceType(ROOK), pieceColor(BLACK), 7, 0, "./sprites/black_rook.png");
    Piece black_knight_one(pieceType(KNIGHT), pieceColor(BLACK), 7, 1, "./sprites/black_knight.png");
    Piece black_bishop_one(pieceType(BISHOP), pieceColor(BLACK), 7, 2, "./sprites/black_bishop.png");
    Piece black_bishop_two(pieceType(BISHOP), pieceColor(BLACK), 7, 5, "./sprites/black_bishop.png");
    Piece black_knight_two(pieceType(KNIGHT), pieceColor(BLACK), 7, 6, "./sprites/black_knight.png");
    Piece black_rook_two(pieceType(ROOK), pieceColor(BLACK), 7, 7, "./sprites/black_rook.png");
    Piece black_queen(pieceType(QUEEN), pieceColor(BLACK), 7, 3, "./sprites/black_queen.png");
    Piece black_king(pieceType(KING), pieceColor(BLACK), 7, 4, "./sprites/black_king.png");

    Piece black_pawn_one(pieceType(PAWN), pieceColor(BLACK), 6, 0, "./sprites/black_pawn.png");
    Piece black_pawn_two(pieceType(PAWN), pieceColor(BLACK), 6, 1, "./sprites/black_pawn.png");
    Piece black_pawn_three(pieceType(PAWN), pieceColor(BLACK), 6, 2, "./sprites/black_pawn.png");
    Piece black_pawn_four(pieceType(PAWN), pieceColor(BLACK), 6, 3, "./sprites/black_pawn.png");
    Piece black_pawn_five(pieceType(PAWN), pieceColor(BLACK), 6, 4, "./sprites/black_pawn.png");
    Piece black_pawn_six(pieceType(PAWN), pieceColor(BLACK), 6, 5, "./sprites/black_pawn.png");
    Piece black_pawn_seven(pieceType(PAWN), pieceColor(BLACK), 6, 6, "./sprites/black_pawn.png");
    Piece black_pawn_eight(pieceType(PAWN), pieceColor(BLACK), 6, 7, "./sprites/black_pawn.png");

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

std::vector<Piece> *Board::getPieceList()
{
    return &pieceList;
}

void Board::printPieceList()
{

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            int *type = board[i][j]->getPieceType();
            std::cout << *type;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Board::fillBoard()
{
    for (int i = 0; i < pieceList.size(); i++)
    {
        int *piecePosition = pieceList[i].getPiecePosition();
        Piece *piecePtr = &pieceList[i];
        board[piecePosition[0]][piecePosition[1]] = piecePtr;
    }
}

void Board::overwritePiece(int type, int color, int x, int y)
{
    overwriteList.push_back(Piece(type, color, x, y));
    Piece *piecePtr = &overwriteList[0];
    board[x][y] = piecePtr;
}

void Board::swapPieces(int x1, int y1, int x2, int y2)
{
    Piece *tempPiecePtr = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = tempPiecePtr;

    int *positionOne = board[x1][y1]->getPiecePosition();
    int *positionTwo = board[x2][y2]->getPiecePosition();

    int tempX = positionOne[0];
    int tempY = positionOne[1];

    board[x1][y1]->setPiecePosition(positionTwo[0], positionTwo[1]);
    board[x2][y2]->setPiecePosition(tempX, tempY);
}

void Board::takePiece(int overwriteX, int overwriteY, int overwrittenX, int overwrittenY)
{
    board[overwrittenX][overwrittenY]->setPieceType(pieceType(NONE));
    board[overwrittenX][overwrittenY]->setPieceColor(pieceColor(NEITHER));
    swapPieces(overwriteX, overwriteY, overwrittenX, overwrittenY);
}
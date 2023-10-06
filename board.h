#include "piece.h"
#include "pieceEnum.h"
#include <vector>
#include <iostream>

#ifndef BOARD
#define BOARD

class Board
{
private:
    std::vector<Piece> pieceList;
    std::vector<Piece> overwriteList;
    std::vector<sf::Texture> textureList;
    const int BOARD_SIZE = 8;

public:
    Piece *board[8][8] = {nullptr};
    void initPieceList();
    std::vector<Piece> *getPieceList();
    void printPieceList();
    void initBoard();
    void fillBoard();
    void overwritePiece(int type, int color, int x, int y);
    void swapPieces(int x1, int y1, int x2, int y2);
    void takePiece(int overwriteX, int overwriteY, int overwrittenX, int overwrittenY);
};

#endif
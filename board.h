#include "piece.h"
#include "globalEnum.h"
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
    std::vector<int> positionOfLastMovedWhitePiece = {-1, -1};
    std::vector<int> positionOfLastMovedBlackPiece = {-1, -1};
    int turn = playerTurn::WHITE;

public:
    int mode = playerMode::NONE;
    int swapBuffer[2];

    Piece *board[8][8] = {nullptr};

    void initPieceList();
    std::vector<Piece> *getPieceList();
    void printBoard();
    void initBoard();
    void fillBoard();
    void overwritePiece(int type, int color, int x, int y);
    void swapPieces(int x1, int y1, int x2, int y2);
    void takePiece(int overwriteX, int overwriteY, int overwrittenX, int overwrittenY);
    void erasePiece(int x, int y);

    void setpositionOfLastMovedWhitePiece(int x, int y);
    std::vector<int> *getpositionOfLastMovedWhitePiece();

    void setpositionOfLastMovedBlackPiece(int x, int y);
    std::vector<int> *getpositionOfLastMovedBlackPiece();

    int *getCurrentTurn();
    void switchTurn();

    void checkForPassant(int x, int y);

    void movePiece(int x, int y);

    void movePieceWithCheck(std::vector<std::vector<int>> *moves, int x, int y);

    void movePieceWithoutCheck(int x, int y);
};

#endif
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
    std::vector<int> positionOfMostRecentMove = {-1, -1};

    struct moveData
    {
        int positionOfOverWriteX;
        int positionOfOverWriteY;
        int positionOfOverWrittenX;
        int positionOfOverWrittenY;

        int overWriteType;
        int overWrittenType;

        int overWriteColor;
        int overWrittenColor;
    } moveHistory;

    int swapBuffer[2];

    int turn = playerTurn::WHITE;

    int mode = playerMode::NONE;

    int totalWhiteMoveCount = 0;

    std::vector<std::vector<int>> checkMovesList;

    bool hasWhiteCastled = false;
    bool hasBlackCastled = false;

    bool isPieceMoving = false;

public:
    Piece *board[8][8] = {nullptr};

    void initPieceList();
    std::vector<Piece> *getPieceList();
    void printBoard(Piece *boardPtr[8][8]);
    void initBoard();
    void fillBoard();
    void overwritePiece(int type, int color, int x, int y);
    void swapPieces(Piece *boardPtr[8][8], int x1, int y1, int x2, int y2);
    void takePiece(Piece *boardPtr[8][8], int overwriteX, int overwriteY, int overwrittenX, int overwrittenY, bool simulate = false);
    void erasePiece(Piece *boardPtr[8][8], int x, int y);
    void clearPiece(Piece *boardPtr[8][8], int x, int y);

    void setPositionOfLastMovedWhitePiece(int x, int y);
    std::vector<int> *getpositionOfLastMovedWhitePiece();

    void setPositionOfLastMovedBlackPiece(int x, int y);
    std::vector<int> *getpositionOfLastMovedBlackPiece();

    void setPositionOfMostRecentPiece(int x, int y);

    int *getCurrentTurn();
    void switchTurn();

    void checkForPassant(Piece *boardPtr[8][8], int x, int y, bool simulate = false);

    void checkPawnPromotion(Piece *boardPtr[8][8], int x, int y);
    void promotePiece(Piece *boardPtr[8][8], int x, int y, int type);

    void castle(Piece *boardPtr[8][8], int overWriteX, int overWriteY, int overWrittenX, int overWrittenY, int &positionDifferential, bool simulat);

    void movePiece(Piece *boardPtr[8][8], int overWriteX, int overWriteY, int overWrittenX, int overWrittenY, bool simulate);

    void movePieceWithCheck(sf::RenderWindow &window, Piece *boardPtr[8][8], std::vector<std::vector<int>> *moves, int x, int y);

    void movePieceWithoutCheck(Piece *boardPtr[8][8], int overWriteX, int overWriteY, int overWrittenX, int overWrittenY, bool simulate = false);

    void copyArray(Piece *copyFrom[8][8], Piece *copyTo[8][8]);

    void deleteArray(Piece *array[8][8]);

    void undoMove(Piece *boardPtr[8][8], int positionOfOverWriteX,
                  int positionOfOverWriteY,
                  int positionOfOverWrittenX,
                  int positionOfOverWrittenY, int overWriteType,
                  int overWrittenType,
                  int overWriteColor,
                  int overWrittenColor,
                  bool isPassant,
                  bool isCastle);

    void drawSprites(sf::RenderWindow &window);
    void drawBoard(sf::RenderWindow &window);
    void drawPossibleMoves(sf::RenderWindow &window, std::vector<std::vector<int>> *moves);

    friend class Input;
    friend class ValidMoves;
    friend class Open;
};

#endif
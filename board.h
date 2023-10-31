#include "piece.h"
#include "globalEnum.h"

#include <vector>
#include <iostream>

#ifndef BOARD
#define BOARD

class Board
{
private:
    Piece *board[8][8] = {nullptr};

    std::vector<Piece> pieceList;
    std::vector<Piece> overwriteList;
    std::vector<sf::Texture> textureList;
    std::vector<int> positionOfLastMovedWhitePiece = {-1, -1};
    std::vector<int> positionOfLastMovedBlackPiece = {-1, -1};
    std::vector<int> positionOfMostRecentMove = {-1, -1};
    std::vector<int> positionOfWhiteKing = {0, 4};
    std::vector<int> positionOfBlackKing = {7, 4};

    struct moveData
    {
        int positionOfAttackingX;
        int positionOfAttackingY;
        int positionOfDefendingX;
        int positionOfDefendingY;

        int attackingType;
        int defendingType;

        int attackingColor;
        int defendingColor;
    } moveHistory;

    int swapBuffer[2];

    int turn = playerTurn::WHITE;

    int mode = playerMode::NONE;

    int totalWhiteMoveCount = 0;

    std::vector<std::vector<int>> checkMovesList;

    bool hasWhiteCastled = false;
    bool hasBlackCastled = false;

    bool isPieceMoving = false;

    bool isPlayerInCheck = false;
    std::vector<std::vector<int>> displayCheckList;

public:
    void initilizeBoard();
    void overwritePiece(int type, int color, int x, int y);
    void swapPieces(Piece *boardPtr[8][8], int x1, int y1, int x2, int y2);
    void takePiece(Piece *boardPtr[8][8], int attackingX, int attackingY, int defendingX, int defendingY, bool simulate = false);
    void erasePiece(Piece *boardPtr[8][8], int x, int y);
    void clearPiece(Piece *boardPtr[8][8], int x, int y);

    void setIsPlayerInCheck(bool check);
    bool getIsPlayerInCheck();

    void addPieceToDisplayCheckList(int x, int y);

    void setPositionOfLastMovedWhitePiece(int x, int y);
    std::vector<int> *getpositionOfLastMovedWhitePiece();

    void setPositionOfLastMovedBlackPiece(int x, int y);
    std::vector<int> *getpositionOfLastMovedBlackPiece();

    void setPositionOfMostRecentPiece(int x, int y);

    int *getCurrentTurn();
    void switchTurn();

    void checkForPassant(Piece *boardPtr[8][8], int x, int y, bool simulate = false);

    void checkPawnPromotion(Piece *boardPtr[8][8], int x, int y, bool simulate);
    void promotePiece(Piece *boardPtr[8][8], int x, int y, int type, bool simulate);

    void castle(Piece *boardPtr[8][8], int attackingX, int attackingY, int defendingX, int defendingY, int &positionDifferential, bool simulat);

    void movePiece(Piece *boardPtr[8][8], int attackingX, int attackingY, int defendingX, int defendingY, bool simulate);

    bool movePieceWithCheck(sf::RenderWindow &window, Piece *boardPtr[8][8], std::vector<std::vector<int>> *moves, int x, int y);

    void undoMove(Piece *boardPtr[8][8], int positionOfAttackingX,
                  int positionOfAttackingY,
                  int positionOfDefendingX,
                  int positionOfDefendingY, int attackingType,
                  int defendingType,
                  int attackingColor,
                  int defendingColor,
                  bool isPassant,
                  bool isCastle,
                  bool isPromotion);

    void drawSprites(sf::RenderWindow &window);
    void drawBoard(sf::RenderWindow &window);
    void drawPossibleMoves(sf::RenderWindow &window, std::vector<std::vector<int>> *moves);
    void drawBorder(sf::RenderWindow &window, int x, int y, int r, int g, int b, int outlineThickness);

    friend class Input;
    friend class ValidMoves;
    friend class Open;
    friend class AI;
};

#endif
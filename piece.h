#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#ifndef PIECE
#define PIECE

class Piece
{
private:
    struct pieceData
    {
        int type;
        int color;
        int position[2];
        float positionBuffer[2];
        std::vector<std::vector<int>> validMoves;
        sf::Sprite sprite;
        sf::Texture *texture;
        int moveCounter = 0;
    };

    pieceData pieceInfo;

public:
    Piece(int type, int color, int x, int y, std::string fileName = "");
    int *getPieceType();
    void setPieceType(int type);

    int *getPieceColor();
    void setPieceColor(int color);

    int *getPiecePosition();
    void setPiecePosition(int x, int y);

    float *getPiecePositionBuffer();
    void setPiecePositionBuffer(int x, int y);

    int *getMoveCounter();
    void increamentMoveCounter();
    void decreamentMoveCounter();

    std::vector<std::vector<int>> *getValidMoves();
    void printValidMoves();

    sf::Sprite *getSprite();

    void setTexture(std::string fileName);
    void deleteTexture();

    void addMove(int x, int y);
};

#endif
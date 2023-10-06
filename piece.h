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
        std::vector<std::vector<int>> validMoves;
        sf::Sprite sprite;
        sf::Texture *texture;
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
    std::vector<std::vector<int>> *getValidMoves();
    void setSprite(std::string fileName);
    sf::Sprite *getSprite();
    void addMove(int x, int y);
};

#endif
#include "piece.h"

Piece::Piece(int type, int color, int x, int y, std::string fileName)
{
    pieceInfo.type = type;
    pieceInfo.color = color;
    pieceInfo.position[0] = x;
    pieceInfo.position[1] = y;

    if (fileName != "")
    {
        pieceInfo.texture = new sf::Texture;
        pieceInfo.texture->loadFromFile(fileName);
        // std::cout << &pieceInfo.texture << "\n";
        pieceInfo.sprite.setTexture(*pieceInfo.texture);
        // std::cout << pieceInfo.sprite.getTexture() << "\n";
    }
}

int *Piece::getPieceType()
{
    return &pieceInfo.type;
}

void Piece::setPieceType(int type)
{
    pieceInfo.type = type;
}

int *Piece::getPieceColor()
{
    return &pieceInfo.color;
}

void Piece::setPieceColor(int color)
{
    pieceInfo.color = color;
}

int *Piece::getPiecePosition()
{
    return pieceInfo.position;
}

void Piece::setPiecePosition(int x, int y)
{
    pieceInfo.position[0] = x;
    pieceInfo.position[1] = y;
}

std::vector<std::vector<int>> *Piece::getValidMoves()
{
    return &pieceInfo.validMoves;
}

sf::Sprite *Piece::getSprite()
{
    return &pieceInfo.sprite;
}

void Piece::addMove(int x, int y)
{
    std::vector<int> move = {x, y};
    pieceInfo.validMoves.push_back(move);
}
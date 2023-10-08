#include "piece.h"

// Construct Piece
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
        pieceInfo.sprite.setTexture(*pieceInfo.texture);
    }
}

// Return a pointer to piece type
int *Piece::getPieceType()
{
    return &pieceInfo.type;
}

// Set the piece type
void Piece::setPieceType(int type)
{
    pieceInfo.type = type;
}

// Return a pointer to piece color
int *Piece::getPieceColor()
{
    return &pieceInfo.color;
}

// Set piece color
void Piece::setPieceColor(int color)
{
    pieceInfo.color = color;
}

// Return a pointer to piece position
int *Piece::getPiecePosition()
{
    return pieceInfo.position;
}

// Set piece position with given x and y values
void Piece::setPiecePosition(int x, int y)
{
    pieceInfo.position[0] = x;
    pieceInfo.position[1] = y;
}

// Return a pointer to hasMoved variable
bool *Piece::getHasMoved()
{
    return &pieceInfo.hasMoved;
}

// Set hasMoved variable to true
void Piece::setHasMoved()
{
    pieceInfo.hasMoved = true;
}

// Return a pointer to the moveCounter
int *Piece::getMoveCounter()
{
    return &pieceInfo.moveCounter;
}

// Increament moveCounter by 1
void Piece::increamentMoveCounter()
{
    pieceInfo.moveCounter += 1;
}

// Return a pointer to the list of valid moves a piece can make
std::vector<std::vector<int>> *Piece::getValidMoves()
{
    return &pieceInfo.validMoves;
}

void Piece::printValidMoves()
{
    std::cout << "Position: " << pieceInfo.position[0] << ", " << pieceInfo.position[1] << "| ";
    for (auto move : pieceInfo.validMoves)
    {
        std::cout << "(" << move[0] << ", " << move[1] << ")"
                  << ", ";
    }
}

// Return a pointer to a sprite
sf::Sprite *Piece::getSprite()
{
    return &pieceInfo.sprite;
}

// Delete a texture off the heap
void Piece::deleteTexture()
{
    delete pieceInfo.texture;
}

// Add a move to the list of valid moves
void Piece::addMove(int x, int y)
{
    std::vector<int> move = {x, y};
    pieceInfo.validMoves.push_back(move);
}
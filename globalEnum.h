#ifndef GLOBALENUM
#define GLOBALENUM

namespace pieceType
{
    enum pieceType
    {
        PAWN,
        ROOK,
        BISHOP,
        KNIGHT,
        QUEEN,
        KING,
        NONE
    };
}

namespace pieceColor
{
    enum pieceColor
    {
        WHITE,
        BLACK,
        NONE
    };
}

namespace playerMode
{
    enum playerMode
    {
        VIEW,
        TAKE,
        NONE
    };
}

namespace playerTurn
{
    enum playerTurn
    {
        WHITE,
        BLACK
    };
}

#endif
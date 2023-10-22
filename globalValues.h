#ifndef GLOBALVALUES
#define GLOBALVALUES

namespace global
{
    inline int depth = 2;

    inline int squareSize = 68;

    inline int pawnValue = 100;
    inline int knightValue = 320;
    inline int bishopValue = 330;
    inline int rookValue = 500;
    inline int queenValue = 900;

    inline void changeDepth(int number)
    {
        depth = number;
    }
}

#endif
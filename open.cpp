#include "open.h"
#include "pieceMobilityMatrices.h"

std::vector<int> Open::randomOpening(Board *board, Piece *boardPtr[8][8], int randomNumber)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::vector<int> matrixData;

    switch (randomNumber)
    {
    case 1:
        matrixData = royLopez(board, boardPtr);
        break;
    case 2:
        matrixData = italian(board, boardPtr);
        break;
    case 3:
        matrixData = scotchGame(board, boardPtr);
        break;
    case 4:
        matrixData = londonSystem(board, boardPtr);
        break;
    default:
        break;
    }
    return matrixData;
}

void Open::addMove(int pieceType, int row, int col, int value, bool continueOpening, std::vector<int> &matrixData)
{
    matrixData[0] = pieceType;
    matrixData[1] = row;
    matrixData[2] = col;
    matrixData[3] = value;
    matrixData[4] = continueOpening;

    switch (pieceType)
    {
    case (pieceType::PAWN):
        matrices::whitePawnMatrix[row][col] = skewValue;
        break;
    case (pieceType::ROOK):
        matrices::whiteRookMatrix[row][col] = skewValue;
        break;
    case (pieceType::BISHOP):
        matrices::whiteBishopMatrix[row][col] = skewValue;
        break;
    case (pieceType::KNIGHT):
        matrices::knightMatrix[row][col] = skewValue;
        break;
    case (pieceType::QUEEN):
        matrices::whiteQueenMatrix[row][col] = skewValue;
        break;
    case (pieceType::KING):
        matrices::whiteKingMatrix[row][col] = skewValue;
        break;
    }
}

// Roy Lopez opening
std::vector<int> Open::royLopez(Board *board, Piece *boardPtr[8][8])
{
    // {type, row, col, value, continue (true or false)}
    std::vector<int> matrixData = {-1, -1, -1, -1, -1};

    switch (board->totalWhiteMoveCount)
    {
    case 0:
        addMove(pieceType::PAWN, 3, 4, matrices::whitePawnMatrix[3][4], true, matrixData);
        break;
    case 1:
        addMove(pieceType::KNIGHT, 2, 5, matrices::knightMatrix[2][5], true, matrixData);
        break;
    case 2:
        addMove(pieceType::BISHOP, 4, 1, matrices::whiteBishopMatrix[4][1], false, matrixData);
        break;

    default:
        break;
    }
    return matrixData;
}

// Roy Lopez opening
std::vector<int> Open::italian(Board *board, Piece *boardPtr[8][8])
{
    // {type, row, col, value, continue (true or false)}
    std::vector<int> matrixData = {-1, -1, -1, -1, -1};

    switch (board->totalWhiteMoveCount)
    {
    case 0:
        addMove(pieceType::PAWN, 3, 4, matrices::whitePawnMatrix[3][4], true, matrixData);
        break;
    case 1:
        addMove(pieceType::KNIGHT, 2, 5, matrices::knightMatrix[2][5], true, matrixData);
        break;
    case 2:
        addMove(pieceType::BISHOP, 3, 2, matrices::whiteBishopMatrix[3][2], false, matrixData);
        break;

    default:
        break;
    }
    return matrixData;
}

// Scotch Game opening
std::vector<int> Open::scotchGame(Board *board, Piece *boardPtr[8][8])
{
    // {type, row, col, value, continue (true or false)}
    std::vector<int> matrixData = {-1, -1, -1, -1, -1};

    switch (board->totalWhiteMoveCount)
    {
    case 0:
        addMove(pieceType::PAWN, 3, 4, matrices::whitePawnMatrix[3][4], true, matrixData);
        break;
    case 1:
        addMove(pieceType::PAWN, 3, 3, matrices::whitePawnMatrix[3][3], true, matrixData);
        break;
    case 2:
        addMove(pieceType::KNIGHT, 2, 5, matrices::knightMatrix[2][5], false, matrixData);
        break;
    default:
        break;
    }
    return matrixData;
}

// London System opening
std::vector<int> Open::londonSystem(Board *board, Piece *boardPtr[8][8])
{
    // {type, row, col, value, continue (true or false)}
    std::vector<int> matrixData = {-1, -1, -1, -1, -1};

    switch (board->totalWhiteMoveCount)
    {
    case 0:
        addMove(pieceType::PAWN, 3, 3, matrices::whitePawnMatrix[3][3], true, matrixData);
        break;
    case 1:
        addMove(pieceType::BISHOP, 3, 5, matrices::whiteBishopMatrix[3][5], true, matrixData);
        break;
    case 2:
        addMove(pieceType::KNIGHT, 2, 2, matrices::knightMatrix[2][2], false, matrixData);
        break;
    default:
        break;
    }
    return matrixData;
}
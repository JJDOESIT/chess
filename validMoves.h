#include "piece.h"
#include "board.h"
#include <iostream>
#include <vector>
#include <string>

#ifndef VALIDMOVES
#define VALIDMOVES

class ValidMoves
{
public:
    bool checkBoundary(int x, int y);
    void getValidMoves(Board *board,
                       Piece *boardPtr[8][8],
                       int x,
                       int y,
                       std::vector<std::vector<int>> &checkMoves,
                       bool &isInCheck,
                       std::vector<std::vector<int>> *moves = NULL,
                       std::vector<std::vector<std::vector<int>>> *allPossibleMoves = NULL);

    void compareTwoMovesLists(Piece *boardPtr[8][8], int x, int y, std::vector<std::vector<int>> moveListOne, std::vector<std::vector<int>> moveListTwo);
    void printValidMoves(Piece *board[8][8], int x, int y);

    void getPawn(Board *board, Piece *boardPtr[8][8], int x, int y);
    void getRook(Board *board, Piece *boardPtr[8][8], int x, int y);
    void getKnight(Board *board, Piece *boarPtrd[8][8], int x, int y);
    void getBishop(Board *board, Piece *boardPtr[8][8], int x, int y);
    void getKing(Piece *boardPtr[8][8], int x, int y);
    void getQueen(Board *board, Piece *boardPtr[8][8], int x, int y);

    void calculateLinearMoves(Board *board, Piece *boardPtr[8][8], std::vector<std::vector<int>> possibleMoves, int x, int y);
    void calculateSingleMoves(Piece *board[8][8], std::vector<std::vector<int>> possibleMoves, int x, int y);

    // Functions for calculating check
    void isKingInCheck(Piece *boardPtr[8][8], int kingX, int kingY, int kingColor, std::vector<std::vector<int>> &checkMoves, bool &isInCheck);
    void detectCheckFromPawn(Piece *boardPtr[8][8], int kingX, int kingY, int kingColor, std::vector<std::vector<int>> &checkMoves);
    void detectCheckFromLinearPieces(Piece *board[8][8],
                                     std::vector<std::vector<int>> possibleMoves,
                                     int kingX, int kingY, int kingColor, int type,
                                     std::vector<std::vector<int>> &finalXRayPath);
    void detectCheckFromSingularPieces(Piece *boardPtr[8][8], std::vector<std::vector<int>> possibleMoves, int kingX, int kingY, int kingColor, int type, std::vector<std::vector<int>> &checkMoves);

    // Functions for calculating pinned pieces and their possible moves
    void detectPinnedPieces(Piece *boardPtr[8][8], int color, int x, int y);
    void linearPiecePin(Piece *boardPtr[8][8], std::vector<std::vector<int>> possibleMoves, int pinnerX, int pinnerY, int pinnedPieceX, int pinnedPieceY);
};

#endif

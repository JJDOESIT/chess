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
    void getValidMoves(Board *board, Piece *boardPtr[8][8], int x, int y, std::vector<std::vector<int>> *moves = NULL, std::vector<std::vector<std::vector<int>>> *allPossibleMoves = NULL);
    void printValidMoves(Piece *board[8][8], int x, int y);
    void getPawn(Board *board, Piece *boardPtr[8][8], int x, int y);
    void getRook(Piece *board[8][8], int x, int y);
    void getKnight(Piece *board[8][8], int x, int y);
    void getBishop(Piece *board[8][8], int x, int y);
    void getKing(Piece *board[8][8], int x, int y);
    void getQueen(Piece *board[8][8], int x, int y);

    void calculateLinearMoves(Piece *board[8][8], std::vector<std::vector<int>> possibleMoves, int x, int y);
    void calculateSingleMoves(Piece *board[8][8], std::vector<std::vector<int>> possibleMoves, int x, int y);

    // Functions for calculating check
    void isKingInCheck(Piece *board[8][8]);
    void checkLinearMoves(Piece *board[8][8], std::vector<std::vector<int>> possibleMoves, int x, int y, int type);
};

#endif

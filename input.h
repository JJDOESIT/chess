#include "ai.h"
#include "open.h"
#include "time.h"

#include <cstdlib>

#ifndef INPUT
#define INPUT

class Input
{
private:
    Open openingMoves;
    bool isOpening = true;
    int openingSet;

    bool check = false;
    std::vector<std::vector<int>> checkMoves;

public:
    void whileOpen(sf::RenderWindow &window, sf::Event &events, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> *moves, AI *ai);
    void getPossibleMoves(sf::RenderWindow &window,
                          Board *board,
                          ValidMoves *checkValidMoves,
                          std::vector<std::vector<int>> *moves,
                          std::vector<std::vector<int>> checkMoves,
                          bool check);
    void getMousePosition(sf::RenderWindow &window, int &x, int &y);

    void isKingInCheck(Board *board, ValidMoves *checkValidMoves);

    std::vector<int> handleOpeningMove(Board *board);
    void cleanUpOpening(std::vector<int> matrixData);

    void addCheckPositions(Board *board);

    int randomInt(int start, int end);
};
#endif
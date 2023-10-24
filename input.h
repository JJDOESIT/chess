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

public:
    void whileOpen(sf::RenderWindow &window, sf::Event &events, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> *moves, AI *ai);
    void getPossibleMoves(sf::RenderWindow &window,
                          Board *board,
                          ValidMoves *checkValidMoves,
                          std::vector<std::vector<int>> *moves,
                          std::vector<std::vector<int>> checkMoves,
                          bool check);
    void getMousePosition(sf::RenderWindow &window, int &x, int &y);

    std::vector<int> handleOpeningMove(Board *board);
    int randomInt(int start, int end);
};
#endif
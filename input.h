#include <SFML/Graphics.hpp>
#include "board.h"
#include "validMoves.h"
#include "globalEnum.h"
#include "ai.h"

#ifndef INPUT
#define INPUT
class Input
{
private:
public:
    void whileOpen(sf::RenderWindow &window, sf::Event &events, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> *moves, AI *ai);
    void getPossibleMoves(sf::RenderWindow &window,
                          Board *board,
                          ValidMoves *checkValidMoves,
                          std::vector<std::vector<int>> *moves,
                          std::vector<std::vector<int>> checkMoves,
                          bool check);
    void getMousePosition(sf::RenderWindow &window, int &x, int &y);
};
#endif
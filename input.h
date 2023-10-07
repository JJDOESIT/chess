#include <SFML/Graphics.hpp>
#include "board.h"
#include "validMoves.h"
#include "pieceEnum.h"

#ifndef INPUT
#define INPUT
class Input
{
private:
    int turn = playerMode(NADA);
    int swapBuffer[2];

public:
    void whileOpen(sf::RenderWindow &window, sf::Event &events, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> &moves);
    void getPossibleMoves(sf::RenderWindow &window, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> &moves);
    void getMousePosition(sf::RenderWindow &window, int &x, int &y);
    void movePiece(sf::RenderWindow &window, Board *board, std::vector<std::vector<int>> &moves);
};
#endif
#include "piece.h"
#include "input.h"
#include "validMoves.h"
#include "board.h"
#include "ai.h"

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    Board board;
    ValidMoves checkValidMoves;
    Input input;
    AI ai;

    board.initilizeBoard();
    std::vector<std::vector<int>> moves;

    sf::RenderWindow window(sf::VideoMode(544, 544), "Chess");

    while (window.isOpen())
    {
        sf::Event events;
        input.whileOpen(window, events, &board, &checkValidMoves, &moves, &ai);

        window.clear();

        board.drawBoard(window);

        board.drawSprites(window);

        board.drawPossibleMoves(window, &moves);

        window.display();
    }
    return 0;
}
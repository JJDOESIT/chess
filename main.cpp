#include "piece.h"
#include "input.h"
#include "validMoves.h"
#include "board.h"
#include "ai.h"
#include "globalValues.h"

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

    sf::RenderWindow window(sf::VideoMode(global::windowSize, global::windowSize), "Chess", sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen())
    {
        sf::Event events;
        input.whileOpen(window, events, &board, &checkValidMoves, &moves, &ai);

        window.clear();

        board.drawBoard(window);

        board.drawSprites(window);

        board.drawPossibleMoves(window, &moves);

        if (*board.getCheckmate())
        {
            board.drawText(window, "Checkmate", (global::windowSize / 2) - 125, (global::windowSize / 2) - 70);
        }

        window.display();
    }
    return 0;
}
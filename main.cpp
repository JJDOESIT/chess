#include "board.h"
#include <vector>
#include "piece.h"
#include "validMoves.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    Board board;
    ValidMoves checkValidMoves;
    board.initPieceList();
    board.fillBoard();
    board.printPieceList();

    sf::RenderWindow window(sf::VideoMode(544, 544), "Chess");
    while (window.isOpen())
    {
        sf::Event events;
        while (window.pollEvent(events))
        {
            if (events.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(68, 68));
                rect.setPosition(sf::Vector2f(i * 68, j * 68));
                if ((i + j) % 2 == 0)
                {
                    rect.setFillColor(sf::Color(230, 230, 230));
                }
                else
                {
                    rect.setFillColor(sf::Color(30, 30, 30));
                }

                window.draw(rect);
            }
        }

        for (int row = 0; row < 8; row++)
        {
            for (int col = 0; col < 8; col++)
            {
                sf::Sprite sprite = *board.board[row][col]->getSprite();
                int *position = board.board[row][col]->getPiecePosition();
                sprite.setPosition(sf::Vector2f(position[1] * 68, position[0] * 68));
                window.draw(sprite);
            }
        }

        window.display();
    }
    return 0;
}
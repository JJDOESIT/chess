#include "board.h"
#include <vector>
#include "piece.h"
#include "input.h"
#include "validMoves.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    Board board;
    board.initPieceList();
    board.fillBoard();
    board.printPieceList();

    ValidMoves checkValidMoves;
    Input input;

    std::vector<std::vector<int>> moves;
    sf::RenderWindow window(sf::VideoMode(544, 544), "Chess");

    while (window.isOpen())
    {
        sf::Event events;
        input.whileOpen(window, events, &board, &checkValidMoves, moves);

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
                if (*board.board[row][col]->getPieceType() != pieceType(NONE))
                {
                    sf::Sprite sprite = *board.board[row][col]->getSprite();
                    int *position = board.board[row][col]->getPiecePosition();
                    sprite.setPosition(sf::Vector2f(position[1] * 68, position[0] * 68));
                    window.draw(sprite);
                }
            }
        }

        for (auto i : moves)
        {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(68, 68));
            rect.setPosition(i[1] * 68, i[0] * 68);
            rect.setFillColor(sf::Color(255, 0, 0, 100));
            window.draw(rect);
        }

        window.display();
    }
    return 0;
}
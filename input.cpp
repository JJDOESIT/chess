#include "input.h"

void Input::whileOpen(sf::RenderWindow &window, sf::Event &events, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> &moves)
{
    while (window.pollEvent(events))
    {
        if (events.type == sf::Event::Closed)
            window.close();

        if (events.type == sf::Event::MouseButtonReleased)
        {
            if (turn == playerTurn(NADA))
            {
                displayValidMoves(window, board, checkValidMoves, moves);
            }
            else if (turn == playerTurn(VIEW))
            {
                swapTwoPieces(window, board, moves);
            }
        }
    }
}

void Input::getMousePosition(sf::RenderWindow &window, int &x, int &y)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    int x_remainder = mousePosition.x % 68;
    int y_remainder = mousePosition.y % 68;
    x = (mousePosition.x - x_remainder) / 68;
    y = (mousePosition.y - y_remainder) / 68;
}

void Input::displayValidMoves(sf::RenderWindow &window, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> &moves)
{
    int x, y;
    getMousePosition(window, x, y);

    if (*board->board[y][x]->getPieceType() == pieceType(ROOK))
    {
        checkValidMoves->getRook(board->board, y, x);
        swapBuffer[0] = y;
        swapBuffer[1] = x;
    }
    else if (*board->board[y][x]->getPieceType() == pieceType(PAWN))
    {
        checkValidMoves->getPawn(board->board, y, x);
        swapBuffer[0] = y;
        swapBuffer[1] = x;
    }
    moves = *board->board[y][x]->getValidMoves();
    turn = playerTurn(VIEW);
}

void Input::swapTwoPieces(sf::RenderWindow &window, Board *board, std::vector<std::vector<int>> &moves)
{
    int x, y;
    getMousePosition(window, x, y);
    for (auto move : moves)
    {
        if (move[1] == x && move[0] == y)
        {
            if (*board->board[y][x]->getPieceType() == pieceType(NONE))
            {
                std::cout << "SWAP" << std::endl;
                board->swapPieces(swapBuffer[0], swapBuffer[1], y, x);
            }
            else
            {
                std::cout << "TAKE" << std::endl;
                board->takePiece(swapBuffer[0], swapBuffer[1], y, x);
            }
        }
    }
    turn = playerTurn(NADA);
    moves.clear();
}

#include "input.h"

// While the window is open, check for these events
void Input::whileOpen(sf::RenderWindow &window, sf::Event &events, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> *moves, AI *ai)
{
    while (window.pollEvent(events))
    {
        if (events.type == sf::Event::Closed)
            window.close();

        if (events.type == sf::Event::MouseButtonReleased)
        {
            if (board->mode == playerMode::NONE)
            {
                getPossibleMoves(window, board, checkValidMoves, moves);
            }
            else if (board->mode == playerMode::VIEW)
            {
                int x, y;
                getMousePosition(window, y, x);
                board->movePieceWithCheck(board->board, moves, x, y);
            }
        }
    }

    if (*board->getCurrentTurn() == playerTurn::WHITE)
    {
        std::vector<int> move = ai->calculateBestMove(board, board->board, checkValidMoves, 3);
        if (move[0] != -1 && move[1] != -1 && move[2] != -1 && move[3] != -1)
        {
            std::cout << move[0] << ", " << move[1] << std::endl;
            board->movePieceWithoutCheck(board->board, move[0], move[1], move[2], move[3]);
        }
        board->switchTurn();
    }
}

// Get the mouse position relative to the window size
void Input::getMousePosition(sf::RenderWindow &window, int &x, int &y)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    int x_remainder = mousePosition.x % 68;
    int y_remainder = mousePosition.y % 68;
    x = (mousePosition.x - x_remainder) / 68;
    y = (mousePosition.y - y_remainder) / 68;
}

// When a sqaure is clicked, if there is a piece on that tile, get its possible moves
void Input::getPossibleMoves(sf::RenderWindow &window, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> *moves)
{
    int x, y;
    getMousePosition(window, y, x);

    int type = *board->board[x][y]->getPieceType();
    int color = *board->board[x][y]->getPieceColor();

    int colorMustMatch;

    if (*board->getCurrentTurn() == playerTurn::WHITE)
    {
        colorMustMatch = pieceColor::WHITE;
    }
    else
    {
        colorMustMatch = pieceColor::BLACK;
    }

    if (color == colorMustMatch)
    {
        if (type != pieceType::NONE)
        {
            checkValidMoves->getValidMoves(board, board->board, x, y, moves);
        }
    }
}

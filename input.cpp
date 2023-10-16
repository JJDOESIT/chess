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
                bool check;

                std::vector<std::vector<int>> checkMoves;
                for (int row = 0; row < 8; row++)
                {
                    for (int col = 0; col < 8; col++)
                    {
                        if (*board->board[row][col]->getPieceType() == pieceType::KING && *board->board[row][col]->getPieceColor() == board->turn)
                        {

                            checkValidMoves->isKingInCheck(board->board, row, col, board->turn, checkMoves, check);

                            getPossibleMoves(window, board, checkValidMoves, moves, checkMoves, check);
                        }
                    }
                }
            }
            else if (board->mode == playerMode::VIEW)
            {
                int x, y;
                getMousePosition(window, y, x);
                board->movePieceWithCheck(window, board->board, moves, x, y);
            }
        }
    }

    if (*board->getCurrentTurn() == playerTurn::WHITE)
    {
        /* Piece *copyBoard[8][8];
        board->copyArray(board->board, copyBoard);

        std::vector<int> move = ai->calculateBestMove(board, board->board, checkValidMoves, 4, pieceColor::WHITE, -9999, 9999);
        board->movePieceWithoutCheck(board->board, move[0], move[1], move[2], move[3]);
        board->deleteArray(copyBoard);
        board->switchTurn(); */
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
void Input::getPossibleMoves(sf::RenderWindow &window, Board *board,
                             ValidMoves *checkValidMoves,
                             std::vector<std::vector<int>> *moves,
                             std::vector<std::vector<int>> checkMoves,
                             bool check)
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
            checkValidMoves->getValidMoves(board, board->board, x, y, checkMoves, check, moves, NULL);
        }
    }
}

#include "input.h"

// While the window is open, check for these events
void Input::whileOpen(sf::RenderWindow &window, sf::Event &events, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> *moves, AI *ai)
{
    while (window.pollEvent(events))
    {
        if (events.type == sf::Event::Closed)
            window.close();

        // If the mouse button is clicked
        if (events.type == sf::Event::MouseButtonReleased)
        {
            // If the current mode is none (no moves displayed)
            if (board->mode == playerMode::NONE)
            {
                /* Initilize check (is the current players turn in check) and
                checkMoves (what moves positions must be played in order to escape check)*/
                bool check;
                std::vector<std::vector<int>> checkMoves;

                // Loop through the board to find the kings position
                for (int row = 0; row < 8; row++)
                {
                    for (int col = 0; col < 8; col++)
                    {
                        // If the piece is a king and its color matches the current current player
                        if (*board->board[row][col]->getPieceType() == pieceType::KING && *board->board[row][col]->getPieceColor() == board->turn)
                        {
                            // Check if the king is in check
                            checkValidMoves->isKingInCheck(board->board, row, col, board->turn, checkMoves, check);
                            // Get possible moves for the piece
                            getPossibleMoves(window, board, checkValidMoves, moves, checkMoves, check);
                        }
                    }
                }
            }

            // Possible moves are being displayed
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
        if (!openingMoves.randomOpening(board, board->board, 0))
        {
            Piece *copyBoard[8][8];
            board->copyArray(board->board, copyBoard);
            int count = 0;

            std::vector<int> move = ai->calculateBestMove(board, board->board, checkValidMoves, 4, pieceColor::WHITE, -9999, 9999, count);
            board->movePieceWithoutCheck(board->board, move[0], move[1], move[2], move[3]);
            board->deleteArray(copyBoard);
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

#include "input.h"

// While the window is open, check for these events
void Input::whileOpen(sf::RenderWindow &window, sf::Event &events, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> &moves)
{
    while (window.pollEvent(events))
    {
        if (events.type == sf::Event::Closed)
            window.close();

        if (events.type == sf::Event::MouseButtonReleased)
        {
            if (turn == playerMode(NADA))
            {
                getPossibleMoves(window, board, checkValidMoves, moves);
            }
            else if (turn == playerTurn(VIEW))
            {
                movePiece(window, board, moves);
            }
        }
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
void Input::getPossibleMoves(sf::RenderWindow &window, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> &moves)
{
    int x, y;
    getMousePosition(window, x, y);

    int type = *board->board[y][x]->getPieceType();

    if (type != pieceType(NONE))
    {
        if (type == pieceType(ROOK))
        {
            checkValidMoves->getRook(board->board, y, x);
        }
        else if (type == pieceType(PAWN))
        {
            checkValidMoves->getPawn(board->board, y, x);
        }
        else if (type == pieceType(KING))
        {
            checkValidMoves->getKing(board->board, y, x);
        }
        swapBuffer[0] = y;
        swapBuffer[1] = x;
        moves = *board->board[y][x]->getValidMoves();
        if (moves.size() > 0)
        {
            turn = playerMode(VIEW);
        }
    }
}

// Move a piece
void Input::movePiece(sf::RenderWindow &window, Board *board, std::vector<std::vector<int>> &moves)
{
    int x, y;
    getMousePosition(window, x, y);
    for (auto move : moves)
    {
        if (move[1] == x && move[0] == y)
        {
            // If the square a piece is moving too is empty, swap the two pointers
            if (*board->board[y][x]->getPieceType() == pieceType(NONE))
            {
                board->swapPieces(swapBuffer[0], swapBuffer[1], y, x);
            }
            // Else if the square has another piece on it, destory the piece and deconstruct its data
            else
            {
                board->takePiece(swapBuffer[0], swapBuffer[1], y, x);
            }
        }
    }
    // Swap modes
    turn = playerMode(NADA);
    moves.clear();
}

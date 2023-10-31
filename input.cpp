#include "input.h"
#include "globalValues.h"
#include "pieceMobilityMatrices.h"

// While the window is open, check for these events
void Input::whileOpen(sf::RenderWindow &window, sf::Event &events, Board *board, ValidMoves *checkValidMoves, std::vector<std::vector<int>> *moves, AI *ai)
{
    bool isMoveFinished = false;

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
                // Check if the king is in check
                isKingInCheck(board, checkValidMoves);

                // Get possible moves for the piece
                getPossibleMoves(window, board, checkValidMoves, moves, checkMoves, check);
            }

            // Possible moves are being displayed
            else if (board->mode == playerMode::VIEW)
            {
                int x, y;
                getMousePosition(window, y, x);
                isMoveFinished = board->movePieceWithCheck(window, board->board, moves, x, y);
            }
        }
    }

    // If the current turn is white (AI)
    if (*board->getCurrentTurn() == playerTurn::WHITE)
    {
        // If the no pieces are in the process of moving
        if (!board->isPieceMoving)
        {
            // If the opening set is still being played, skew and get the matrix data
            std::vector<int> matrixData = handleOpeningMove(board);

            // Call minimax function to calculate the best move
            std::vector<int> move = ai->calculateBestMove(board, checkValidMoves, global::depth, pieceColor::WHITE, -9999, 9999);
            board->movePiece(board->board, move[0], move[1], move[2], move[3], false);
            isMoveFinished = true;

            cleanUpOpening(matrixData);
        }
    }

    // Once white or black has moved their piece
    if (isMoveFinished)
    {
        board->switchTurn();

        // Check if the move resulted in check
        isKingInCheck(board, checkValidMoves);
        addCheckPositions(board);
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

    if (color == *board->getCurrentTurn())
    {
        if (type != pieceType::NONE)
        {
            checkValidMoves->getValidMoves(board, board->board, x, y, checkMoves, check, moves, NULL);
        }
    }
}

// Return a random number from the range start to end inclusive
int Input::randomInt(int start, int end)
{
    std::srand(time(NULL));
    return rand() % end + start;
}

// Handle the opening sequence from a soft-coded move set
std::vector<int> Input::handleOpeningMove(Board *board)
{
    // Choose a random opening move set for the AI
    static bool isOpeningSetInitilized = false;
    static int opening;

    std::vector<int> matrixData;

    if (!isOpeningSetInitilized)
    {
        opening = randomInt(1, 4);
        isOpeningSetInitilized = true;
    }

    if (isOpening)
    {
        matrixData = openingMoves.randomOpening(board, board->board, opening);
    }
    return matrixData;
}

// Restore the matrix data
void Input::cleanUpOpening(std::vector<int> matrixData)
{
    if (isOpening)
    {
        if (matrixData[4] != -1)
        {
            matrices::restoreMatrixData(matrixData[0], matrixData[1], matrixData[2], matrixData[3]);
        }
        if (matrixData[4] == 0)
        {
            isOpening = false;
            global::changeDepth(4);
        }
    }
}

// Check if the king is in check
void Input::isKingInCheck(Board *board, ValidMoves *checkValidMoves)
{
    // Check if the king is in check
    if (*board->getCurrentTurn() == playerTurn::WHITE)
    {
        checkValidMoves->isKingInCheck(board->board, board->positionOfWhiteKing[0], board->positionOfWhiteKing[1], *board->getCurrentTurn(), checkMoves, check);
    }
    else
    {
        checkValidMoves->isKingInCheck(board->board, board->positionOfBlackKing[0], board->positionOfBlackKing[1], *board->getCurrentTurn(), checkMoves, check);
    }

    board->setIsPlayerInCheck(check);
}

// Add the positions of pieces who are putting the king in check to the list
void Input::addCheckPositions(Board *board)
{
    board->displayCheckList.clear();

    for (std::vector<int> move : checkMoves)
    {
        if (*board->board[move[0]][move[1]]->getPieceType() != pieceType::NONE)
        {
            board->addPieceToDisplayCheckList(move[0], move[1]);
        }
    }
}

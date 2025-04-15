#include "Bishop.h"

/**
 * Constructor for the Bishop class.
 * Initializes a Bishop Piece with the given location and color.
 * Passes the Piece type ('b') to the base class constructor using the KING_TYPE macro.
 *
 * @param coordinate The initial location of the bishop on the board.
 * @param player The color of the player (WHITE or BLACK).
 */
Bishop::Bishop(location coordinate, color player): Piece(coordinate, player, BISHOP_TYPE) {

}

/**
 * Calculates all valid moves for the bishop according to chess rules.
 * The bishop can move diagonally in all four directions until blocked by another Piece or the board's limit.
 * The method updates the bishop's internal move list accordingly.
 * @param board A map representing the current state of the chessboard.
 *              Keys are locations and values are shared pointers to pieces.
 */
void Bishop::calculateMoves(std::map<location, std::shared_ptr<Piece>> &board) {
    location current = this->getCoordinate();
    int numOfDiagonal =4;
    int dRow[4] = {1, 1, -1, -1};
    int dCol[4] = {1, -1, 1, -1};

    for (int i = 0; i < numOfDiagonal; i++) {
        char row = current.first;
        int col = current.second;

        while (true) {
            row += dRow[i];
            col += dCol[i];

            if (row < LIMIT_ROW.first || row > LIMIT_ROW.second ||
                col < LIMIT_COL.first || col > LIMIT_COL.second)
                break;

            location newLoc(row, col);
            auto it = board.find(newLoc);

            if (it == board.end()) {
                this->addMove(newLoc);
            }
            else {
                if (it->second->getColor() != this->getColor()) {
                    this->addMove(newLoc);
                }
                break;
            }
        }
    }
}

/**
 * Creates a deep copy of the current bishop object.
 * @return A shared pointer to a new bishop with the same state.
 */
std::shared_ptr<Piece> Bishop::clone() const {
    return std::make_shared<Bishop>(*this);
}


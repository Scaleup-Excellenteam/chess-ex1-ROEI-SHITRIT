
#include "King.h"

/**
 * @brief Constructs a King Piece with the given position and color.
 *
 * @param coordinate The initial location of the King on the board.
 * @param player The color of the King (WHITE or BLACK).
 */
King::King(location coordinate, color player): Piece(coordinate, player, KING_TYPE){

}

/**
 * @brief Calculates all possible legal moves for the King.
 *
 * The King can move one square in any direction, as long as the target square
 * is within the bounds of the board and is either empty or contains an opponent's Piece.
 *
 * @param board A reference to the current state of the board, mapping locations to pieces.
 */
void King::calculateMoves(std::map<location, std::shared_ptr<Piece>> &board) {
    location current = this->getCoordinate();
    int dRow[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    int dCol[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < LIMIT_COL.second; i++) {
        char newRow = current.first + dRow[i];
        int newCol = current.second + dCol[i];

        if (newRow < LIMIT_ROW.first || newRow > LIMIT_ROW.second ||
            newCol < LIMIT_COL.first || newCol > LIMIT_COL.second)
            continue;

        location newLoc = location (newRow, newCol);
        auto it = board.find(newLoc);

        if (it == board.end()){
            this->addMove(newLoc);

        }
        else{
            if (it->second->getColor() != this->getColor()) {
                this->addMove(newLoc);
            }
        }

    }
}

/**
 * @brief Creates a deep copy of the King object.
 *
 * @return std::shared_ptr<Piece> A shared pointer to a new King object
 *         with the same properties as this one.
 */
std::shared_ptr<Piece> King::clone() const {
    return std::make_shared<King>(*this);
}


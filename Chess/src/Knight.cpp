
#include "Knight.h"
/**
 * @brief Constructor for the Knight Piece.
 *
 * Initializes the Knight Piece with a given position and color.
 *
 * @param coordinate The position of the Knight on the board.
 * @param player The color of the player (WHITE or BLACK).
 */
Knight::Knight(location coordinate, color player): Piece(coordinate, player, KNIGHT_TYPE) {

}

/**
 * @brief Calculates all possible moves for the Knight Piece.
 *
 * The Knight moves in an "L" shape: two squares in one direction and one square perpendicular,
 * or one square in one direction and two squares perpendicular. This method calculates all valid moves
 * for the Knight on the given chessboard.
 *
 * @param board A map of all pieces on the chessboard.
 */
void Knight::calculateMoves(std::map<location, std::shared_ptr<Piece>> &board) {
    location current = this->getCoordinate();
    int dRow[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dCol[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
    int numOfOption = 8;

    for(int i=0;i<numOfOption;i++){
        char row = current.first + dRow[i];
        int col = current.second + dCol[i];

        if (row < LIMIT_ROW.first || row > LIMIT_ROW.second ||
            col < LIMIT_COL.first || col > LIMIT_COL.second) {
            continue;
        }
        location newLoc(row, col);
        auto it = board.find(newLoc);

        if (it == board.end() ||
            it->second->getColor() != this->getColor()) {
            this->addMove(newLoc);
        }

    }

}

/**
 * @brief Creates a copy of the Knight Piece.
 *
 * @return A shared pointer to a new Knight object.
 */
std::shared_ptr<Piece> Knight::clone() const {
    return std::make_shared<Knight>(*this);
}

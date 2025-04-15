#include "Rook.h"

/**
 * @brief Constructor for the Rook class.
 *
 * Initializes a rook with the given coordinate and color.
 *
 * @param coordinate The initial position of the rook.
 * @param player The color (WHITE or BLACK) of the rook.
 */
Rook::Rook(location coordinate, color player): Piece(coordinate, player, ROOK_TYPE) {

}


/**
 * @brief Calculates all legal moves for the rook.
 *
 * The rook moves in straight lines vertically and horizontally.
 * This function updates the Piece's internal list of legal moves,
 * based on the current state of the board.
 *
 * @param board A map representing the board with locations as keys and shared pointers to pieces as values.
 */
void Rook::calculateMoves(std::map<location, std::shared_ptr<Piece>> &board) {
    bool flag_up = true, flag_down = true, flag_right = true, flag_left = true;

    location current = this->getCoordinate();

    for (int i = 1; i < LIMIT_COL.second; i++) {
        if (flag_up) {
            char row = current.first + i;
            if (row <= LIMIT_ROW.second) {
                location loc(row, current.second);
                auto it = board.find(loc);
                if (it == board.end()) {
                    this->addMove(loc);
                } else {
                    if (it->second->getColor() != this->getColor()) {
                        this->addMove(loc);
                    }
                    flag_up = false;
                }
            } else {
                flag_up = false;
            }
        }


        if (flag_down) {
            char row = current.first - i;
            if (row >= LIMIT_ROW.first) {
                location loc(row, current.second);
                auto it = board.find(loc);
                if (it == board.end()) {
                    this->addMove(loc);
                } else {
                    if (it->second->getColor() != this->getColor()) {
                        this->addMove(loc);
                    }
                    flag_down = false;
                }
            } else {
                flag_down = false;
            }
        }


        if (flag_right) {
            int col = current.second + i;
            if (col <= LIMIT_COL.second) {
                location loc(current.first, col);
                auto it = board.find(loc);
                if (it == board.end()) {
                    this->addMove(loc);
                } else {
                    if (it->second->getColor() != this->getColor()) {
                        this->addMove(loc);
                    }
                    flag_right = false;
                }
            } else {
                flag_right = false;
            }
        }

        if (flag_left) {
            int col = current.second - i;
            if (col >= LIMIT_COL.first) {
                location loc(current.first, col);
                auto it = board.find(loc);
                if (it == board.end()) {
                    this->addMove(loc);
                } else {
                    if (it->second->getColor() != this->getColor()) {
                        this->addMove(loc);
                    }
                    flag_left = false;
                }
            } else {
                flag_left = false;
            }
        }

        if (!flag_up && !flag_down && !flag_right && !flag_left) {
            break;
        }
    }
}

/**
 * @brief Creates a deep copy of the rook.
 *
 * @return std::shared_ptr<Piece> A shared pointer to the cloned rook.
 */
std::shared_ptr<Piece> Rook::clone() const {
    return std::make_shared<Rook>(*this);
}

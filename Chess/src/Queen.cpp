
#include "Queen.h"

/**
 * @brief Constructs a Queen Piece with a given position and color.
 *
 * Initializes the base Piece class and also initializes the Rook and Bishop parts,
 * since Queen inherits from both to reuse their movement capabilities.
 *
 * @param coordinate The position of the Queen on the board.
 * @param player The color of the Queen (WHITE or BLACK).
 */
Queen::Queen(location coordinate, color player): Piece(coordinate, player, QUEEN_TYPE), Rook(coordinate, player), Bishop(coordinate, player) {

}

/**
 * @brief Calculates all valid moves for the Queen based on current board state.
 *
 * The Queen's moves are a combination of Rook and Bishop, so it calls both calculate functions.
 *
 * @param board Reference to the current board state.
 */
void Queen::calculateMoves(std::map<location, std::shared_ptr<Piece>> &board) {
    Rook::calculateMoves(board);
    Bishop::calculateMoves(board);
}

/**
 * @brief Creates a copy of the current Queen object.
 *
 * Used when simulating moves or copying the board state.
 *
 * @return A shared pointer to a newly cloned Queen instance.
 */
std::shared_ptr<Piece> Queen::clone() const {
    return std::make_shared<Queen>(*this);
}


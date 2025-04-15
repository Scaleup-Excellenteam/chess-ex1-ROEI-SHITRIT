#include <utility>
#include "Piece.h"

/**
 * Constructor for the Piece class.
 * Initializes the Piece with its coordinate, color, and tool (type).
 * @param coordinate The initial location of the Piece on the board.
 * @param player The color of the Piece (WHITE or BLACK).
 * @param tool A character representing the type of the Piece (e.g., 'R' for rook).
 */
Piece::Piece(location &coordinate, color player, char tool): _coordinate(coordinate), _player(player), _tool(tool){
    this->_hasMove = false;
    this->_moves = std::vector<location>();
}

/**
 * @return The current coordinate of the Piece on the board.
 */
location Piece::getCoordinate() const {
    return this->_coordinate;
}

/**
 * @return The color of the Piece.
 */
color Piece::getColor() const {
    return this->_player;
}

/**
 * @return The character representing the Piece type.
 */
char Piece::getTool() const {
    return this->_tool;
}

/**
* @return True if the Piece has moved at least once; otherwise, false.
*/
bool Piece::hasMoved() const {
    return this->_hasMove;
}

/**
 * @return A reference to the vector of legal moves for the Piece.
 */
std::vector<location>& Piece::getMoves()  {
    return this->_moves;
}

/**
 * Adds a legal move to the Piece's list of moves.
 * @param move A location representing a valid move.
 */
void Piece::addMove(const location &move) {
    this->_moves.push_back(move);

}

/**
 * Clears the list of legal moves for the Piece.
 */
void Piece::clearMoves() {
    this->_moves.clear();

}

/**
 * Updates the Piece's position on the board.
 * @param coordinateToChange The new coordinate for the Piece.
 */
void Piece::setLocation(location &coordinateToChange) {
    this->_coordinate =coordinateToChange;
}

/**
 * Marks the Piece as having moved.
 */
void Piece::pieceMoved() {
    this->_hasMove = true;
}





#pragma once
#include "ChessBoard.h"
#define ROOK_TYPE 'r'

/**
 * @class Rook
 * @brief Represents a Rook Piece in the game of chess.
 *
 * The Rook can move in straight lines along rows and columns.
 * This class inherits virtually from the base class `Piece`, allowing
 * multiple inheritance with other pieces (e.g., Queen).
 */
class Rook: virtual public Piece{
public:
    Rook(location coordinate,color player);
    void calculateMoves(std::map<location, std::shared_ptr<Piece>> &board) override;
    [[nodiscard]] std::shared_ptr<Piece> clone() const override;


};

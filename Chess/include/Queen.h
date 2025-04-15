#pragma once
#include "Rook.h"
#include "Bishop.h"
#define QUEEN_TYPE 'q'

/**
 * @brief Represents the Queen chess Piece.
 *
 * The Queen combines the movement abilities of both the Rook and the Bishop.
 * It can move any number of squares in a straight line horizontally, vertically, or diagonally.
 * Inherits from both Rook and Bishop classes to reuse their move logic.
 */
class Queen: public Rook,public Bishop{
public:
    Queen(location coordinate,color player);
    void calculateMoves(std::map<location, std::shared_ptr<Piece>> &board) override;
    [[nodiscard]] std::shared_ptr<Piece> clone() const override;

};

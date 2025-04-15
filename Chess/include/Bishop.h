#pragma once
#include "ChessBoard.h"
#define BISHOP_TYPE 'b'

/**
 * Represents a Bishop chess Piece.
 * Inherits from the abstract class Piece.
 * The class implements logic specific to Bishop movement and cloning.
 */
class Bishop: virtual public Piece{
public:
    Bishop(location coordinate,color player);
    void calculateMoves(std::map<location, std::shared_ptr<Piece>> &board) override;
    [[nodiscard]] std::shared_ptr<Piece> clone() const override;



};
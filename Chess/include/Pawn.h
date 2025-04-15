#pragma once
#include "ChessBoard.h"
#define PAWN_TYPE 'p'
/**
 * @class Pawn
 * @brief Represents a pawn chess Piece.
 *
 * Implements pawn-specific movement logic including forward movement
 * and diagonal captures.
 */
class Pawn:public Piece{
public:
    Pawn(location coordinate,color player);
    void calculateMoves(std::map<location, std::shared_ptr<Piece>> &board) override;
    [[nodiscard]] std::shared_ptr<Piece> clone() const override;


};
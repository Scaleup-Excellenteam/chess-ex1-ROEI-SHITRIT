#pragma once
#include "ChessBoard.h"
#define KING_TYPE 'k'

/**
 * @file King.h
 * @brief Represents a King Piece on the chess board.
 *
 * This class inherits from the base class `Piece` and implements the movement logic specific to a King.
 * It supports calculating legal moves and cloning the Piece.
 */
class King:public Piece{
public:
    King(location coordinate,color player);
    void calculateMoves(std::map<location, std::shared_ptr<Piece>> &board) override;
    [[nodiscard]] std::shared_ptr<Piece> clone() const override;

};

#pragma once
#include "ChessBoard.h"
#define KNIGHT_TYPE 'n'

/**
 * @brief Represents a Knight Piece in a chess game.
 *
 * The Knight is a chess Piece that moves in an "L" shape: two squares in one direction and one square perpendicular,
 * or one square in one direction and two squares perpendicular. This class encapsulates the logic for the Knight Piece.
 * It allows calculation of possible moves and cloning of the Piece for game operations.
 */
class Knight:public Piece{
public:
    Knight(location coordinate,color player);
    void calculateMoves(std::map<location, std::shared_ptr<Piece>> &board) override;
    [[nodiscard]] std::shared_ptr<Piece> clone() const override;
};

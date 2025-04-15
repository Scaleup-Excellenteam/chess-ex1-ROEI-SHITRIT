#pragma once
#include <memory>
#include <map>
#include <vector>
#include "common.h"
#include <algorithm>

/**
 * Abstract base class representing a chess Piece.
 * Each Piece has a color, position, type (tool), and movement state.
 * It also maintains a vector of valid moves according to the board state.
 */

class Piece {


public:

    Piece(location &coordinate, color player, char tool);
    virtual ~Piece()=default;

    [[nodiscard]] location getCoordinate()const;
    [[nodiscard]] color getColor()const;
    [[nodiscard]] char getTool() const;
    [[nodiscard]] bool hasMoved() const;
    [[nodiscard]] std::vector<location>& getMoves();

    void setLocation(location& coordinateToChange);
    void addMove(const location& move);
    void pieceMoved();

    void clearMoves();
    [[nodiscard]] virtual std::shared_ptr<Piece> clone() const = 0;
    virtual void calculateMoves(std::map<location, std::shared_ptr<Piece>>& board)=0;



private:
    color _player;
    location _coordinate;
    char _tool;
    bool _hasMove;
    std::vector<location> _moves;





};




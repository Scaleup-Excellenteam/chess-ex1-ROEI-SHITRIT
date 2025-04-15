#pragma once
#include <string>
#include <map>
#include "Piece.h"
#include <memory>
#define LIMIT_COL std::pair(1,8)
#define LIMIT_ROW std::pair('A','H')

/**
 * @class ChessBoard
 * @brief Represents the state of a chess game, including the board layout and current turn.
 *
 * This class manages the board's internal representation using a map of locations to pieces.
 * It provides functionality to validate and perform moves, track the king's position,
 * simulate moves for check detection, and switch turns between players.
 *
 * The board is initialized using a string that represents the starting state.
 * Detailed behavior of each function is documented in the .cpp file.
 */

class ChessBoard{
public:
    explicit ChessBoard(std::string& board);
    ChessBoard(const ChessBoard &chessBoard);
    ~ChessBoard()=default;
    int isValidMove(location &from,location &to);
    void movePiece(location &from,location &to);
    void switchTurn();
    [[nodiscard]] bool isKingInCheck(bool isWhite) const;
    int simulateMove(location &from, location &to);
    void calcMoveForAll();
    int runProgram(std::string &input);
    //getters
    std::map<location,std::shared_ptr<Piece>>& getBoard();



private:
    bool _whiteTurn;
    location _blackKing;
    location _whiteKing;
    std::map<location, std::shared_ptr<Piece>> _board;


};



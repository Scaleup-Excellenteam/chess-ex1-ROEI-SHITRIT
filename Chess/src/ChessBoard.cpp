#pragma one

#include <iostream>
#include "ChessBoard.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include "Queen.h"

/**
 * @brief Constructs a ChessBoard from a string representation of the board.
 * @param boardStr A string representing the initial board setup.
 *                 Each character represents a Piece ('P', 'K', etc.), or '#' for empty.
 *                 Characters are read left to right, top to bottom.
 * @throws std::invalid_argument if an invalid character appears in the string.
 */
ChessBoard::ChessBoard(std::string &boardStr): _whiteTurn(true) {
    int counter = 1;
    int modulNeed = 9;
    location start = location (LIMIT_ROW.first,LIMIT_COL.first);
    for(const char c : boardStr){
        if (counter % modulNeed == 0){
            start.first +=1;
            start.second=1;
            counter=1;
        }
        switch (c) {
            case '#':
                break;
            case 'P':
                this->_board[start] = std::make_shared<Pawn>(start, WHITE);
                break;
            case 'K':
                this->_board[start] = std::make_shared<King>(start, WHITE);
                this->_whiteKing=start;
                break;
            case 'R':
                this->_board[start] = std::make_shared<Rook>(start, WHITE);
                break;
            case 'N':
                this->_board[start] = std::make_shared<Knight>(start, WHITE);
                break;
            case 'Q':
                this->_board[start] = std::make_shared<Queen>(start, WHITE);
                break;
            case 'B':
                this->_board[start] = std::make_shared<Bishop>(start, WHITE);
                break;
            case 'p':
                this->_board[start] = std::make_shared<Pawn>(start, BLACK);
                break;
            case 'k':
                this->_board[start] = std::make_shared<King>(start, BLACK);
                this->_blackKing=start;
                break;
            case 'r':
                this->_board[start] = std::make_shared<Rook>(start, BLACK);
                break;
            case 'n':
                this->_board[start] = std::make_shared<Knight>(start, BLACK);
                break;
            case 'q':
                this->_board[start] = std::make_shared<Queen>(start, BLACK);
                break;
            case 'b':
                this->_board[start] = std::make_shared<Bishop>(start, BLACK);
                break;
            default:
                throw std::invalid_argument("Invalid move string values");

        }
        counter+=1;
        start.second+=1;
    }
    calcMoveForAll();
}

/**
 * @brief Copy constructor - creates a deep copy of the given ChessBoard.
 * @param chessBoard The ChessBoard to copy.
 */
ChessBoard::ChessBoard(const ChessBoard &chessBoard) {
    for (const auto& [loc, piecePtr] : chessBoard._board) {
        this->_board[loc] = piecePtr->clone();
    }
    this->_whiteTurn = chessBoard._whiteTurn;
    this->_blackKing = chessBoard._blackKing;
    this->_whiteKing = chessBoard._whiteKing;
}

/**
 * @brief Gets a reference to the internal board map.
 * @return Reference to the board map.
 */
std::map<location, std::shared_ptr<Piece>> &ChessBoard::getBoard() {
    return this->_board;
}

/**
 * @brief Switches the turn between white and black.
 */
void ChessBoard::switchTurn() {
    this->_whiteTurn=!_whiteTurn;

}

/**
 * @brief Checks whether a move is valid, and what type it is.
 * @param from The starting location.
 * @param to The target location.
 * @return Status code:
 *         - INVALID_NO_PIECE
 *         - INVALID_ENEMY_PIECE
 *         - INVALID_DEST_OWN_PIECE
 *         - INVALID_ILLEGAL_MOVE
 *         - INVALID_SELF_CHECK
 *         - VALID_CHECK
 *         - VALID_MOVE
 */
int ChessBoard::isValidMove(location &from, location &to) {
    auto it  = getBoard().find(from);
    if(it == getBoard().end()){
        return INVALID_NO_PIECE;
    }
    else{
        if((_whiteTurn && it->second->getColor() == BLACK) || !_whiteTurn && it->second->getColor() == WHITE ){
            return INVALID_ENEMY_PIECE;
        }
        auto itTo = _board.find(to);
        if( it != getBoard().end()){
            if(itTo != _board.end() && itTo ->second->getColor() == it->second->getColor()){
                return INVALID_DEST_OWN_PIECE;
            }
            if(std::find(it->second->getMoves().begin(), it->second->getMoves().end(), to) == it->second->getMoves().end()){
                return INVALID_ILLEGAL_MOVE;
            }
            int status =this->simulateMove(from,to);
            if(status == INVALID_SELF_CHECK){
                return INVALID_SELF_CHECK;
            }
            if (status == VALID_CHECK){
                return VALID_CHECK;
            }
            return VALID_MOVE;
        }

    }
    return 0;

}

/**
 * @brief Executes a move from one location to another and updates internal state.
 * @param from The starting location.
 * @param to The target location.
 */
void ChessBoard::movePiece(location &from, location &to) {
    auto it =getBoard().find(from);
    std::shared_ptr<Piece> value = it->second;
    value->setLocation(to);
    this->_board.erase(from);
    value->pieceMoved();
    if(value->getTool() == 'k'){
        if(value->getColor() == WHITE){
            this->_whiteKing = value->getCoordinate();
        }
        else{
            this->_blackKing = value->getCoordinate();
        }
    }
    ChessBoard::_board[to] = value;
    this->switchTurn();
    calcMoveForAll();

}

/**
 * @brief Simulates a move to check if it would result in check or self-check.
 *        If valid, performs the move.
 * @param from The source location.
 * @param to The destination location.
 * @return Status code:
 *         - INVALID_SELF_CHECK
 *         - VALID_CHECK
 *         - VALID_MOVE
 */
int ChessBoard::simulateMove(location &from, location &to) {
    ChessBoard tmpBoard(*this);
    bool isWhite = tmpBoard._whiteTurn;
    tmpBoard.movePiece(from,to);
    if(tmpBoard.isKingInCheck(isWhite)){
        return INVALID_SELF_CHECK;
    }
    if(tmpBoard.isKingInCheck(!isWhite)){
        this->movePiece(from,to);
        return VALID_CHECK;
    }
    this->movePiece(from,to);
    return VALID_MOVE;

}

/**
 * @brief Checks if the current player's king is in check.
 * @param isWhite Whether to check for white's king.
 * @return True if in check, false otherwise.
 */
bool ChessBoard::isKingInCheck(bool isWhite) const {
    location kingLocation;
    color player;
    if(isWhite){
        kingLocation = this->_whiteKing;
        player = WHITE;
    }
    else{
        kingLocation = this->_blackKing;
        player = BLACK;
    }
    for(const auto& it : this->_board) {
        const std::shared_ptr<Piece>& piecePtr = it.second;
        if(piecePtr->getColor()!= player){
            if( std::find(piecePtr->getMoves().begin(), piecePtr->getMoves().end(), kingLocation) != piecePtr->getMoves().end()){

                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Recalculates all possible moves for every Piece on the board.
 */
void ChessBoard::calcMoveForAll() {
    for (const auto& [loc, piecePtr] : _board) {
        piecePtr->clearMoves();
        piecePtr->calculateMoves(this->getBoard());
    }
}

/**
 * @brief Converts a string like "E2E4" into a move and checks its validity.
 * @param input A move string of format "E2E4".
 * @return Result of `isValidMove()` on the parsed move.
 * @throws std::invalid_argument if input format is incorrect or out of board limits.
 */
int ChessBoard::runProgram(std::string &input) {
    if (input.length() != 4) {
        throw std::invalid_argument("Invalid move string length");
    }
    int firsIndex =1;
    int thirdIndex = 3;
    int secondIndex =2;
    char fromRow = toupper(input[0]);
    int fromCol = input[firsIndex] - '0';
    char toRow = toupper(input[secondIndex]);
    int toCol = input[thirdIndex] - '0';

    if (fromRow < LIMIT_ROW.first || fromRow > LIMIT_ROW.second ||
        toRow < LIMIT_ROW.first || toRow > LIMIT_ROW.second ||
        fromCol < LIMIT_COL.first || fromCol > LIMIT_COL.second ||
        toCol < LIMIT_COL.first || toCol > LIMIT_COL.second) {
        throw std::invalid_argument("Invalid move string values");
    }

    location from(fromRow, fromCol);
    location to(toRow, toCol);
    return isValidMove(from,to);
}





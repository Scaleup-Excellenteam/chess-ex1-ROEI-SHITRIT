#pragma once

#include <iostream>
#include "ChessBoard.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include "Queen.h"
#include "SpecialExceptions.h"

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
void ChessBoard::movePiece(location &from, location &to,bool isSimulate) {
    auto it =getBoard().find(from);
    std::shared_ptr<Piece> value = it->second;
    value->setLocation(to);
    this->_board.erase(from);
    if(!isSimulate){
        value->pieceMoved();
    }

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
    tmpBoard.movePiece(from,to, false);
    if(tmpBoard.isKingInCheck(isWhite)){
        return INVALID_SELF_CHECK;
    }
    if(tmpBoard.isKingInCheck(!isWhite)){
        this->movePiece(from,to, false);
        return VALID_CHECK;
    }
    this->movePiece(from,to, false);
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
 * @throws std::InvalidMoveFormatException if input format is incorrect or out of board limits.
 */
int ChessBoard::runProgram(std::string &input) {
    if (input.length() != 4) {
        throw InvalidMoveFormatException(input);
    }
    int firsIndex =1;
    int thirdIndex = 3;
    int secondIndex =2;
    char fromRow = toupper(input[0]);
    int fromCol = input[firsIndex] - '0';
    char toRow = toupper(input[secondIndex]);
    int toCol = input[thirdIndex] - '0';
    color statColor = this->_whiteTurn? WHITE : BLACK;

    if (fromRow < LIMIT_ROW.first || fromRow > LIMIT_ROW.second ||
        toRow < LIMIT_ROW.first || toRow > LIMIT_ROW.second ||
        fromCol < LIMIT_COL.first || fromCol > LIMIT_COL.second ||
        toCol < LIMIT_COL.first || toCol > LIMIT_COL.second) {
        throw std::invalid_argument("Invalid move string values");
    }

    location from(fromRow, fromCol);
    location to(toRow, toCol);
    int validMove =  isValidMove(from,to);
    promotePawn(statColor);
    return validMove;
}

/**
 * @brief Checks if it's currently white's turn to move.
 *
 * @return true if it's white's turn, false otherwise.
 */
bool ChessBoard::isWhiteTurn() const {
    return this->_whiteTurn;
}

/**
 * @brief Promotes a pawn that has reached the last row to another piece chosen by the player.
 *
 * This function checks the appropriate row (first or last, depending on color) for pawns eligible for promotion.
 * If a pawn is found, the user is prompted to choose a piece to promote to (Queen, Rook, Bishop, or Knight).
 * The selected piece replaces the pawn on the board.
 *
 * @param currentColor The color of the player whose pawn is being promoted.
 */
void ChessBoard::promotePawn(color& currentColor) {
    char limit;
    color col;
    if(currentColor == WHITE){
         limit = LIMIT_ROW.second;
         col = WHITE;
    } else{
        limit = LIMIT_ROW.first;
        col = BLACK;
    }
    for(int i = 0 ; i < LIMIT_COL.second ; i++){
        location key(limit,i+1);
        auto it = _board.find(key);
        if(it != this->_board.end() && it->second->getTool() == 'p'){
            printPromotionOptions();
            char symbol = getPromotionChoice();
            this->_board[key] = createAPiece(key,symbol , col);
        }
    }

}


/**
 * @brief Creates a new piece of a given type and color at a specified location.
 *
 * This function is used to instantiate a specific chess piece based on a character symbol:
 * 'p' = Pawn, 'k' = King, 'r' = Rook, 'n' = Knight, 'q' = Queen, 'b' = Bishop.
 *
 * @param loc The location on the board where the piece will be placed.
 * @param simbol The character representing the type of piece.
 * @param col The color of the piece (WHITE or BLACK).
 *
 * @return A shared pointer to the newly created Piece.
 *
 * @throws std::invalid_argument If the symbol does not correspond to a valid piece type.
 */
std::shared_ptr<Piece> ChessBoard::createAPiece(location &loc,char simbol,color col) {
    switch(simbol){
        case 'p':
            return std::make_shared<Pawn>(loc, col);

        case 'k':
            return std::make_shared<King>(loc, col);
        case 'r':
            return std::make_shared<Rook>(loc, col);
            break;
        case 'n':
            return std::make_shared<Knight>(loc, col);
            break;
        case 'q':
            return std::make_shared<Queen>(loc, col);
            break;
        case 'b':
            return std::make_shared<Bishop>(loc, col);
            break;
        default:
            throw std::invalid_argument("Invalid move string values");

    }

}


/**
 * @brief Prompts the user to select a piece for pawn promotion and validates the input.
 *
 * Continuously prompts the user until a valid promotion character is entered.
 * Valid inputs are: 'q' for Queen, 'r' for Rook, 'b' for Bishop, 'n' for Knight.
 *
 * @return The selected promotion character.
 *
 * @throws InvalidPromotionException If the entered character is not a valid promotion option.
 */

char ChessBoard::getPromotionChoice() const {
    char choice;
    while (true) {
        try {
            std::cout << "Choose a piece to promote to (q - Queen, r - Rook, b - Bishop, n - Knight): ";
            std::cin >> choice;

            if (choice == 'q' || choice == 'r' || choice == 'b' || choice == 'n') {
                return choice;
            } else {
                throw InvalidPromotionException(choice);
            }

        } catch (const InvalidPromotionException& e) {

            std::cerr << "Promotion Error: " << e.what() << std::endl;
        }
    }
}


/**
 * @brief Prints the available promotion options for a pawn.
 *
 * Displays the characters and corresponding piece names that the user can choose from during promotion.
 */
void ChessBoard::printPromotionOptions()const {
    std::cout << "The pawn has reached the last row! Choose which piece to promote it to:\n";
    std::cout << "q - Queen\n";
    std::cout << "r - Rook\n";
    std::cout << "b - Bishop\n";
    std::cout << "n - Knight\n";

}





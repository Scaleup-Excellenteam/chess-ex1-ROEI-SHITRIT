

#include "Pawn.h"

/**
 * @brief Constructor for the Pawn class.
 * @param coordinate The starting location of the pawn.
 * @param player The color of the pawn (WHITE or BLACK).
 */
Pawn::Pawn(location coordinate, color player): Piece(coordinate, player, PAWN_TYPE){

}


/**
 * @brief Calculates all valid moves for the pawn based on the current board state.
 *
 * Handles forward movement (one or two squares), as well as diagonal captures.
 * Takes into account whether the pawn has already moved.
 */
void Pawn::calculateMoves(std::map<location, std::shared_ptr<Piece>> &board){
    location current = this->getCoordinate();
    bool block = true;
    int numOfOption = 4;
    int dRow[4] = {1,2,1, 1};
    int dCol[4] = {0,0,1, -1};
    int direction = (this->getColor() == WHITE) ? 1 : -1;
    for (int i = 0; i < numOfOption; i++){
        if(dRow[i] == 2 && (this->hasMoved() || block)){
            continue;
        }
        char row = current.first + dRow[i] * direction;
        int col = current.second + dCol[i];

        if (row < LIMIT_ROW.first || row > LIMIT_ROW.second ||
            col < LIMIT_COL.first || col > LIMIT_COL.second){
            continue;
        }

        location newLoc(row, col);
        auto it = board.find(newLoc);
        if(i <= 1){
            if (it == board.end()){
                block = false;
                this->addMove(newLoc);
            }
        }

        else{
            if(it != board.end() && this->getColor() != it->second->getColor()){
                this->addMove(newLoc);
            }

        }

    }

}

/**
 * @brief Creates a copy of the pawn.
 * @return A shared pointer to a new Pawn object copied from this one.
 */
std::shared_ptr<Piece> Pawn::clone() const {
    return std::make_shared<Pawn>(*this);
}




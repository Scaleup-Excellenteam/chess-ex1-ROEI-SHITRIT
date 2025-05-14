#pragma once
#include "common.h"
#include "ChessBoard.h"
#include "PriorityQueue.h"

/**
 * @struct Movement
 * @brief Represents a move in a chess game, including the starting and ending locations, piece type, and move value.
 *
 * This struct is used to store the details of a recommended or performed move. It includes:
 * - The starting location (`from`), the target location (`to`),
 * - The piece symbol (`symbol`), and
 * - The move's value (`value`), which may be used for move prioritization.
 *
 * The struct also defines a subtraction operator to compare moves based on their value.
 */
struct Movement {
    location from;
    location to;
    char symbol;
    int value;

    /**
     * @brief Compares two moves based on their value.
     * @param other The other movement to compare against.
     * @return The difference between the values of the two moves.
     */
    int operator-(const Movement& other) const {
        return this->value - other.value;
    }

    /**
     * @brief Outputs the details of the move in a human-readable format.
     * @param os The output stream to write to.
     * @param movement The movement to print.
     * @return The output stream with the move details appended.
     */
    friend std::ostream& operator<<(std::ostream& os, const Movement& movement) {
        os << "recommended move in order: " << movement.from.first << movement.from.second
           << " to: " << movement.to.first << movement.to.second << std::endl;
    }
};

/**
 * @brief Retrieves all possible moves for a given player on the chessboard.
 * @param board A map representing the chessboard with piece locations.
 * @param playerColor The color of the player (either white or black).
 * @return A vector of all possible movements for the player.
 */
std::vector<Movement> getAllPossibleMoves(const std::map<location, std::shared_ptr<Piece>>& board, color playerColor);

/**
 * @brief Computes the best move using the Minimax algorithm.
 * @param board The current state of the chessboard.
 * @param move The movement to be evaluated.
 * @param depth The maximum depth for the Minimax search.
 * @param currentPlayer The color of the current player.
 * @param isMaximizingPlayer A flag indicating if the current player is maximizing or minimizing their score.
 * @param capturedPieces A vector of pieces captured during the game.
 * @return The value of the move based on the evaluation.
 */
int minimax(ChessBoard& board, Movement& move, int depth, color currentPlayer, bool isMaximizingPlayer, std::vector<std::shared_ptr<Piece>>& capturedPieces);

/**
 * @brief Manages the flow of the game, handling player turns and move execution.
 * @param board The chessboard representing the game state.
 * @param currentPlayer The color of the player whose turn it is.
 */
void manager(ChessBoard& board, color currentPlayer);

/**
 * @brief Undoes the last move made, restoring the board to its previous state.
 * @param board The chessboard representing the game state.
 * @param move The movement to be undone.
 * @param capturedPiece A piece that was captured during the move (if any).
 */
void undoMove(ChessBoard& board, Movement& move, const std::shared_ptr<Piece>& capturedPiece);

/**
 * @brief Evaluates the quality of a move based on various chess principles.
 * @param board The chessboard representing the current game state.
 * @param move The move to be evaluated.
 * @param currentPlayer The color of the player whose move it is.
 * @param capturedPieces A vector of pieces that have been captured during the game.
 * @return The evaluation score of the move.
 */
int evaluateMove(ChessBoard& board, Movement& move, color currentPlayer, std::vector<std::shared_ptr<Piece>>& capturedPieces);

/**
 * @brief Retrieves the value of a chess piece based on its type.
 * @param piece A shared pointer to the piece whose value is to be determined.
 * @return The numerical value of the piece (e.g., 9 for Queen, 1 for Pawn).
 */
int getPieceValue(const std::shared_ptr<Piece>& piece);

/**
 * @brief Attempts to capture a piece on the board if it exists in the target location.
 * @param board The chessboard representing the game state.
 * @param move The movement that may result in a capture.
 * @param currentPlayer The color of the player making the move.
 * @return A shared pointer to the captured piece (if any).
 */
std::shared_ptr<Piece> captureIfExists(ChessBoard& board, const Movement& move, color currentPlayer);

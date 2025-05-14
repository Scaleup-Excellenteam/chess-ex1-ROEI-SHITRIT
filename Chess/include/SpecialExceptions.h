#pragma once
#include <exception>
#include <string>

/**
 * @class InvalidPromotionException
 * @brief Exception thrown when an invalid piece is selected for promotion.
 *
 * This exception is used when a player attempts to promote a pawn to a piece
 * that is not allowed. The allowed pieces are Queen (Q), Rook (R), Bishop (B),
 * and Knight (N). If an invalid piece is selected, this exception is thrown
 * with an appropriate error message.
 */
class InvalidPromotionException : public std::exception {
private:
    std::string message; ///< Error message describing the invalid promotion.

public:
    /**
     * @brief Constructs the exception with the invalid promotion character.
     * @param invalidChar The character representing the invalid piece.
     */
    explicit InvalidPromotionException(const char& invalidChar)
            : message("Invalid promotion piece: '" + std::string(1, invalidChar) + "'. Allowed: Q, R, B, N.") {}

    /**
     * @brief Returns the error message for the invalid promotion exception.
     * @return The error message string.
     */
    const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @class InvalidMoveFormatException
 * @brief Exception thrown when the move input format is invalid.
 *
 * This exception is used when the input format for a move is not valid.
 * It ensures that moves are entered in the correct format, such as 'e2e4'
 * for a valid chess move. If the input does not follow this format,
 * the exception is thrown with a detailed error message.
 */
class InvalidMoveFormatException : public std::exception {
private:
    std::string message; ///< Error message describing the invalid move format.

public:
    /**
     * @brief Constructs the exception with the invalid move input string.
     * @param input The invalid move input string.
     */
    InvalidMoveFormatException(const std::string& input)
            : message("Invalid move input format: '" + input + "'. Expected format: e2e4.") {}

    /**
     * @brief Returns the error message for the invalid move format exception.
     * @return The error message string.
     */
    const char* what() const noexcept override {
        return message.c_str();
    }
};

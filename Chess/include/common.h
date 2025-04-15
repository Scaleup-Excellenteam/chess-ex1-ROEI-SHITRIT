#pragma once
#include <utility>

/**
 * @enum codes
 * @brief Status codes returned when checking the validity of a move.
 */
enum codes{

    INVALID_NO_PIECE = 11,
    INVALID_ENEMY_PIECE = 12,
    INVALID_DEST_OWN_PIECE = 13,
    INVALID_ILLEGAL_MOVE = 21,
    INVALID_SELF_CHECK = 31,
    VALID_MOVE = 42,
    VALID_CHECK = 41

};

/**
 * @enum color
 * @brief Represents the color of a chess Piece or player.
 */

enum color{
    WHITE,
    BLACK
};

/**
 * @typedef location
 * @brief Represents a board location using a row character and column integer.
 *        For example, 'E', 2 represents square E2.
 */
typedef std::pair<char, int> location;
inline bool operator==(location location1 , location location2){
    return location1.first ==location2.first && location1.second==location2.second;
}
inline bool operator<(const location& lhs, const location& rhs) {
    if (lhs.first == rhs.first) {
        return lhs.second < rhs.second;
    }
    return lhs.first < rhs.first;
}

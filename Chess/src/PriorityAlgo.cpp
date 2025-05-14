#include <climits>
#include <iostream>
#include  "PriorityAlgo.h"
#define DEPTH 2

void manager(ChessBoard& board, color currentPlayer){
    PriorityQueue<Movement> bestMoves;
    std::vector<std::shared_ptr<Piece>> capturedPieces;
    std::vector<Movement> allMoves  = getAllPossibleMoves(board.getBoard(),currentPlayer);
    bool isMaximizing = true;
    for(Movement movement : allMoves){
        movement.value = minimax(board,movement,DEPTH,currentPlayer,isMaximizing,capturedPieces);
        bestMoves.push(movement);

    }
   bestMoves.print();


}


std::vector<Movement> getAllPossibleMoves(const std::map<location, std::shared_ptr<Piece>>& board, color playerColor){
    std::vector<Movement> allMoves;
    for(auto& [pos,piece] : board){
        if( piece->getColor()== playerColor){
            Movement movement;
            for(location loc : piece->getMoves()){
                movement.from = pos;
                movement.to = loc;
                movement.symbol = piece->getTool();
                movement.value = 0;
                allMoves.push_back(movement);
            }
        }
    }
    return allMoves;

}





int evaluateMove(ChessBoard& board, Movement& move, color currentPlayer, std::vector<std::shared_ptr<Piece>>& capturedPieces) {
    int score = 0;

    if (!capturedPieces.empty()) {
        for (const auto& capturedPiece : capturedPieces) {
            if(capturedPiece->getColor() != currentPlayer){
                score += getPieceValue(capturedPiece);
            }

        }
    }


    for (const auto& pair : board.getBoard()) {
        auto attacker = pair.second;

        if (attacker->getColor() != currentPlayer)
            continue;

        int attackerValue = getPieceValue(attacker);
        auto moves = attacker->getMoves();

        for (const auto& targetPos : moves) {
            auto it = board.getBoard().find(targetPos);
            if (it != board.getBoard().end() && it->second->getColor() != currentPlayer) {
                int targetValue = getPieceValue(it->second);
                if (targetValue > attackerValue) {
                    score += targetValue/2;
                }
            }
        }
    }


    for (const auto& pair : board.getBoard()) {

        auto enemyPiece = pair.second;

        if (enemyPiece->getColor() == currentPlayer)
            continue;

        int enemyValue = getPieceValue(enemyPiece);
        auto threats = enemyPiece->getMoves();

        for (const auto& threatenedPos : threats) {
            auto it = board.getBoard().find(threatenedPos);
            if (it != board.getBoard().end() && it->second->getColor() == currentPlayer) {
                int ourValue = getPieceValue(it->second);
                if (enemyValue < ourValue) {
                    score -= ourValue/2;
                }
            }
        }
    }

    return score;
}





int getPieceValue(const std::shared_ptr<Piece>& piece) {
    if (!piece) return 0;

    switch (piece->getTool()) {
        case 'K':
        case 'k':
            return 100;
        case 'Q':
        case 'q':
            return 90;
        case 'R':
        case 'r':
            return 50;
        case 'B':
        case 'b':
            return 30;
        case 'N':
        case 'n':
            return 30;
        case 'P':
        case 'p':
            return 10;
        default:
            return 0;
    }
}


void undoMove(ChessBoard& board, Movement& move, const std::shared_ptr<Piece>& capturedPiece){
    board.movePiece(move.to, move.from, true);

    if(capturedPiece != nullptr){
        board.getBoard()[move.to] = capturedPiece;
    }

}




int minimax(ChessBoard& board, Movement& move, int depth, color currentPlayer, bool isMaximizingPlayer, std::vector<std::shared_ptr<Piece>>& capturedPieces) {
    std::shared_ptr<Piece> capturedPiece = captureIfExists(board, move, currentPlayer);
    if (capturedPiece) {
        capturedPieces.push_back(capturedPiece);
    }

    board.movePiece(move.from, move.to, true);

    if (depth == 0) {
        int eval = evaluateMove(board, move, currentPlayer, capturedPieces);
        undoMove(board, move, capturedPiece);
        if (capturedPiece) {
            capturedPieces.pop_back();
        }
        return eval;
    }

    color nextPlayer = (currentPlayer == color::WHITE) ? color::BLACK : color::WHITE;
    std::vector<Movement> nextMoves = getAllPossibleMoves(board.getBoard(), nextPlayer);
    int bestEval = isMaximizingPlayer ? INT_MIN : INT_MAX;

    for (auto& nextMove : nextMoves) {
        int score = minimax(board, nextMove, depth - 1, nextPlayer, !isMaximizingPlayer, capturedPieces);
        if (isMaximizingPlayer) {
            bestEval = std::max(bestEval, score);
        } else {
            bestEval = std::min(bestEval, score);
        }
    }

    undoMove(board, move, capturedPiece);
    if (capturedPiece) {
        capturedPieces.pop_back();
    }

    return bestEval;
}







std::shared_ptr<Piece> captureIfExists( ChessBoard& board, const Movement& move, color currentPlayer) {
    auto it = board.getBoard().find(move.to);
    if (it != board.getBoard().end() && it->second->getColor() != currentPlayer) {
        return it->second;
    }
    return nullptr;
}






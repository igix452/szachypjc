#include "gamestatus.h"
#include "pieces/king.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "chessboard.h"
#include "movemanager.h"
#include "positionmanager.h"

GameStatus::GameStatus() {}

bool GameStatus::castleAllowed(const PieceColor &color, const bool &kingSide) const
{
    int rank = (color == WHITE ? 0 : 7);
    int kingFile = 4;
    int rookFile = kingSide ? 7 : 0;
    Piece* potentialKing = board->getPiece(Square(kingFile, rank));
    Piece* potentialRook = board->getPiece(Square(rookFile, rank));

    if (potentialKing &&
        dynamic_cast<King*>(potentialKing) &&
        !potentialKing->hasMoved() &&
        potentialRook &&
        dynamic_cast<Rook*>(potentialRook) &&
        !potentialRook->hasMoved()
        ) {
        return true;
    }
    return false;
}

bool GameStatus::isCheckmate(const PieceColor &color) const
{
    if (positionManager->isKingInCheck(color)) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++){
                const Piece* piece = board->getPiece(Square(i,j));
                if (piece && piece->getColor() == color) {
                    if(!moveManager->getLegalMoves(Square(i,j)).empty()) return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool GameStatus::isStalemate(const PieceColor &color) const
{
    if (!positionManager->isKingInCheck(color) && turn == color) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++){
                const Piece* piece = board->getPiece(Square(i,j));
                if (piece && piece->getColor() == color) {
                    if(!moveManager->getLegalMoves(Square(i,j)).empty()) return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool GameStatus::isPromotion() const
{
    // sprawdza czy są piony na linii promocji
    for (int i=0; i<8; i++) {
        if (board->getPiece(Square(i, 0)) && dynamic_cast<Pawn*>(board->getPiece(Square(i, 0)))) return true;
        if (board->getPiece(Square(i, 7)) && dynamic_cast<Pawn*>(board->getPiece(Square(i, 7)))) return true;
    }
    return false;
}

void GameStatus::incIdleMoves()
{
    idleMovesCounter++;
}

void GameStatus::resetIdleMoves()
{
    idleMovesCounter = 0;
}

PieceColor GameStatus::getTurn()
{
    return turn;
}

void GameStatus::switchTurn()
{
    (turn == WHITE) ? turn = BLACK : turn = WHITE;
}

std::string GameStatus::getFEN()
{
    std::string positionField = "";
    std::string turnField = "";
    std::string castleField = "";
    std::string enPassantField = "";
    std::string idleMovesField = "";
    std::string fullMovesField = "";

    for (int i = 7; i >=0; i--){
        int emptyFields = 0;
        for (int j = 0; j < 8; j++) {
            const Piece* piece = board->getPiece(Square(j,i));
            if (piece) {
                char letter = piece->getLetter();
                letter = (piece->getColor() == BLACK) ? std::tolower(letter) : letter;
                if (emptyFields > 0) positionField += std::to_string(emptyFields);
                positionField += letter;
                emptyFields = 0;
            } else {
                emptyFields++;
            }
        }
        if (emptyFields > 0) positionField += std::to_string(emptyFields);
        if (i != 0) positionField += '/';
    }

    turnField += (turn == WHITE) ? 'w' : 'b';

    if (castleAllowed(WHITE, true)) castleField += 'K';
    if (castleAllowed(WHITE, false)) castleField += 'Q';
    if (castleAllowed(BLACK, true)) castleField += 'k';
    if (castleAllowed(BLACK, false)) castleField += 'q';
    if (castleField.empty()) castleField = "-";

    const Move* lastMove = moveManager->getLastMove();
    if (lastMove) {
        if (dynamic_cast<Pawn*>(lastMove->getPiece())) {
            int x = lastMove->getStartSquare().getFile();
            //int x2 = lastMove->getEndSquare().getFile();
            int y1 = lastMove->getStartSquare().getRank();
            int y2 = lastMove->getEndSquare().getRank();
            if (abs(y1-y2) == 2) { //pion sie ruszyl o 2 pola
                char fileChar = 'a' + x;
                char rankChar = '0' + ((y1+y2+2)/2);
                enPassantField += fileChar;
                enPassantField += rankChar;
            }
        }
    }
    if (enPassantField.empty()) enPassantField = "-";

    idleMovesField = std::to_string(idleMovesCounter);

    fullMovesField = std::to_string(moveManager->getMovesList().size()/2 + 1);

    return positionField + " " + turnField + " " + castleField + " " + enPassantField + " " + idleMovesField + " " + fullMovesField;
}

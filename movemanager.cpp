#include "movemanager.h"
#include "pieces/king.h"
#include "pieces/pawn.h"
#include "positionmanager.h"
#include "qlogging.h"
#include <cstdlib>

MoveManager::MoveManager() {}


void MoveManager::handleMove(const Square &from, const Square &to)
{
    Piece* movedPiece = board->getPiece(from);
    Piece* capturedPiece = board->getPiece(to);

    if (!movedPiece || getLegalMoves(from).empty()) {
        qDebug("nieprawidłowy ruch");
        return;
    }

    // Obsługa roszady - ruch wieży
    if (dynamic_cast<const King*>(movedPiece) && abs(from.getFile() - to.getFile()) == 2) {
        // Roszada
        int rank = from.getRank();
        if (to.getFile() == 6) {
            // Roszada krótka
            board->movePiece(Square(7, rank), Square(5, rank));
        } else if (to.getFile() == 2) {
            // Roszada długa
            board->movePiece(Square(0, rank), Square(3, rank));
        }
    }

    //Obsługa bicia w przelocie
    if (dynamic_cast<const Pawn*>(movedPiece) && from.getFile() != to.getFile() && !capturedPiece) {
        Square capturedEnPassant = Square(to.getFile(), from.getRank());
        capturedPiece = board->getPiece(capturedEnPassant);
        board->setPiece(capturedEnPassant, nullptr);
    }

    movesList.push_back(Move(from, to, movedPiece, capturedPiece));
    board->movePiece(from, to);
    movedPiece->setPieceMoved();
    status->switchTurn();
    if (dynamic_cast<const Pawn*>(movedPiece) || capturedPiece) {
        status->resetIdleMoves();
    } else {
        status->incIdleMoves();
    }
}

std::vector<Square> MoveManager::getLegalMoves(const Square &position) const
{
    // sprawdza czy potencjalne ruchy figury nie narażą króla na atak
    const Piece* piece = board->getPiece(position);
    if (!piece) return {};
    std::vector<Square> potentialMoves = piece->getValidSquares(position);
    std::vector<Square> legalMoves;
    for (const auto& move : potentialMoves) {
        ChessBoard tempBoard = *board;
        tempBoard.movePiece(position,move);
        PositionManager tempManager;
        tempManager.setBoard(tempBoard);
        if (!tempManager.isKingInCheck(piece->getColor())) {
            legalMoves.push_back(move);
        }
    }
    // Roszada:
    if (dynamic_cast<const King*>(piece)) {
        if (canCastle(piece->getColor(), true)) {
            Square castleSquare = Square(position.getFile()+2, position.getRank());
            legalMoves.push_back(castleSquare);
        }
        if (canCastle(piece->getColor(), false)) {
            Square castleSquare = Square(position.getFile()-2, position.getRank());
            legalMoves.push_back(castleSquare);
        }

    }
    // Bicie w przelocie:
    if (dynamic_cast<const Pawn*>(piece)) {
        if (!movesList.empty()) {
            const Move lastMove = movesList.back();
            if (dynamic_cast<const King*>(lastMove.getPiece())) {
                int x = lastMove.getStartSquare().getFile();
                int y1 = lastMove.getStartSquare().getRank();
                int y2 = lastMove.getEndSquare().getRank();
                if (abs(y1-y2) == 2) { //pionek przeciwnika sie ruszyl o 2 pola
                    if (position == Square(x-1, y2) || position == Square(x+1, y2)) {
                        Square enPsntSquare = Square(x, (y1+y2)/2);
                        legalMoves.push_back(enPsntSquare);
                    }
                }
            }
        }
    }
    return legalMoves;
}

bool MoveManager::canCastle(const PieceColor &color, const bool &kingSide) const
{
    int rank = (color == WHITE ? 0 : 7);
    int kingFile = 4;
    if (status->castleAllowed(color, kingSide))
    {

        // sprawdzenie czy droga jest zablokowana
        int direction = kingSide ? 1 : -1;
        for (int i = 1; i <= (kingSide ? 2 : 3); i++) {
            if (board->getPiece(Square(kingFile + i * direction, rank))) {
                return false;
            }
        }

        // sprawdzenie czy król lub droga nie jest atakowana
        for (int i = 0; i <= 2; i++) {
            ChessBoard tempBoard = *board;
            tempBoard.movePiece(Square(kingFile, rank), Square(kingFile + i * direction, rank));
            PositionManager tempManager;
            tempManager.setBoard(tempBoard);
            if (tempManager.isKingInCheck(color)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

std::list<Move> MoveManager::getMovesList()
{
    return movesList;
}

Move* MoveManager::getLastMove()
{
    return &movesList.back();
}

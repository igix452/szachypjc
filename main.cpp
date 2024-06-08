#include "gamesettingswindow.h"
#include "mainwindow.h"
#include "chess.h"
#include "cli.h"
#include <iostream>

#include <QApplication>

/*********************************************
 *
 * PROTOTYP APLIKACJI
 * ZAIMPLEMENTOWANA LOGIKA RUCHÓW
 * GRA PRZECIWKO STOCKFISH
 * GRA JAKO BIAŁE
 *
 ********************************************/



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GameSettingsWindow sett;
    w.show();
    //return a.exec();
    //sett.show();
    return a.exec();
    //std::cout<<std::endl;
    /*ChessGame game;
    game.initializeGame();
    //CLI::displayPiece(std::make_unique<Pawn>(BLACK, false).get());
    std::cout<<std::endl;

    game.makeMove(Square(4,1),Square(4,3));
    CLI::displayBoard(*game.getBoard());*/

    return 0;
}

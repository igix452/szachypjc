#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qgridlayout.h"
#include "QPushButton"
#include "QMessageBox"
#include "QInputDialog"
#include "chess.h"
#include "QPixmap"
#include "QIcon"
#include <iostream>
#include "QProcess"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setVerticalSpacing(0);
    gridLayout->setHorizontalSpacing(0);
    gridLayout->setContentsMargins(0,0,0,0);
    ui->centralwidget->setLayout(gridLayout);
    for (int i = 0; i < 8; ++i) { // Iteruje przez wszystkie wiersze szachownicy
        for (int j = 0; j < 8; ++j) { // Iteruje przez wszystkie kolumny szachownicy
            QPushButton *button = new QPushButton(this); // Tworzy nowy przycisk
            button->setFixedSize(70, 70); // Ustawia rozmiar przycisku
            button->setContentsMargins(0,0,0,0);
            //setStyleSheet("font-size:60px");
            button->setIconSize(QSize(60,60));
            ((i+j)%2==0) ? button->setStyleSheet("background-color: #759557") : button->setStyleSheet("background-color: #EDEDD1");
            gridLayout->addWidget(button, 7-j /*j*/ , i); // Dodaje przycisk do układu siatki
            boardButtons[i][j] = button; // Zapisuje wskaźnik do przycisku

            // Łączy sygnał kliknięcia przycisku z odpowiednią metodą


            // STOCKFISH -------------------------------------------
            game.blackPlayer = std::make_unique<StockfishPlayer>(10, BLACK, 5);
            game.blackPlayer->connectToEngine();
            game.blackPlayer->setDifficulty(0);
            // -----------------------------------------------------------------

            connect(button, &QPushButton::clicked, [this, i, j]() {
                handleButtonClick(i, j);
            });
        }
    }
    game.initializeGame();
    updateBoard();
    lastClick.reset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButtonClick(int x, int y)
{
    setDefaultSquaresColors(true);
    const Piece* piece = game.getBoard()->getPiece(Square(x, y));

    // Pierwsze kliknięcie
    if (!lastClick) {
        if (piece) {
            if (piece->getColor() == game.getTurn()) {
                lastClick = std::make_unique<Square>(x, y);
                for (auto& square : game.getLegalMoves(Square(x, y))) {
                    boardButtons[square.getFile()][square.getRank()]->setStyleSheet("background-color: lightblue;");
                }
            }
        }
        return;
    }
    // Drugie kliknięcie
    else if (lastClick) {
        Square lastClickedSquare = *lastClick;

        // Sprawdzenie, czy użytkownik kliknął na własną figurę ponownie
        if (lastClickedSquare.getFile() == x && lastClickedSquare.getRank() == y) {
            lastClick.reset();
            setDefaultSquaresColors(true);
            return;
        }

        std::vector<Square> legalMoves = game.getLegalMoves(lastClickedSquare);

        // Sprawdzenie, czy kliknięcie jest na liście legalnych ruchów
        if (std::find(legalMoves.begin(), legalMoves.end(), Square(x, y)) != legalMoves.end()) {
            game.makeMove(lastClickedSquare, Square(x, y));
            if (game.isPromotion()) {
                promotePawn(Square(x,y));
            }
            updateBoard();
            setDefaultSquaresColors(true);
            lastClick.reset();
            std::cout<<game.getFENPosition()<<std::endl;
            handleGameEnd();


            //testy stockfisha
            QApplication::processEvents();
            Move stockfishMove = game.blackPlayer->getNextMove(game);
            game.makeMove(stockfishMove.getStartSquare(), stockfishMove.getEndSquare());
            updateBoard();
            setDefaultSquaresColors(true);
            //koniec testow
            handleGameEnd();

        }
        // Kliknięcie na innej figurze tego samego gracza
        else if (piece && piece->getColor() == game.getTurn()) {
            lastClick = std::make_unique<Square>(x, y);
            for (auto& square : game.getLegalMoves(Square(x, y))) {
                boardButtons[square.getFile()][square.getRank()]->setStyleSheet("background-color: lightblue;");
            }
        }
        // Kliknięcie na nielegalny ruch lub przeciwnika
        else {
            lastClick.reset();
            setDefaultSquaresColors(true);
        }
    }
}
void MainWindow::updateBoard(){
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            const Piece* piece = game.getBoard()->getPiece(Square(i,j));
            switch ((piece) ? piece->getType() : NONE) {
            case NONE:
                boardButtons[i][j]->setIcon(QIcon());
                break;
            case PAWN:
                boardButtons[i][j]->setIcon((piece->getColor() == WHITE ? QIcon(":/assets/pawn-w.svg") : QIcon(":/assets/pawn-b.svg")));
                break;
            case KNIGHT:
                boardButtons[i][j]->setIcon((piece->getColor() == WHITE ? QIcon(":/assets/knight-w.svg") : QIcon(":/assets/knight-b.svg")));
                break;
            case BISHOP:
                boardButtons[i][j]->setIcon((piece->getColor() == WHITE ? QIcon(":/assets/bishop-w.svg") : QIcon(":/assets/bishop-b.svg")));
                break;
            case ROOK:
                boardButtons[i][j]->setIcon((piece->getColor() == WHITE ? QIcon(":/assets/rook-w.svg") : QIcon(":/assets/rook-b.svg")));
                break;
            case QUEEN:
                boardButtons[i][j]->setIcon((piece->getColor() == WHITE ? QIcon(":/assets/queen-w.svg") : QIcon(":/assets/queen-b.svg")));
                break;
            case KING:
                boardButtons[i][j]->setIcon((piece->getColor() == WHITE ? QIcon(":/assets/king-w.svg") : QIcon(":/assets/king-b.svg")));
                break;
            default:
                boardButtons[i][j]->setIcon(QIcon());
                break;
            }
        }
    }
}

void MainWindow::setDefaultSquaresColors(const bool &paintSpecialSquares){
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            ((i+j)%2==0) ? boardButtons[i][j]->setStyleSheet("background-color: #759557") : boardButtons[i][j]->setStyleSheet("background-color: #EDEDD1");
        }
    }
    if (paintSpecialSquares) {
        if (game.getBoard()->isKingInCheck(WHITE)) {
            const Square kingPos = game.getBoard()->findKing(WHITE);
            boardButtons[kingPos.getFile()][kingPos.getRank()]->setStyleSheet("background-color: #EE5555");
        }
        if (game.getBoard()->isKingInCheck(BLACK)) {
            const Square kingPos = game.getBoard()->findKing(BLACK);
            boardButtons[kingPos.getFile()][kingPos.getRank()]->setStyleSheet("background-color: #EE5555");
        }
        if (const Move* lastMove = game.getLastMove()) {
            int x1 = lastMove->getStartSquare().getFile();
            int x2 = lastMove->getEndSquare().getFile();
            int y1 = lastMove->getStartSquare().getRank();
            int y2 = lastMove->getEndSquare().getRank();
            boardButtons[x1][y1]->setStyleSheet("background-color: #AFA23D");
            boardButtons[x2][y2]->setStyleSheet("background-color: #AFA23D");
        }
    }
}

void MainWindow::handleGameEnd() {
    if (game.isCheckmate(WHITE)) {
        QMessageBox::information(this, "Koniec gry", "Mat! Czarne wygrywają");
    } else if (game.isCheckmate(BLACK)) {
        QMessageBox::information(this, "Koniec gry", "Mat! Białe wygrywają.");
    } else if (game.isStalemate(BLACK) || game.isStalemate(WHITE)){
        QMessageBox::information(this, "Koniec gry", "Pat! Remis.");
    }
}

void MainWindow::promotePawn(const Square& pos) {
    QStringList items;
    items << "Hetman" << "Wieża" << "Goniec" << "Skoczek";

    bool ok;
    PieceType type = QUEEN; // domyslnie hetman
    QString item = QInputDialog::getItem(this, tr("Promocja piona"), tr("Wybierz figure:"), items, 0, false, &ok);
    if (ok && !item.isEmpty()) {

        if (item == "Hetman") {
            type = QUEEN;
        } else if (item == "Wieża") {
            type = ROOK;
        } else if (item == "Goniec") {
            type = BISHOP;
        } else if (item == "Skoczek") {
            type = KNIGHT;
        }
        game.getBoard()->promotePawn(pos, type);
        updateBoard();
    }
}

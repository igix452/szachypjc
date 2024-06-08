#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chess.h"
#include "qpushbutton.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void handleButtonClick(int x, int y);
private:
    Ui::MainWindow *ui;
    void updateBoard();
    ChessGame game;
    QPushButton* boardButtons[8][8];
    std::unique_ptr<Square> lastClick;
    void setDefaultSquaresColors(const bool &paintSpecialSquares);
    void handleGameEnd();
    void promotePawn(const Square &pos);
};
#endif // MAINWINDOW_H

#ifndef GAMESETTINGSWINDOW_H
#define GAMESETTINGSWINDOW_H
// DO ZROBIENIA
#include <QWidget>

namespace Ui {
class GameSettingsWindow;
}

class GameSettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameSettingsWindow(QWidget *parent = nullptr);
    ~GameSettingsWindow();

private:
    Ui::GameSettingsWindow *ui;
};

#endif // GAMESETTINGSWINDOW_H

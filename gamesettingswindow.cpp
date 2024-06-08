#include "gamesettingswindow.h"
#include "ui_gamesettingswindow.h"

GameSettingsWindow::GameSettingsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameSettingsWindow)
{
    ui->setupUi(this);
}

GameSettingsWindow::~GameSettingsWindow()
{
    delete ui;
}

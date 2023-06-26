#include "gameoptions.h"
#include "ui_gameoptions.h"

GameOptions::GameOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOptions)
{
    ui->setupUi(this);
    this->setFixedSize(400,300);

    stwindow = nullptr;

    //Модифицируем SpinBox
    ui->spinBox->setRange(3,100);
}

GameOptions::~GameOptions()
{
    // (?) Поудалять game и игроков
    delete ui;
}


void GameOptions::on_buttonBox_accepted()
{
    Game = new game();
    Game->Player1 = new player(ui->Player1name->text());
    Game->Player2 = new player(ui->Player2name->text());
    // Передаём количество палочек N и выводим окно игры.
    Game->numberOfSticks = ui->spinBox->value();
    Game->paintSticks();
    Game->updatePlayersMove();
    Game->show();
}


void GameOptions::on_buttonBox_rejected()
{
    return;
}


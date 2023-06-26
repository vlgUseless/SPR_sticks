#include "startwindow.h"
#include "ui_startwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QString>

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);

    ui->statusbar->showMessage("Сделал: Гаар В. С., гр. 3530201/20002 ☺");

    //Выставляем изображения
    QPixmap stick(":/img/img/stick.png");
    QPixmap stick_rev(":/img/img/stick_reversed.png");

    int w = ui->img1->width();
    int h = ui->img1->height();

    ui->img1->setPixmap(stick.scaled(w, h, Qt::KeepAspectRatio));
    ui->img2->setPixmap(stick_rev.scaled(w, h, Qt::KeepAspectRatio));
}

StartWindow::~StartWindow()
{
    // (?) Удалить options
    delete ui;
}


void StartWindow::on_StartGame_clicked()
{
    options = new GameOptions();
    options->stwindow = this;
    options->show();
}


void StartWindow::on_Rules_clicked()
{
    QMessageBox::information(this, "Правила игры",
                       "Два игрока поочерёдно выбирают от 1 до 3 палочек из доступной кучи. Игрок, взявший последнюю палочку, проигрывает.");
}


void StartWindow::on_Exit_clicked()
{
    QMessageBox::StandardButton quit_reply = QMessageBox::critical(this,"Закрытие программы","Вы действительно хотите выйти?", QMessageBox::Yes | QMessageBox::No);
    if (quit_reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}



#include "startwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //player *player1, *player2;
    // Создать указатели на двух игроков и как-то их вернуть из функции?
    StartWindow *w = new StartWindow();
    w->show();
    return a.exec();
}

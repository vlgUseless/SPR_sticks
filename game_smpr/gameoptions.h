#ifndef GAMEOPTIONS_H
#define GAMEOPTIONS_H

#include <QDialog>
#include "game.h"

namespace Ui {
class GameOptions;
}

class StartWindow;
class GameOptions : public QDialog
{
    Q_OBJECT

public:
    friend StartWindow;

    explicit GameOptions(QWidget *parent = nullptr);
    ~GameOptions();

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::GameOptions *ui;
protected:
    game *Game;
    StartWindow *stwindow;
};

#endif // GAMEOPTIONS_H

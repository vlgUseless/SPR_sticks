#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "gameoptions.h"


namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    friend GameOptions;

    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_StartGame_clicked();

    void on_Rules_clicked();

    void on_Exit_clicked();
private:
    Ui::StartWindow *ui;

protected:
    GameOptions *options;
};

#endif // STARTWINDOW_H

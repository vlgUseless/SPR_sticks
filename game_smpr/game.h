#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

QT_BEGIN_NAMESPACE
namespace Ui { class game; }
QT_END_NAMESPACE

class player;
class GameOptions;
class game : public QMainWindow
{
    Q_OBJECT

public:
    friend player;
    friend GameOptions;
    game(QWidget *parent = nullptr);
    ~game();

private slots:
    void on_action_triggered();
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::game *ui;
    void removeObjectsFromScene();
protected:
    QGraphicsScene *scene;
    size_t numberOfSticks;
    player *Player1, *Player2;
    //QVector<QGraphicsPixmapItem*> sticks; //Массив палочек

    void updatePlayersMove();
    void paintSticks();
};

//Класс ИГРОК
class player : public game
{
public:
    friend game;
    friend GameOptions;
    player(QString name = "", size_t win = 0);

protected:
    QString PlayerName;
    size_t win_count;
};

#endif // GAME_H

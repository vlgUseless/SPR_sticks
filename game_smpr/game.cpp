#include "game.h"
#include "ui_game.h"
#include <QDebug>
#include <QPixmap>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QObject>
#include <math.h>
#include <QPen>
#include <QMouseEvent>
#include <QKeyEvent>

game::game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::game)
{
    //Устанавливаем UI и его размеры
    ui->setupUi(this);
    this->setFixedSize(800,600);
    //Значения по умолчанию
    numberOfSticks = 3;

    //Устанавливаем сцену
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(10,30,781,511);

    //Настраиваем спинбокс для выбора палочек
    ui->spinBox->setRange(1,3);
}

game::~game()
{
    //Удаление элементов со сцены
    /*
    for (int i = 0; i < itemCount && i >= 0 && objectsToRemove > 0; i++) {
        QGraphicsItem* item = items[i];
        QGraphicsPixmapItem* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(item);
        if (pixmapItem) {
            scene->removeItem(pixmapItem);
            delete pixmapItem;
            objectsToRemove--;
            numberOfSticks--;
        }
    }
    */
    delete scene;
    delete ui;
}

void game::on_action_triggered()
{
    QMessageBox::StandardButton quit_reply = QMessageBox::critical(this,"Выход из игры","Вы действительно хотите выйти?", QMessageBox::Yes | QMessageBox::No);
    if (quit_reply == QMessageBox::Yes) {
        this->close();
    }
    return;
}

void game::paintSticks() {

    //Меняем статус-бар
    ui->statusbar->showMessage(QString("Количество палочек в куче: %1").arg(numberOfSticks));

    //Добавляем палочки на экран
    QPixmap stick_img(":/img/img/stick.png");

    // Размеры сцены и изображения
    int sceneWidth = scene->width();
    int sceneHeight = scene->height();
    int imageWidth = stick_img.width();
    int imageHeight = stick_img.height();

    // Вычисление промежутков для равномерного распределения изображений
    int rowCount = std::sqrt(numberOfSticks); // Количество строк
    int columnCount = std::ceil(qreal(numberOfSticks) / rowCount); // Количество столбцов
    // int columnCount = (numberOfSticks + rowCount - 1) / rowCount; // Альтернативный вариант подсчёта кол-ва столбцов
    int gapX = sceneWidth / columnCount;
    int gapY = sceneHeight / rowCount;

    // Вычисление дополнительного смещения для изображений в первой строке
    int extraOffsetY = 10 + numberOfSticks / 5;

    // Создание и распределение изображений
    for (size_t i = 0; i < numberOfSticks; ++i) {
        // Создание QGraphicsPixmapItem с изображением
        QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(stick_img);

        // Масштабирование изображения
        qreal scaleFactor = qMin(qreal(gapX) / imageWidth, qreal(gapY) / imageHeight);
        pixmapItem->setScale(scaleFactor);

        // Вычисление позиции изображения на сцене
        int row = i / columnCount; // Номер строки
        int column = i % columnCount; // Номер столбца
        qreal x = column * gapX + (gapX - imageWidth * scaleFactor) / 2;
        qreal y = row * gapY + extraOffsetY + (gapY - imageHeight * scaleFactor) / 2;
        pixmapItem->setPos(x, y);

        // Добавление изображения на сцену
        scene->addItem(pixmapItem);
    }
}


player::player(QString name, size_t win): PlayerName(name), win_count(win) {}

void game::on_spinBox_valueChanged(int arg1)
{
    // Удалите предыдущие подсвеченные изображения
    scene->clearSelection();

    // Подсветка нового количества изображений
    QList<QGraphicsItem*> items = scene->items();
    for (int i = 0; i < ui->spinBox->value(); i++) {
        if (i < items.size()) {
            items[i]->setSelected(true);
        }
    }
    scene->update();
}

void game::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        removeObjectsFromScene();
    }
}

void game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        removeObjectsFromScene();
    }
}

void game::removeObjectsFromScene()
{
    int objectsToRemove = ui->spinBox->value(); //Количество элементов для удаления

    QList<QGraphicsItem*> items = scene->items(); //Список всех элементов на сцене (экране)
    int itemCount = items.size(); //Количество всех элементов на сцене (экране)
    // Удаляем только выбранное количество объектов, начиная с первого или последнего объекта
    for (int i = 0; i < itemCount && i >= 0 && objectsToRemove > 0; i++) {
        QGraphicsItem* item = items[i];
        QGraphicsPixmapItem* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(item);
        if (pixmapItem) {
            scene->removeItem(pixmapItem);
            delete pixmapItem;
            objectsToRemove--;
            numberOfSticks--;
        }
    }
    //Меняем общее количество палочек в статус-баре.
    ui->statusbar->showMessage(QString("Количество палочек в куче: %1").arg(numberOfSticks));
    //Если осталось 0 палочек, то завершаем игру
    if (numberOfSticks == 0) {
        QString winner;
        //Если в поле имя первого игрока
        if (ui->lab_currentPlayerName->text() == Player1->PlayerName) {
            winner = Player2->PlayerName;
            //Player1->win_count++; //Пока не имеет смысла, т. к. игроки каждый раз создаются новые
        }
        else {
            winner = Player1->PlayerName;
            //Player2->win_count++;
        }
        QMessageBox::information(this, QString("Победил игрок %1").arg(winner),
                           QString("Игра завершилась победой %1.").arg(winner));
        this->close();
    }
    //Меняем ход игрока
    updatePlayersMove();
    // Обновление сцены
    scene->update();

}

void game::updatePlayersMove() {
    //Если поле пустое, то ход первого игрока
    if ((ui->lab_currentPlayerName->text()).isEmpty()) {
        ui->lab_currentPlayerName->setText(Player1->PlayerName);
    }
    else {
        //Если в поле имя первого игрока, тогда меняем его на второго
        if (ui->lab_currentPlayerName->text() == Player1->PlayerName) {
            ui->lab_currentPlayerName->setText(Player2->PlayerName);
        }
        else {
            ui->lab_currentPlayerName->setText(Player1->PlayerName);
        }
    }
}


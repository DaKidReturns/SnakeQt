#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

#include "snake.h"
#include "food.h"

class Playground : public QWidget
{
        Q_OBJECT
    public:
        explicit Playground(QWidget *parent = nullptr);

    signals:
        void kill();
        void ateFood();


    private:
        void paintEvent(QPaintEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;

        QPen *pen;
        QBrush *brush;
        QPoint snakePos;
        QSize size;
        int displacement;
        int direction;

        bool isStarted;
        bool isPaused;

        QPalette pal;

        QTimer *timer;

        Snake *snake;
        Food *food;

        enum movement {Up,Down,Left,Right};

        void move();

};
#endif

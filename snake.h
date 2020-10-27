#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QRect>

class Snake : public QObject
{
        Q_OBJECT
    public:
        explicit Snake(QObject *parent = nullptr,QPoint headPos=QPoint(30,30),QSize size=QSize(30,30),int length=3);


        void move(QPoint a);

        int x() {return body->front().x();} ;
        int y() {return body->front().y();} ;
        QVector<QRect>* getSnake(){return body;}

    signals:
        void dead();


    public slots:
        void grow();


    private:
        int length;
        QVector<QRect> *body;
        QPoint headPos;
        QSize size;
        bool bellyFull;

        void createBody();
        void updateHead();
        void checkCollition();


};

#endif // SNAKE_H

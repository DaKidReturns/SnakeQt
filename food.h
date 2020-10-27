#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QSize>
#include <QPoint>
#include <QVector>
#include <QRect>
#include <QDebug>
#include <cstdlib>
#include <vector>
#include <ctime>

class Food : public QObject
{
        Q_OBJECT
    public:
        //explicit Food(QObject *parent = nullptr);
        Food(QObject *parent,QSize winSize,QSize foodSize,QVector<QRect> *excl);

        QRect getHitBox(){return hitBox;}
        QPoint getFoodPosition() {return foodPosition;}
        void moveFood(QVector<QRect> *avoidRects);


    private:
        //QVector<QPoint> *exclution;
        QVector<QPoint> grid;

        QSize hitBoxSize;
        QRect hitBox;
        int foodRadius;

        //std::vector<int> *points;
        QPoint foodPosition;

        void createGrid(QSize winSize);

        int genarateRandom(int start, int end, std::vector<int> &excl);



    public slots:
        ; //this sets
};

#endif // FOOD_H

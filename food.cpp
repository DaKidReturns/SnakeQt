#include "food.h"

Food::Food(QObject *parent,QSize parentSize,QSize hitBoxSize,QVector<QRect> *excl) : QObject(parent)
{
    this->hitBoxSize = hitBoxSize;
    this->foodRadius = hitBoxSize.width()/2;

    createGrid(parentSize);

    std::srand(std::time(NULL));
    this->moveFood(excl);

}

void Food::createGrid(QSize parentSize)
{
    for(int i = 0;i<parentSize.height();i=i+hitBoxSize.height())
        for(int j = 0;j<parentSize.width();j=j+hitBoxSize.width())
            grid.push_back(QPoint(i,j));
}



void Food::moveFood(QVector<QRect> *avoidRects)
{
    QVector<QPoint> exclutionPoints;
    std::vector<int> points;
    points.clear();
    for(auto r = avoidRects->cbegin();r!=avoidRects->cend();++r)
    {
        exclutionPoints.push_back(r->topLeft());
    }

    for(auto i = grid.cbegin();i!=grid.cend();++i)
        for(auto j = exclutionPoints.cbegin();j!=exclutionPoints.cend();++j)
            if(*i==*j)
                points.push_back(grid.indexOf(*i));


    int index = genarateRandom(0,grid.length(),points);
    foodPosition = grid[index];
    hitBox = QRect(foodPosition,hitBoxSize);
    //delete exclutionPoints;
}



int Food::genarateRandom(int start, int end, std::vector<int> &excl)
{
    int max = end - start +1 - excl.size();
    std::sort(excl.begin(),excl.end());

    int random = std::rand()%max + start;
    for (unsigned int x =0; x<excl.size(); x++)
    {
        if(random<excl[x])
        {
            break;
        }
        random++;
    }
    return random;
}

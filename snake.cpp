#include "snake.h"

Snake::Snake(QObject *parent, QPoint headPos, QSize size, int length) : QObject(parent)
{
    this->length=length;
    this->headPos = headPos;
    this->size=size;
    createBody();
   this->bellyFull = false;
}

void Snake::createBody()
{
    this->body = new QVector<QRect>;
    for(int i = 0;i<length;i++)
        this->body->append(QRect(QPoint(headPos.x()+i*this->size.width(),headPos.y()),size));
}


void Snake::move(QPoint a)
{
    QRect head = QRect(a,size);

    if(!bellyFull)
        body->pop_back();
    else
    {
        this->length +=1;
        bellyFull =false;
    }

    body->push_front(head);
    updateHead();
    checkCollition();
}

void Snake::updateHead()
{
    headPos = this->body->at(0).topRight();
}

void Snake::checkCollition()
{
    //QRect head = body->at(0);
    for(auto i = body->cbegin()+1;i!=body->cend();++i)
    {
        if(body->at(0).intersects(*i))
            emit dead();
    }
}

void Snake::grow()
{
    this->bellyFull = true;
}

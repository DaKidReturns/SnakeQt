#include "playground.h"

Playground::Playground(QWidget *parent) : QWidget(parent)
{

    this->setMaximumSize(QSize(600,600));

    setMinimumWidth(600);
    setMinimumHeight(600);

    this->pal = palette();
    pal.setColor(QPalette::Background,QColor(125,118,170));

    this->setAutoFillBackground(true);
    this->setPalette(pal);


    this->pen = new QPen;
    this->pen->setColor(Qt::black);
    this->pen->setWidth(2);
    this->pen->setStyle(Qt::SolidLine);
    this->pen->setCapStyle(Qt::SquareCap);
    this->pen->setJoinStyle(Qt::RoundJoin);

    this->brush = new QBrush;
    this->brush->setColor(Qt::black);
    this->brush->setStyle(Qt::CrossPattern);

    this->snakePos = QPoint(width()/2-20,height()/2-20);
    this->size = QSize(20,20);

    this->snake = new Snake(this,snakePos,size,3);
    this->food = new Food(this,this->maximumSize(),size,snake->getSnake());

    this->displacement = 20;
    this->direction = Left;

    this->isStarted=false;
    this->isPaused=false;


    this->timer = new QTimer(this);
    connect(this->timer,&QTimer::timeout,this,&Playground::move);
    connect(this->snake,&Snake::dead,this,&emit Playground::kill);

    connect(this,&Playground::ateFood,this->snake,&Snake::grow);

}

void Playground::paintEvent(QPaintEvent *)
 {
     QVector<QRect> *s =  snake->getSnake();
     /*QPainterPath path;
     path.moveTo(20, 80);
     path.lineTo(20, 30);*/

     QPainter painter(this);
     painter.setPen(*pen);
     painter.setBrush(*brush);

     for(auto rect = s->begin();rect!=s->end();++rect)
        painter.drawRect(*rect);


     painter.drawEllipse(food->getHitBox());


 }

void Playground::move() //run this funciton when the timer times out
{
    if(isPaused!=true)
    {
        switch (this->direction)
        {
            case Up:
                       if(snake->y()>0)
                            snakePos-=QPoint(0,displacement);
                        else
                            snakePos.setY(this->height()-size.height());
                        break;

            case Down:
                        if(snake->y()+size.height()<this->height())
                            snakePos+=QPoint(0,displacement);
                        else
                            snakePos.setY(0);
                        break;

            case Right:
                        if(snake->x()+size.width()<this->width())
                            snakePos+=QPoint(displacement,0);
                        else
                            snakePos.setX(0);
                        break;
            case Left:
                        if(snake->x()>0)
                             snakePos-=QPoint(displacement,0);
                         else
                             snakePos.setX(this->width()-size.width());
                         break;

                        break;
        }
         if(snakePos == food->getFoodPosition())
        {
            emit ateFood();
            food->moveFood(snake->getSnake());
        }
        snake->move(snakePos);
        update();
    }
}


void Playground::keyPressEvent(QKeyEvent *event)
{
   switch(event->key())
   {
        case Qt::Key_Up:
                if(!isPaused)
                {
                    if(direction !=Up && direction !=Down)
                        direction = Up;
                }
                break;
        case Qt::Key_Down:
                if(!isPaused)
               if(direction !=Up && direction !=Down)
                    direction = Down;
               break;
        case Qt::Key_Left:
                if(!isPaused)
                {
                    if(direction !=Left && direction !=Right)
                        direction = Left;
                }
               break;
        case Qt::Key_Right:
                if(!isPaused)
                {
                    if(direction !=Left && direction !=Right)
                        direction = Right;
                }
                break;
        case Qt::Key_Space:
               isPaused=(isPaused==true?false:true);
               if (isStarted == false){
                    isStarted = true;
                    timer->start(80);  //call the timeout funtion evety 100 milliseconds
               }
               break;

        case Qt::Key_Q:
                emit kill();
                this->close();
                break;
   }

}

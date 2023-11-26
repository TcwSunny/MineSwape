#include "Block.h"

#include <QFont>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

Block::Block(int x, int y):Count(0),status(Status::Close)
{
    setRect(0,0,20,20);
    setPos(2+22*x,42+22*y);
    Bomb = false;
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit Left(this);
        update();
    }
    if (event->button() == Qt::RightButton) {
        emit Right(this);
        update();
    }
    QGraphicsRectItem::mousePressEvent(event);
}
void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);

    if (status == Status::Open) {
        if(Bomb == false){
            QFont font;
            font.setPixelSize(20);
            painter->setFont(font);
            painter->setPen(Qt::white);
            painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(Count));
        }
    }
}

Block::Status Block::getStatus() const
{
    return status;
}

void Block::setStatus(Status newStatus)
{
    status = newStatus;
}

int Block::getX() const
{
    return X;
}

void Block::setX(int newX)
{
    X = newX;
}

int Block::getY() const
{
    return Y;
}

void Block::setY(int newY)
{
    Y = newY;
}

bool Block::hasBomb() const
{
    return Bomb;
}

void Block::setBomb(bool value)
{
    Bomb = value;
}

int Block::getCount() const
{
    return Count;
}

void Block::setCount(int value)
{
    Count = value;
}

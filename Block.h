#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QGraphicsRectItem>

class Block : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    enum Status{
        Open, Close, Flag
    };
    explicit Block(int x, int y);

    bool hasBomb() const;
    void setBomb(bool value);

    int getCount() const;
    void setCount(int value);

    int getY() const;
    void setY(int newY);

    int getX() const;
    void setX(int newX);

    Block::Status getStatus() const;
    void setStatus(Status newStatus);

signals:
    void Left(Block* block);
    void Right(Block* block);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Status status;
    bool Bomb;
    int Count;
    int Y;
    int X;
};


#endif // BLOCK_H

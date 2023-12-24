// ClickableTextItem.h

#ifndef CLICKABLETEXTITEM_H
#define CLICKABLETEXTITEM_H

#include <QGraphicsTextItem>

class ClickableTextItem : public QGraphicsTextItem {
    Q_OBJECT

public:
    ClickableTextItem(QGraphicsItem *parent = nullptr); // 加入這個建構函式的聲明

signals:
    void textClicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CLICKABLETEXTITEM_H

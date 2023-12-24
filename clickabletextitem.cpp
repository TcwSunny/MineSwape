#include "ClickableTextItem.h"

ClickableTextItem::ClickableTextItem(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    // 構造函式的實作
}

void ClickableTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // mousePressEvent 的實作
    emit textClicked();
    // 其他處理...
}

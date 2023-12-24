#ifndef SCENE_H
#define SCENE_H
#include "Block.h"
#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void setAllBomb(int BombCount);
    int countSurroundingBombs(int x, int y) const;
    void openSurroundingBlocks(int x, int y);
public slots:
    void LeftMouse(Block *clickedBlock);
    void RightMouse(Block *clickedBlock);
    void resetGame();
signals:

private:
    Block *block[10][10];


};

#endif // SCENE_H

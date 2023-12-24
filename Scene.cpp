#include "Scene.h"
#include <ClickableTextItem.h>
#include <QRandomGenerator>

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    ClickableTextItem *clickableText = new ClickableTextItem();
    clickableText->setPos(70,0); // Adjust the position as needed
    QFont font;
    font.setPointSize(20);  // Set the font size to 16
    font.setBold(true);
    clickableText->setFont(font);
    QColor textColor(Qt::black); // Example: White text color
    clickableText->setDefaultTextColor(textColor);
    QString TextStr = QString("Start");
    clickableText->setPlainText(TextStr);
    addItem(clickableText);
    connect(clickableText, &ClickableTextItem::textClicked, this, &Scene::resetGame);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            block[i][j] = new Block(i , j);
            block[i][j]->setX(i);
            block[i][j]->setY(j);
            addItem(block[i][j]);
            connect(block[i][j], &Block::Left, this, &Scene::LeftMouse);
            connect(block[i][j], &Block::Right, this, &Scene::RightMouse);
        }
    }
    setAllBomb(10);
    connect(clickableText, &ClickableTextItem::textClicked, this, &Scene::resetGame);
}

void Scene::setAllBomb(int BombCount)
{
    QRandomGenerator *rand = QRandomGenerator::global();

    // 創建地雷
    while (BombCount > 0) {
        int i = rand->bounded(10);
        int j = rand->bounded(10);
        if (block[i][j]->hasBomb() == false) {
            block[i][j]->setBomb(true);
            BombCount--;
        }
    }

    // 設定每個方塊的 Count
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            int count = countSurroundingBombs(i, j);
            block[i][j]->setCount(count);
        }
    }
}

int Scene::countSurroundingBombs(int x, int y) const
{
    int count = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;

            if (newX >= 0 && newX < 10 && newY >= 0 && newY < 10) {
                if (block[newX][newY]->hasBomb()) {
                    count++;
                }
            }
        }
    }

    return count;
}

void Scene::LeftMouse(Block *clickedBlock)
{
    if (clickedBlock->getStatus() == Block::Status::Close) {
        clickedBlock->setStatus(Block::Status::Open);
        if (!clickedBlock->hasBomb()) {
            QBrush newBrush(Qt::green);
            clickedBlock->setBrush(newBrush);
            clickedBlock->update();

            if (clickedBlock->getCount() == 0) {
                int x = clickedBlock->getX();
                int y = clickedBlock->getY();
                openSurroundingBlocks(x, y);
            }
        } else {
            QBrush newBrush(Qt::red);
            clickedBlock->setBrush(newBrush);
            clickedBlock->update();
        }
    }
}

void Scene::RightMouse(Block *clickedBlock)
{
    if (clickedBlock->getStatus() == Block::Status::Close){
        clickedBlock->setStatus(Block::Status::Flag);
        QBrush newBrush(Qt::yellow);
        clickedBlock->setBrush(newBrush);
        clickedBlock->update();
    }else if(clickedBlock->getStatus() == Block::Status::Flag){
        clickedBlock->setStatus(Block::Status::Close);
        QBrush newBrush(Qt::white);
        clickedBlock->setBrush(newBrush);
        clickedBlock->update();
    }
}

void Scene::resetGame()
{
    clear();

    ClickableTextItem *clickableText = new ClickableTextItem();
    clickableText->setPos(70,0); // Adjust the position as needed
    QFont font;
    font.setPointSize(20);  // Set the font size to 16
    font.setBold(true);
    clickableText->setFont(font);
    QColor textColor(Qt::black); // Example: White text color
    clickableText->setDefaultTextColor(textColor);
    QString TextStr = QString("Start");
    clickableText->setPlainText(TextStr);
    addItem(clickableText);
    connect(clickableText, &ClickableTextItem::textClicked, this, &Scene::resetGame);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            block[i][j] = new Block(i , j);
            block[i][j]->setX(i);
            block[i][j]->setY(j);
            addItem(block[i][j]);
            connect(block[i][j], &Block::Left, this, &Scene::LeftMouse);
            connect(block[i][j], &Block::Right, this, &Scene::RightMouse);
        }
    }
    setAllBomb(10);
    connect(clickableText, &ClickableTextItem::textClicked, this, &Scene::resetGame);
}


void Scene::openSurroundingBlocks(int x, int y)
{
    // 檢查周圍的 8 個方向
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;

            // 確保新的座標在合法範圍內
            if (newX >= 0 && newX < 10 && newY >= 0 && newY < 10) {
                Block* currentBlock = block[newX][newY];
                if (currentBlock->getStatus()==Block::Status::Close && !currentBlock->hasBomb()) {
                    // 點開未點開的方塊
                    LeftMouse(currentBlock);
                }
            }
        }
    }
}


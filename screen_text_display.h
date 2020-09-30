#pragma once

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "utilities.h"

class ScreenTextDisplay : public QGraphicsItem
{
public:
    ScreenTextDisplay();
    void SetScore(int score) {m_Score = score;}
    void SetGameResult(GameResult gameResult) {m_GameResult = gameResult;}

private:
    const int WIDTH = 600;
    const int HEIGHT = 200;
    const int X = 614 / 2 - WIDTH / 2;
    const int Y = 714 / 2 - HEIGHT / 2;
    const int POINT_SIZE = 30;

    GameResult m_GameResult;
    int m_Score;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

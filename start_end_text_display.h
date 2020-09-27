#pragma once

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class StartEndTextDisplay : public QGraphicsItem
{
public:
    StartEndTextDisplay();
    void SetScore(int score);
    void SetGameWon(bool gameWon);
    void SetGameLost(bool gameLost);

private:
    bool m_GameWon;
    bool m_GameLost;
    bool m_Playing;
    int m_Score;

    const int WIDTH = 600;
    const int HEIGHT = 200;
    const int X = 614 / 2 - WIDTH / 2;
    const int Y = 714 / 2 - HEIGHT / 2;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

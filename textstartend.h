#ifndef TEXTSTARTEND_H
#define TEXTSTARTEND_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class TextStartEnd : public QGraphicsItem
{
public:
    TextStartEnd();
    void SetScore(int score);
    void SetGameWon(bool gameWon);
    void SetGameLost(bool gameLost);
    bool m_GameWon, m_GameLost, m_Playing;
    int m_Score;
    int m_X, m_Y, m_W, m_H;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TEXTSTARTEND_H

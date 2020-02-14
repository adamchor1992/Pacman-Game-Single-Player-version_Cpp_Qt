#ifndef STARTENDTEXTDISPLAY_H
#define STARTENDTEXTDISPLAY_H

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
    bool m_GameWon, m_GameLost, m_Playing;
    int m_Score;
    int m_X, m_Y, m_Width, m_Height;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // STARTENDTEXTDISPLAY_H

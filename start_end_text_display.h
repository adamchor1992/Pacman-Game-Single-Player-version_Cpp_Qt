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

private:
    bool m_GameWon;
    bool m_GameLost;
    bool m_Playing;
    int m_Score;
    int m_X;
    int m_Y;
    int m_Width;
    int m_Height;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // STARTENDTEXTDISPLAY_H

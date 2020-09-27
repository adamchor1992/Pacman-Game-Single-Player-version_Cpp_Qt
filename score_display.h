#pragma once

#include <QGraphicsItem>

class ScoreDisplay : public QGraphicsItem
{
public:
    ScoreDisplay();
    void SetScore(int score);
    void IncreaseScore(int score){m_Score += score;}
    void ResetScore(){m_Score = 0;}
    int GetScore() {return m_Score;}

private:
    const int X = 0;
    const int Y = 680;
    const int WIDTH = 600;
    const int HEIGHT = 200;
    const int POINT_SIZE = 30;

    int m_Score;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

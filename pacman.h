#pragma once

#include <QGraphicsItem>
#include "utilities.h"

class Pacman : public QGraphicsItem
{
public:
    static int GetX() {return m_X;}
    static int GetY() {return m_Y;}

    Pacman();
    void Reset();
    void AdvanceAnimation();
    void SetNextDirection(Direction direction);
    Direction GetNextDirection() const {return m_NextDirection;}
    void Move();

private:
    static const int STARTING_X = 320;
    static const int STARTING_Y = 514;
    static int m_X;
    static int m_Y;

    const int DIAMETER = 30;
    const int OFFSET_X = -15;
    const int OFFSET_Y = -15;

    QPixmap m_Left1Pixmap, m_Left2Pixmap, m_Left3Pixmap, m_Left4Pixmap;
    QPixmap m_Up1Pixmap, m_Up2Pixmap, m_Up3Pixmap, m_Up4Pixmap;
    QPixmap m_Down1Pixmap, m_Down2Pixmap, m_Down3Pixmap, m_Down4Pixmap;
    QPixmap m_Right1Pixmap, m_Right2Pixmap, m_Right3Pixmap, m_Right4Pixmap;

    int m_AnimationState;
    int m_AnimationModifyFactor;

    Direction m_Direction;
    Direction m_NextDirection;

    void LoadImages();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

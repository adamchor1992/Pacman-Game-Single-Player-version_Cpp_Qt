#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsItem>
#include "utilities.h"

class Pacman : public QGraphicsItem
{
public:
    static int GetPacX() {return m_PacX;}
    static int GetPacY() {return m_PacY;}

    Pacman();
    void Reset();
    void AdvanceAnimation();
    void SetNextDirection(Direction direction);
    Direction GetNextDirection() const {return m_NextDirection;}
    void Move();

private:
    static int const STARTING_X = 320;
    static int const STARTING_Y = 514;
    static int m_PacX;
    static int m_PacY;

    QPixmap m_PacmanPixmap;
    QPixmap m_Left1, m_Left2, m_Left3, m_Left4;
    QPixmap m_Up1, m_Up2, m_Up3, m_Up4;
    QPixmap m_Down1, m_Down2, m_Down3, m_Down4;
    QPixmap m_Right1, m_Right2, m_Right3, m_Right4;

    int m_AnimationState;
    int m_AnimationModifyFactor;

    Direction m_Direction;
    Direction m_NextDirection;

    void LoadPacmanImages();
    void SetPacX(int);
    void SetPacY(int);
    void SetDirection(Direction direction);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // PACMAN_H

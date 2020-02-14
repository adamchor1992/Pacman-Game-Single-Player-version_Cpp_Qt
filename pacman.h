#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsItem>

class Pacman : public QGraphicsItem
{
public:
    Pacman();
    void LoadPacmanImages();
    void Advance();
    void SetPacX(int);
    void SetPacY(int);
    void SetDirection(int dir);
    void SetNextDirection(int dir);
    static int GetPacX() {return m_PacX;}
    static int GetPacY() {return m_PacY;}
    int GetDirection() {return m_Direction;}
    int GetNextDirection() {return m_NextDirection;}

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    static int m_PacX;
    static int m_PacY;
    int m_Direction;
    int m_NextDirection;
    int m_AnimeState;
    int m_AnimationModifyFactor;

    QPixmap m_PacmanPixmap;

    QPixmap m_Left1, m_Left2, m_Left3, m_Left4;
    QPixmap m_Up1, m_Up2, m_Up3, m_Up4;
    QPixmap m_Down1, m_Down2, m_Down3, m_Down4;
    QPixmap m_Right1, m_Right2, m_Right3, m_Right4;
};

#endif // PACMAN_H

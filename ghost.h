#ifndef GHOST_H
#define GHOST_H
#include <QGraphicsItem>
#include <QPainter>

class Ghost : public QGraphicsItem
{
public:
    Ghost();
    void LoadGhostImages();
    void Advance();
    void SetGhostX(int);
    void SetGhostY(int);
    void SetIsScared(bool option) {m_IsScared=option;}
    void SetScaredWhite(bool option) {m_ScaredWhite=option;}
    void SetGhostDirection(int dir) {m_GhostDirection=dir;}
    void SetNextGhostDirection(int dir) {m_NextGhostDirection=dir;}
    void SetGhostColor(QString col);
    int GetGhostX() {return m_GhostX;}
    int GetGhostY() {return m_GhostY;}
    int GetGhostDirection() {return m_GhostDirection;}
    int GetNextGhostDirection() {return m_NextGhostDirection;}
    bool GetIsScared() {return m_IsScared;}
    bool GetScaredWhite() {return m_ScaredWhite;}

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap m_GhostPixmap;
    QPixmap m_GhostScaredBlue;
    QPixmap m_GhostScaredWhite;

    QPixmap m_Left1, m_Left2;
    QPixmap m_Up1, m_Up2;
    QPixmap m_Down1, m_Down2;
    QPixmap m_Right1, m_Right2;
    QPixmap m_ScaredBlue, m_ScaredBlue1;
    QPixmap m_ScaredWhitePix, m_ScaredWhite1;

    bool m_IsScared;
    bool m_ScaredWhite;
    bool m_Hidden;

    int m_AnimeState;
    int m_AnimationModifyFactor;

    int m_GhostX, m_GhostY;
    int m_GhostDirection;
    int m_NextGhostDirection;
};

#endif // GHOST_H

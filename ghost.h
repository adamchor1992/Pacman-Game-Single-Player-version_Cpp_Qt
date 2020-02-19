#ifndef GHOST_H
#define GHOST_H
#include <QGraphicsItem>
#include <QPainter>

#include "utilities.h"

class Ghost : public QGraphicsItem
{
public:
    static int const STARTING_X = 307;
    static int const STARTING_Y = 318;

    static int GetAllGhostsScareState(){return m_AllGhostsScaredState;}
    static bool GetAllGhostsScared(){return m_AllGhostScared;}
    static void SetAllGhostsScared(bool allGhostsScared){m_AllGhostScared = allGhostsScared;}
    static bool GetAllGhostsStartedFreeMovement(){return m_AllGhostsStartedFreeMovement;}
    static void SetAllGhostsStartedFreeMovement(bool allGhostsStartedFreeMovement){m_AllGhostsStartedFreeMovement = allGhostsStartedFreeMovement;}
    static int GetGhostsStartTimer(){return m_GhostsStartTimer;}
    static void IncrementGhostsStartTimer(){++m_GhostsStartTimer;}
    static void IncrementAllGhostsScareState(){++m_AllGhostsScaredState;}
    static void SetAllGhostsScareState(int scareState){m_AllGhostsScaredState=scareState;}

    Ghost();
    void Reset();
    void Respawn();
    void SetIsScared(bool option) {m_IsScared=option;}
    void SetScaredWhite(bool option) {m_ScaredWhite=option;}
    bool GetIsScared() const {return m_IsScared;}
    void AdvanceAnimation();
    bool GetGhostStartedFreeMovement() const {return m_GhostStartedFreeMovement;}
    int GetGhostX() const {return m_GhostX;}
    int GetGhostY() const {return m_GhostY;}
    void Move();
    void MoveOutOfTheStartingBox(int ghostX, int ghostY);
    void MoveInStartingRect();

private:
    static int m_GhostNumber;
    static int m_AllGhostsScaredState;
    static bool m_AllGhostScared;
    static bool m_AllGhostsStartedFreeMovement;
    static int m_GhostsStartTimer;

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
    bool m_GhostMoving;
    bool m_GhostStartedFreeMovement;

    int m_AnimationState;
    int m_AnimationModifyFactor;
    int m_GhostX;
    int m_GhostY;

    Direction m_GhostDirection;
    Direction m_NextGhostDirection;

    void LoadGhostImages();
    void SetGhostColor(const QString& col);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // GHOST_H

#pragma once

#include <QGraphicsItem>
#include <QPainter>

#include "utilities.h"

class Ghost : public QGraphicsItem
{
public:
    static const int WHITE_SCARE_STATE_THRESHOLD = 750;
    static const int SCARE_STATE_TIMER_MAX = 1000;

    enum class ScaredState
    {
        NO_SCARED,
        SCARED_BLUE,
        SCARED_WHITE
    };

    static int GetAllGhostsScareState(){return m_AllGhostsScaredState;}
    static bool GetAllGhostsStartedFreeMovement(){return m_AllGhostsStartedFreeMovement;}
    static void SetAllGhostsStartedFreeMovement(bool allGhostsStartedFreeMovement){m_AllGhostsStartedFreeMovement = allGhostsStartedFreeMovement;}
    static int GetGhostsStartTimer(){return m_GhostsStartTimer;}
    static void IncrementGhostsStartTimer(){++m_GhostsStartTimer;}
    static void IncrementAllGhostsScareState(){++m_AllGhostsScaredState;}
    static void SetAllGhostsScareState(int scareState){m_AllGhostsScaredState=scareState;}

    Ghost();
    void Reset();
    void Respawn();
    void SetScaredState(ScaredState scaredState) {m_ScaredState = scaredState;}
    ScaredState GetScaredState() const {return m_ScaredState;}
    void AdvanceAnimation();
    bool GetGhostStartedFreeMovement() const {return m_GhostStartedFreeMovement;}
    int GetX() const {return m_X;}
    int GetY() const {return m_Y;}
    void Move();
    void MoveOutOfTheStartingBox(int ghostX, int ghostY);
    void MoveInStartingRect();

private:
    static const int STARTING_X = 307;
    static const int STARTING_Y = 318;

    static int m_GhostNumber;
    static int m_AllGhostsScaredState;
    static bool m_AllGhostsStartedFreeMovement;
    static int m_GhostsStartTimer;

    QPixmap m_Left1Pixmap, m_Left2Pixmap, m_Up1Pixmap, m_Up2Pixmap, m_Down1Pixmap, m_Down2Pixmap, m_Right1Pixmap, m_Right2Pixmap;
    QPixmap m_ScaredBlue1Pixmap, m_ScaredBlue2Pixmap;
    QPixmap m_ScaredWhite1Pixmap, m_ScaredWhite2Pixmap;

    bool m_GhostMoving;
    bool m_GhostStartedFreeMovement;

    int m_AnimationState;
    int m_AnimationModifyFactor;
    int m_X;
    int m_Y;

    Direction m_Direction;
    Direction m_NextDirection;

    ScaredState m_ScaredState;

    void LoadImages();
    void SetColor(const QString& col);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

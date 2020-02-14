#ifndef GHOST_H
#define GHOST_H
#include <QGraphicsItem>
#include <QPainter>

class Ghost : public QGraphicsItem
{
public:
    Ghost();
    void Reset();
    void LoadGhostImages();
    void AdvanceAnimation();
    void SetGhostX(int x){m_GhostX=x;}
    void SetGhostY(int y){m_GhostY=y;}
    void SetGhostStart(bool ghostStart) {m_GhostStart=ghostStart;}
    void SetIsScared(bool option) {m_IsScared=option;}
    void SetScaredWhite(bool option) {m_ScaredWhite=option;}
    void SetGhostDirection(int dir) {m_GhostDirection=dir;}
    void SetNextGhostDirection(int dir) {m_NextGhostDirection=dir;}
    void SetGhostColor(QString col);
    int GetGhostX() const {return m_GhostX;}
    int GetGhostY() const {return m_GhostY;}
    int GetGhostDirection() const {return m_GhostDirection;}
    int GetNextGhostDirection() const {return m_NextGhostDirection;}
    bool GetIsScared() const {return m_IsScared;}
    bool GetScaredWhite() const {return m_ScaredWhite;}
    bool GetGhostStart() const {return m_GhostStart;}
    void Move();
    void MoveInStartingRect();

    static int GetAllGhostsScareState(){return m_AllGhostsScaredState;}
    static bool GetAllGhostsScared(){return m_AllGhostScared;}
    static void SetAllGhostsScared(bool allGhostsScared){m_AllGhostScared = allGhostsScared;}
    static bool GetAllGhostsStarted(){return m_AllGhostsStarted;}
    static void SetAllGhostsStarted(bool allGhostsStarted){m_AllGhostsStarted = allGhostsStarted;}
    static int GetGhostsStartTimer(){return m_GhostsStartTimer;}
    static void IncrementGhostsStartTimer(){++m_GhostsStartTimer;}
    static void IncrementAllGhostsScareState(){++m_AllGhostsScaredState;}
    static void SetAllGhostsScareState(int scareState){m_AllGhostsScaredState=scareState;}

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
    bool m_GhostMoving;
    bool m_GhostStart;
    int m_AnimeState;
    int m_AnimationModifyFactor;
    int m_GhostX, m_GhostY;
    int m_GhostDirection;
    int m_NextGhostDirection;

    static int m_AllGhostsScaredState;
    static bool m_AllGhostScared;
    static bool m_AllGhostsStarted;
    static int m_GhostsStartTimer;
};

#endif // GHOST_H

#ifndef GHOST_H
#define GHOST_H
#include <QGraphicsItem>
#include <QPainter>

class Ghost : public QGraphicsItem
{
    /*Forward declaration*/
    enum class Direction;

public:
    Ghost();
    void Reset();
    void LoadGhostImages();
    void AdvanceAnimation();
    void SetGhostX(int x){m_GhostX=x;}
    void SetGhostY(int y){m_GhostY=y;}
    void SetGhostStarted(bool ghostStarted) {m_GhostStarted=ghostStarted;}
    void SetIsScared(bool option) {m_IsScared=option;}
    void SetScaredWhite(bool option) {m_ScaredWhite=option;}
    void SetGhostDirection(Direction direction) {m_GhostDirection=direction;}
    void SetNextGhostDirection(Direction direction) {m_NextGhostDirection=direction;}
    void SetGhostColor(QString col);
    int GetGhostX() const {return m_GhostX;}
    int GetGhostY() const {return m_GhostY;}
    QPoint GetGhostPosition() const {return QPoint(m_GhostX, m_GhostY);}
    void IncrementGhostX(){++m_GhostX;}
    void IncrementGhostY(){++m_GhostY;}
    void DecrementGhostX(){--m_GhostX;}
    void DecrementGhostY(){--m_GhostY;}
    Direction GetGhostDirection() const {return m_GhostDirection;}
    Direction GetNextGhostDirection() const {return m_NextGhostDirection;}
    bool GetIsScared() const {return m_IsScared;}
    bool GetScaredWhite() const {return m_ScaredWhite;}
    bool GetGhostStarted() const {return m_GhostStarted;}
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
    bool m_GhostStarted;
    int m_AnimeState;
    int m_AnimationModifyFactor;
    int m_GhostX, m_GhostY;

    enum class Direction
    {
        none=0,
        left=1,
        up=2,
        down=3,
        right=4
    };

    Direction m_GhostDirection;
    Direction m_NextGhostDirection;

    static int m_AllGhostsScaredState;
    static bool m_AllGhostScared;
    static bool m_AllGhostsStarted;
    static int m_GhostsStartTimer;
};

#endif // GHOST_H

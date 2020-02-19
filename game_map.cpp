#include "game_map.h"
#include <array>

QVector<QPoint> GameMap::m_PathPoints;

GameMap::GameMap()
{
    LoadMapImage();

    //HORIZONTAL LINES
    //LINE 1
    CreatePathPoints(35, 35, 274, 35);
    CreatePathPoints(340, 35, 579, 35);

    //LINE 2
    CreatePathPoints(35, 121, 579, 121);

    //LINE 3
    CreatePathPoints(35, 187, 144, 187);
    CreatePathPoints(209, 187, 274, 187);
    CreatePathPoints(340, 187, 406, 187);
    CreatePathPoints(470, 187, 579, 187);

    //LINE 4
    CreatePathPoints(209, 252, 406, 252);

    //LINE 5 - MIDDLE LINE
    CreatePathPoints(0, 318, 209, 318);
    CreatePathPoints(406, 318, 614, 318);

    //LINE 6
    CreatePathPoints(209, 384,406, 384);

    //LINE 7
    CreatePathPoints(35, 449, 274, 449);
    CreatePathPoints(340, 449, 579, 449);

    //LINE 8
    CreatePathPoints(35, 514, 79, 514);
    CreatePathPoints(144, 514, 470, 514);
    CreatePathPoints(536, 514, 579, 514);

    //LINE 9
    CreatePathPoints(35, 580, 144, 580);
    CreatePathPoints(209, 580, 274, 580);
    CreatePathPoints(340, 580, 406, 580);
    CreatePathPoints(470, 580, 579, 580);

    //LINE 10
    CreatePathPoints(35, 645, 579, 645);

    //VERTICAL LINES
    //LINE 1
    CreatePathPoints(35, 35, 35, 187);
    CreatePathPoints(35, 449, 35, 514);
    CreatePathPoints(35, 580, 35, 645);

    //LINE 2
    CreatePathPoints(79, 514, 79, 580);

    //LINE 3
    CreatePathPoints(144, 35, 144, 580);

    //LINE 4
    CreatePathPoints(209, 121, 209, 187);
    CreatePathPoints(209, 252, 209, 449);
    CreatePathPoints(209, 514, 209, 580);

    //LINE 5
    CreatePathPoints(274, 35, 274, 121);
    CreatePathPoints(274, 187, 274, 252);
    CreatePathPoints(274, 449, 274, 514);
    CreatePathPoints(274, 580, 274, 645);

    //LINE 6
    CreatePathPoints(340, 35, 340, 121);
    CreatePathPoints(340, 187, 340, 252);
    CreatePathPoints(340, 449, 340, 514);
    CreatePathPoints(340, 580, 340, 645);

    //LINE 7
    CreatePathPoints(406, 121, 406, 187);
    CreatePathPoints(406, 252, 406, 449);
    CreatePathPoints(406, 514, 406, 580);

    //LINE 8
    CreatePathPoints(470, 35, 470, 580);

    //LINE 9
    CreatePathPoints(536, 514, 536, 580);

    //LINE 10
    CreatePathPoints(579, 35, 579, 187);
    CreatePathPoints(579, 449, 579, 514);
    CreatePathPoints(579, 580, 579, 645);

    CreateFoodballPositionsVector();
    CreatePowerballPositionsVector();
}

void GameMap::LoadMapImage()
{
    m_MapBackgroundPixmap.load(":/images/map.png");
}

void GameMap::CreatePathPoints(int startX, int startY, int endX, int endY) //only left-right and up-down lines
{
    QPoint p;

    if (startX == endX) //vertical line condition
    {
        if (startY < endY) //vertical line from startY to endY
        {
            for (int y=startY; y<=endY; y++)
            {
                p.setX(startX);
                p.setY(y);
                if (! m_PathPoints.contains(p))
                {
                    m_PathPoints.push_front(p);
                }
            }
        }

        else if(startY==endY) //single point
        {
                p.setX(startX);
                p.setY(startY);
                if (! m_PathPoints.contains(p))
                {
                    m_PathPoints.push_front(p);
                }
        }
    }

    if (startY == endY) //horizontal line condition
    {
        if (startX < endX) //horizontal line from startX to endX
        {
            for (int x=startX; x<=endX; x++)
            {
                p.setX(x);
                p.setY(startY);
                if (! m_PathPoints.contains(p))
                {
                    m_PathPoints.push_front(p);
                }
            }
        }
        else //single point
        {
                p.setX(startX);
                p.setY(startY);
                if (! m_PathPoints.contains(p))
                {
                    m_PathPoints.push_front(p);
                }
        }
    }
}

/*Checks if given point is accessible for Pacman (is present in m_PacmanPaths vector)*/
bool GameMap::IsPointAvailable(QPoint const& point)
{
    for(auto m_PathPoint : m_PathPoints)
    {
        if(m_PathPoint==point)
        {
             return true;
        }
    }
    return false;
}

void GameMap::CreateFoodballPositionsVector()
{
    int const COORDINATES_COUNT = 10;

    /*Coordinates (x,y) where foodballs will be placed*/
    std::array<int, COORDINATES_COUNT> verticalLinesXCoordinates={35,79,144,209,274,340,406,470,536,579};
    std::array<int, COORDINATES_COUNT> horizontalLinesYCoordinates={35,121,187,252,318,384,449,514,580,645};

    for(int i : verticalLinesXCoordinates)
    {
        for(int j : horizontalLinesYCoordinates)
        {
            QPoint foodballPoint(i,j);

            /*Check if point is on path*/
            if(GameMap::GetPathPoints().contains(foodballPoint))
            {
                /*Skip points where powerballs are*/
                if((foodballPoint.x()==35 && foodballPoint.y()==75) ||
                        (foodballPoint.x()==579 && foodballPoint.y()==75) ||
                        (foodballPoint.x()==35 && foodballPoint.y()==514) ||
                        (foodballPoint.x()==579 && foodballPoint.y()==514))
                {
                    continue;
                }

                /*Check if the point is already in the vector*/
                if(m_FoodballPositions.contains(foodballPoint))
                {
                    continue;
                }

                m_FoodballPositions.push_back(QPoint(i,j));
            }
        }
    }
}

void GameMap::CreatePowerballPositionsVector()
{
    QPoint powerball1Position = QPoint(35,75);
    QPoint powerball2Position = QPoint(579,75);
    QPoint powerball3Position = QPoint(35,514);
    QPoint powerball4Position = QPoint(579,514);

    m_PowerballPositions.push_back(powerball1Position);
    m_PowerballPositions.push_back(powerball2Position);
    m_PowerballPositions.push_back(powerball3Position);
    m_PowerballPositions.push_back(powerball4Position);
}


QRectF GameMap::boundingRect() const //sets map bounding rect which will be updated and redrawn every timer cycle
{
    return QRect(0,0,614,740);
}

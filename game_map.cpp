#include "game_map.h"
#include <array>

QVector<QPoint> GameMap::m_PathPoints;

GameMap::GameMap()
{
    //HORIZONTAL LINES
    //LINE 1
    GeneratePathPoints(35, 35, 274, 35);
    GeneratePathPoints(340, 35, 579, 35);

    //LINE 2
    GeneratePathPoints(35, 121, 579, 121);

    //LINE 3
    GeneratePathPoints(35, 187, 144, 187);
    GeneratePathPoints(209, 187, 274, 187);
    GeneratePathPoints(340, 187, 406, 187);
    GeneratePathPoints(470, 187, 579, 187);

    //LINE 4
    GeneratePathPoints(209, 252, 406, 252);

    //LINE 5 - MIDDLE LINE
    GeneratePathPoints(0, 318, 209, 318);
    GeneratePathPoints(406, 318, 614, 318);

    //LINE 6
    GeneratePathPoints(209, 384,406, 384);

    //LINE 7
    GeneratePathPoints(35, 449, 274, 449);
    GeneratePathPoints(340, 449, 579, 449);

    //LINE 8
    GeneratePathPoints(35, 514, 79, 514);
    GeneratePathPoints(144, 514, 470, 514);
    GeneratePathPoints(536, 514, 579, 514);

    //LINE 9
    GeneratePathPoints(35, 580, 144, 580);
    GeneratePathPoints(209, 580, 274, 580);
    GeneratePathPoints(340, 580, 406, 580);
    GeneratePathPoints(470, 580, 579, 580);

    //LINE 10
    GeneratePathPoints(35, 645, 579, 645);

    //VERTICAL LINES
    //LINE 1
    GeneratePathPoints(35, 35, 35, 187);
    GeneratePathPoints(35, 449, 35, 514);
    GeneratePathPoints(35, 580, 35, 645);

    //LINE 2
    GeneratePathPoints(79, 514, 79, 580);

    //LINE 3
    GeneratePathPoints(144, 35, 144, 580);

    //LINE 4
    GeneratePathPoints(209, 121, 209, 187);
    GeneratePathPoints(209, 252, 209, 449);
    GeneratePathPoints(209, 514, 209, 580);

    //LINE 5
    GeneratePathPoints(274, 35, 274, 121);
    GeneratePathPoints(274, 187, 274, 252);
    GeneratePathPoints(274, 449, 274, 514);
    GeneratePathPoints(274, 580, 274, 645);

    //LINE 6
    GeneratePathPoints(340, 35, 340, 121);
    GeneratePathPoints(340, 187, 340, 252);
    GeneratePathPoints(340, 449, 340, 514);
    GeneratePathPoints(340, 580, 340, 645);

    //LINE 7
    GeneratePathPoints(406, 121, 406, 187);
    GeneratePathPoints(406, 252, 406, 449);
    GeneratePathPoints(406, 514, 406, 580);

    //LINE 8
    GeneratePathPoints(470, 35, 470, 580);

    //LINE 9
    GeneratePathPoints(536, 514, 536, 580);

    //LINE 10
    GeneratePathPoints(579, 35, 579, 187);
    GeneratePathPoints(579, 449, 579, 514);
    GeneratePathPoints(579, 580, 579, 645);
}

void GameMap::GeneratePathPoints(int startX, int startY, int endX, int endY)
{
    QPoint point;

    /*Vertical line*/
    if (startX == endX)
    {
        /*Vertical line from startY to endY*/
        if (startY < endY)
        {
            for(int y = startY; y <= endY; y++)
            {
                point.setX(startX);
                point.setY(y);
                if(!m_PathPoints.contains(point))
                {
                    m_PathPoints.push_front(point);
                }
            }
        }
        /*Single point*/
        else if(startY == endY)
        {
            point.setX(startX);
            point.setY(startY);
            if (!m_PathPoints.contains(point))
            {
                m_PathPoints.push_front(point);
            }
        }
    }

    /*Horizontal line*/
    if (startY == endY)
    {
        /*Horizontal line from startX to endX*/
        if (startX < endX)
        {
            for(int x = startX; x <= endX; x++)
            {
                point.setX(x);
                point.setY(startY);
                if (! m_PathPoints.contains(point))
                {
                    m_PathPoints.push_front(point);
                }
            }
        }
        /*Single point*/
        else if(startX == endX)
        {
            point.setX(startX);
            point.setY(startY);
            if (!m_PathPoints.contains(point))
            {
                m_PathPoints.push_front(point);
            }
        }
    }
}

bool GameMap::IsPointAvailable(QPoint const& point)
{
    /*Check if given point is accessible for movable characters*/
    return m_PathPoints.contains(point);
}

QVector<QPoint> GameMap::GenerateFoodballPositions() const
{
    const int COORDINATES_COUNT = 10;

    /*Coordinates (x,y) where foodballs will be placed*/
    std::array<int, COORDINATES_COUNT> verticalLinesXCoordinates={35, 79, 144, 209, 274, 340, 406, 470, 536, 579};
    std::array<int, COORDINATES_COUNT> horizontalLinesYCoordinates={35, 121, 187, 252, 318, 384, 449, 514, 580, 645};

    QVector<QPoint> foodballPositions;

    for(int x : verticalLinesXCoordinates)
    {
        for(int y : horizontalLinesYCoordinates)
        {
            QPoint foodballPoint(x, y);

            /*Check if point is on path*/
            if(GameMap::GetPathPoints().contains(foodballPoint))
            {
                /*Skip points where powerballs are*/
                if((foodballPoint.x() == 35 && foodballPoint.y() == 75) ||
                        (foodballPoint.x() == 579 && foodballPoint.y() == 75) ||
                        (foodballPoint.x() == 35 && foodballPoint.y() == 514) ||
                        (foodballPoint.x() == 579 && foodballPoint.y() == 514))
                {
                    continue;
                }

                /*Check if the point is already in the vector*/
                if(foodballPositions.contains(foodballPoint))
                {
                    continue;
                }

                foodballPositions.push_back(QPoint(x, y));
            }
        }
    }

    assert(foodballPositions.size() == TARGET_FOODBALL_COUNT);

    return foodballPositions;
}

QVector<QPoint> GameMap::GeneratePowerballPositions() const
{
    QVector<QPoint> powerballPositions;

    const QPoint powerball1Position(35, 75);
    const QPoint powerball2Position(579, 75);
    const QPoint powerball3Position(35, 514);
    const QPoint powerball4Position(579, 514);

    powerballPositions.push_back(powerball1Position);
    powerballPositions.push_back(powerball2Position);
    powerballPositions.push_back(powerball3Position);
    powerballPositions.push_back(powerball4Position);

    assert(powerballPositions.size() == TARGET_POWERBALL_COUNT);

    return powerballPositions;
}

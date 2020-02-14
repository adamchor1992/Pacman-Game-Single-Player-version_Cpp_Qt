#include "foodball.h"
#include "map.h"

FoodBall::FoodBall()
{
    CreateFoodballPositionsVector();
}

void FoodBall::CreateFoodballPositionsVector()
{
    int const COORDINATES_COUNT = 10;

    /*Coordinates (x,y) where foodballs will be placed*/
    int verticalLines_x[COORDINATES_COUNT]={35,79,144,209,274,340,406,470,536,579};
    int horizontalLines_y[COORDINATES_COUNT]={35,121,187,252,318,384,449,514,580,645};

    for(int i=0;i<COORDINATES_COUNT;i++)
    {
        for(int j=0;j<COORDINATES_COUNT;j++)
        {
            QPoint foodballPoint(verticalLines_x[i],horizontalLines_y[j]);

            /*Check if point is on path*/
            if(Map::GetPathPoints().contains(foodballPoint))
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

                m_FoodballPositions.push_back(QPoint(verticalLines_x[i],horizontalLines_y[j]));
            }
        }
    }
}

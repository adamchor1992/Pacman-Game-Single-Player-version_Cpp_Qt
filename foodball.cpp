#include "foodball.h"
#include "map.h"

FoodBall::FoodBall()
{
    Map referencemap;
    m_PacmanMapForReference= referencemap.GetPacmanPaths();

    CreateFoodballPositionsVector();
}

void FoodBall::CreateFoodballPositionsVector()
{
    int vertical_lines_x[10]={35,79,144,209,274,340,406,470,536,579};
    int horizontal_lines_y[10]={35,121,187,252,318,384,449,514,580,645};

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
                if(m_PacmanMapForReference.contains(QPoint(vertical_lines_x[i],horizontal_lines_y[j])))
                {
                    if((vertical_lines_x[i]==35 && horizontal_lines_y[j]==514) || (vertical_lines_x[i]==579 && horizontal_lines_y[j]==514)) //skip points where powerballs are
                    {
                        continue;
                    }
                    m_FoodballPositions.push_back(QPoint(vertical_lines_x[i],horizontal_lines_y[j]));
                }
        }
    }

    // Create a new vector without the duplicates
    QVector<QPoint> unique_foodballpositions;

    for (QVector<QPoint>::iterator iter = m_FoodballPositions.begin(); iter != m_FoodballPositions.end();iter++)
    {
        if(std::find(unique_foodballpositions.begin(),unique_foodballpositions.end(), *iter)==unique_foodballpositions.end())
        {
            unique_foodballpositions.push_back(*iter);
            m_FoodballCount++;
        }
    }
    std::swap( m_FoodballPositions, unique_foodballpositions );
}

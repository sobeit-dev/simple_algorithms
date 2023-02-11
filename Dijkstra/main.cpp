#include <iostream>
#include <array>
#include <limits>
#include <math.h>
#include <deque>
#include <algorithm>
#include <cstring>

const float_t inf = std::numeric_limits<float_t>::infinity();
#include "data.hpp"

int main()
{
    std::deque<uint8_t> PathPoints, VisitedPoint, AvailablePoints;
    std::array<float_t, data::NumPoints> PointsCost;
    data::StartPoint--; data::EndPoint--;

    std::fill(PointsCost.begin(), PointsCost.end(), inf);
    PointsCost[data::StartPoint] = 0.0;
    VisitedPoint.emplace_back(data::StartPoint);
    PathPoints.emplace_back(data::EndPoint);
    for (uint8_t i = 0; i < data::NumPoints; i++) if(i != data::StartPoint) AvailablePoints.emplace_back(i);
    
    printf_s("Iterations:\n");
    while(VisitedPoint.back() != data::EndPoint)
    {
        std::deque<uint8_t>::iterator tempIt;
        float_t tempCost = std::numeric_limits<float_t>::max();
        for (auto It = AvailablePoints.begin(); It != AvailablePoints.end(); It++)
        {
            PointsCost[*It] = std::min(PointsCost[*It], PointsCost[VisitedPoint.back()] + 
                                                        data::DistanceMatrix[VisitedPoint.back()][*It]);
            if((tempCost = std::min(tempCost, PointsCost[*It])) == PointsCost[*It]) tempIt = It;
        }
        VisitedPoint.emplace_back(*tempIt);
        AvailablePoints.erase(tempIt);
        for(float_t cost : PointsCost) 
            if(cost == inf) printf_s("infinity\t");
            else printf_s("%f\t", cost);
        printf_s("\n");
    }

    while(PathPoints.front() != data::StartPoint)
    {
       for (uint8_t i = 0; i < data::NumPoints; i++)
       {
            if(PathPoints.front() == i) continue;
            if((PointsCost[i] + data::DistanceMatrix[i][PathPoints.front()]) == PointsCost[PathPoints.front()])
                PathPoints.emplace_front(i);
       }
    }
    printf_s("\nMinimum cost: %f\nMinimum path: ", PointsCost[data::EndPoint]);
    for(uint8_t point : PathPoints) { printf_s("%d ", ++point); } printf_s("\n");
    return EXIT_SUCCESS;
}
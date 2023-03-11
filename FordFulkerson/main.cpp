#include <iostream>
#include <array>
#include <limits>
#include <cmath>
#include <queue>
#include <algorithm>

#include "data.hpp"
const float_t inf = std::numeric_limits<float_t>::infinity();

bool BFS(const data::Matrix& Matrix, uint8_t sPoint, uint8_t ePoint, data::Points& PathPoints)
{
    std::queue<uint8_t> tempPoints;
    std::array<bool, data::NumPoints> VisitedPoint = {0};
    
    tempPoints.push(sPoint);
    VisitedPoint[sPoint] = true;
    
    printf("\nChecking the path:\n");
    while (!tempPoints.empty()) 
    {
        uint8_t j = tempPoints.front();
        tempPoints.pop();
        for (uint8_t i = 0; i < data::NumPoints; i++) 
        {
            //  Move 
            //  printf("Edge: %d - %d (%f)\n", j+1, i+1, Matrix[j][i]);
            //  here for more detailed output
            if (VisitedPoint[i] == false && Matrix[j][i] > 0) 
            {
                printf("Edge: %d - %d (%f)\n", j+1, i+1, Matrix[j][i]);
                PathPoints[i] = j;
                if (i == ePoint) return true;
                tempPoints.push(i);
                VisitedPoint[i] = true;
            }
        }
    }
    return false;
}

int main()
{
    data::StartPoint--; data::EndPoint--;
    float_t MaxFlow = 0;

    while (true) 
    {
        data::Points PathPoints = {0};
        bool isPathAvailable = BFS(data::aMatrix, data::StartPoint, data::EndPoint, PathPoints);
        float_t CurFlow = inf;
        for (uint8_t i = data::EndPoint; i != data::StartPoint; i = PathPoints[i]) 
        {
            uint8_t j = PathPoints[i];
            CurFlow = std::min(CurFlow, data::aMatrix[j][i]);
        }
        for (uint8_t i = data::EndPoint; i != data::StartPoint; i = PathPoints[i]) 
        {
            uint8_t j = PathPoints[i];
            data::aMatrix[j][i] -= CurFlow;
            data::aMatrix[i][j] += CurFlow;
        }
        printf("Local maximum flow: %f\n", CurFlow);
        MaxFlow += CurFlow;
        if(!isPathAvailable) break;
    }
    
    printf("\nThe maximum flow between point %d and point %d is: %f\n", data::StartPoint+1, data::EndPoint+1, MaxFlow);
    return EXIT_SUCCESS;
}
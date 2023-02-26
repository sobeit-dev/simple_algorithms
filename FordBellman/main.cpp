#include <iostream>
#include <math.h>
#include <vector>
#include <array>
#include <deque>

struct Edge
{
    uint8_t start;
    uint8_t end;
    float_t cost;
};

constexpr float_t inf = std::numeric_limits<float_t>::infinity();
#include "data.hpp"

int main() 
{
    std::array<float_t, data::NumPoints + 1> PointsCost;
    std::fill(PointsCost.begin(), PointsCost.end(), inf);
    PointsCost[data::StartPoint] = 0.0;
    // variable PointsCost[0] is not used because numbering starts from one

    std::deque<uint8_t> PathPoints;
    PathPoints.emplace_back(data::EndPoint);

    for (size_t i = 0; i < data::NumPoints - 1; i++)
        for (Edge edge : data::Edges)
            if(PointsCost[edge.start] < inf)
                PointsCost[edge.end] = 
                    std::min(PointsCost[edge.end], PointsCost[edge.start] + edge.cost);
    printf("\nMinimum costs from all points to point %d:\n", data::StartPoint);
    for (size_t i = 1; i < data::NumPoints + 1; i++) printf("%f\t", PointsCost[i]);

    for (size_t i = 0; i < data::NumPoints - 1; i++)
       for(Edge edge : data::Edges)
            if(PointsCost[edge.start] + edge.cost == PointsCost[PathPoints.front()])
                if(edge.end == PathPoints.front()) PathPoints.emplace_front(edge.start);
    printf("\n\nMinimum path from point %d to point %d: ", data::StartPoint, data::EndPoint);
    for (uint8_t i : PathPoints) printf("%d ", i);

    return 0;
}
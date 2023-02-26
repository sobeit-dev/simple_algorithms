#ifndef DATA
#define DATA

namespace data
{
    const uint8_t StartPoint = 1;
    const uint8_t EndPoint = 9;
    const uint8_t NumPoints = 10;

    const std::vector<Edge> Edges 
    { 
        {1, 2, 6},
        {1, 4, 5},
        {2, 3, 1},
        {2, 4, 3},
        {3, 4, 2},
        {3, 5, 7},
        {3, 7, 3},
        {3, 8, 12},
        {4, 6, 1},
        {4, 8, 3},
        {5, 7, 3},
        {6, 8, 10},
        {7, 8, 4},
        {7, 9, 3},
        {7, 10, 3},
        {8, 9, 7},
        {9, 10, 1},
    };
}

#endif /* DATA */
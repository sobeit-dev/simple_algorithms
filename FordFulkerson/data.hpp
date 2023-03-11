#ifndef DATA
#define DATA

namespace data
{
    const uint8_t NumPoints = 10;
    uint8_t StartPoint      = 1;
    uint8_t EndPoint        = 9;
    using Points = std::array<uint8_t, data::NumPoints>;
    using Matrix = std::array<std::array<float_t, NumPoints>, NumPoints>;
    
    Matrix aMatrix
    {
        {
            {0, 6, 0, 5, 0, 0, 0, 0,  0, 0},
            {0, 0, 1, 3, 0, 0, 0, 0,  0, 0},
            {0, 0, 0, 2, 7, 0, 3, 12, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 3,  0, 0},
            {0, 0, 0, 0, 0, 0, 3, 0,  0, 0},
            {0, 0, 0, 0, 0, 0, 0, 10, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 4,  3, 3},
            {0, 0, 0, 0, 0, 0, 0, 0,  7, 0},
            {0, 0, 0, 0, 0, 0, 0, 0,  0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0,  0, 0}
        }
    };

    // Matrix aMatrix = // from example 
    // { 
    //     {
    //         {0,  10, 3,  14, 4, 0},
    //         {5,  0,  5,  9,  5, 0},
    //         {5,  6,  0,  15, 0, 10},
    //         {12, 7,  10, 0,  7, 2},
    //         {3,  9,  0,  8,  0, 13},
    //         {0,  0,  3,  4,  5, 0}
    //     }
    // };
}

#endif /* DATA */
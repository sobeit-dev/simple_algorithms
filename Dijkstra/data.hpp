namespace data
{
    const uint8_t NumPoints = 10;
    uint8_t StartPoint      = 1;
    uint8_t EndPoint        = 9;

    const std::array<std::array<const float_t, NumPoints>, NumPoints> DistanceMatrix
    {
        {
            {0,     6,      inf,    5,      inf,    inf,    inf,    inf,    inf,    inf},
            {inf,   0,      1,      3,      inf,    inf,    inf,    inf,    inf,    inf},
            {inf,   inf,    0,      2,      7,      inf,    3,      12,     inf,    inf},
            {inf,   inf,    inf,    0,      inf,    1,      inf,    3,      inf,    inf},
            {inf,   inf,    inf,    inf,    0,      inf,    3,      inf,    inf,    inf},
            {inf,   inf,    inf,    inf,    inf,    0,      inf,    10,     inf,    inf},
            {inf,   inf,    inf,    inf,    inf,    inf,    0,      4,      3,      3  },
            {inf,   inf,    inf,    inf,    inf,    inf,    inf,    0,      7,      inf},
            {inf,   inf,    inf,    inf,    inf,    inf,    inf,    inf,    0,      1  },
            {inf,   inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    0  }
        }
    };
}

#include <iostream>
#include <math.h>
#include <vector>
#include "data.hpp"

enum class sign : uint8_t
{
    equals,
    less,
    greater,
    more_or_equal,
    less_or_equal
};

struct Point2D
{
    bool isExists = true;
    float_t x = 0;
    float_t y = 0;
};

struct LineInequality
{
    float_t A;
    float_t B;
    float_t C;
    sign Sign;
};

Point2D LineCrossing(LineInequality const& first, LineInequality const& second)
{
    Point2D TempPoint;

    float_t denominator_x_and_y = first.A * second.B - second.A * first.B;
    if (denominator_x_and_y == 0.0)
    {
        TempPoint.isExists = false;
        return TempPoint;
    }

    float_t numerator_x = first.B * second.C - second.B * first.C;
    float_t numerator_y = first.C * second.A - second.C * first.A;

    TempPoint.x = numerator_x / denominator_x_and_y;
    TempPoint.y = numerator_y / denominator_x_and_y;
    return TempPoint;
}

bool CheckPointAcceptRange(const Point2D &point, const std::vector<LineInequality> &LISystem)
{
    for (const LineInequality &LI : LISystem)
    {
        float_t tempTotal = LI.A * point.x + LI.B * point.y + LI.C;
        switch (LI.Sign)
        {
        case sign::equals:
            if (tempTotal == 0.0) continue;
            else return false;

        case sign::greater:
            if (tempTotal > 0.0) continue;
            else return false;

        case sign::less:
            if (tempTotal < 0.0) continue;
            else return false;

        case sign::more_or_equal:
            if (tempTotal >= 0.0) continue;
            else return false;

        case sign::less_or_equal:
            if (tempTotal <= 0.0) continue;
            else return false;
        }
    }
    return true;
}

int main()
{
    float_t maxTotal = 0;
    
    std::vector<LineInequality> LISystem = \
    {
        { data::expenses_coper_C,   data::expenses_coper_K,   -data::copper_reserves,     sign::less_or_equal },
        { data::expenses_plastic_C, data::expenses_plastic_K, -data::plastic_reserves,    sign::less_or_equal },
        { -1,                       1,                        -data::K_demand_limit_by_C, sign::less_or_equal },
        { 0,                        1,                        -data::K_demand_limit,      sign::less_or_equal },
        { 1,                        0,                        0,                          sign::more_or_equal },
        { 0,                        1,                        0,                          sign::more_or_equal },
    };

    printf_s("Available key points and profit in them:\n\n");
    for (size_t i = 0; i < LISystem.size(); i++)
    {
        for (size_t j = i + 1; j < LISystem.size(); j++)
        {
            Point2D tempPoint = LineCrossing(LISystem[i], LISystem[j]);

            if (tempPoint.isExists && CheckPointAcceptRange(tempPoint, LISystem))
            {
                float_t tempTotal = data::price_C * tempPoint.x + data::price_K * tempPoint.y; // objective function
                maxTotal = tempTotal > maxTotal ? tempTotal : maxTotal;
                printf_s("\tx:%04f \t y:%04f \t total:%04f\n",
                    tempPoint.x, tempPoint.y, tempTotal);
            }
        }
    }
    printf_s("\nMax total: %4f\n", maxTotal);

    system("pause");
    return EXIT_SUCCESS;
}
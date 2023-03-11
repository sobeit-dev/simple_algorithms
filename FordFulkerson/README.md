# Алгоритм Форда-Фалкерсона

Идея алгоритма заключается в следующем. Выбираем такой путь от источника с к стоку, чтобы для каждого ребра остаточная пропускная способность была строго больше нуля. Выбираем минимальное значение среди остаточных пропускных способностей ребер данного пути. Увеличиваем поток на каждом из ребер данного пути на выбранное минимальное значение. Далее ищем следующий аналогичный путь. Работа алгоритма продолжается до тех пор, пока удается находить данные пути.

[Теорема Форда-Фалкерсона](https://en.wikipedia.org/wiki/Max-flow_min-cut_theorem): величина максимального потока в графе путей равна величине пропускной способности его минимального разреза.
## Задача для демонстрации алгоритма будет задана графом

![Граф]( https://beeimg.com/images/v68200284243.png "Граф")
Требуется определить максимальный поток от точки 1 до точки 9. Граф будет представлен матрицей смежности.

## Программный расчёт
```
Checking the path:
Edge: 1 - 2 (6.000000)
Edge: 1 - 4 (5.000000)
Edge: 2 - 3 (1.000000)
Edge: 4 - 6 (1.000000)
Edge: 4 - 8 (3.000000)
Edge: 3 - 5 (7.000000)
Edge: 3 - 7 (3.000000)
Edge: 8 - 9 (7.000000)
Local maximum flow: 3.000000

Checking the path:
Edge: 1 - 2 (6.000000)
Edge: 1 - 4 (2.000000)
Edge: 2 - 3 (1.000000)
Edge: 4 - 6 (1.000000)
Edge: 3 - 5 (7.000000)
Edge: 3 - 7 (3.000000)
Edge: 3 - 8 (12.000000)
Edge: 7 - 9 (3.000000)
Local maximum flow: 1.000000

Checking the path:
Edge: 1 - 2 (5.000000)
Edge: 1 - 4 (2.000000)
Edge: 4 - 6 (1.000000)
Edge: 6 - 8 (10.000000)
Edge: 8 - 9 (4.000000)
Local maximum flow: 1.000000

Checking the path:
Edge: 1 - 2 (5.000000)
Edge: 1 - 4 (1.000000)
Local maximum flow: 0.000000

The maximum flow between point 1 and point 9 is: 5.000000
```

## Пояснение работы кода

Исходные данные для работы алгоритма указываются в `data.cpp`. 
```C++
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
```
`NumPoints` задает общие колличество точек, `StartPoint` задает начальную точку маршрута, а `EndPoint` конечную.

Сам алгоритм содержится в `main.cpp` и состоит из нескольких частей: 

### Функция для поиска в ширину
```C++
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
```
Данная функция возвращает `true` если доступен хотя бы один путь, так же данная функция заполняет массив `PathPoints`.

### Расчёт максимального потока
```C++
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
```
Результатом этого блока является переменная `MaxFlow` которая хранит значение максимального потока.

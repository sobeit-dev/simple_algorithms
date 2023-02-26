# Алгоритм Форда-Беллмана

Предложен независимо [Ричардом Беллманом](https://ru.wikipedia.org/wiki/%D0%91%D0%B5%D0%BB%D0%BB%D0%BC%D0%B0%D0%BD,_%D0%A0%D0%B8%D1%87%D0%B0%D1%80%D0%B4) и [Лестером Фордом](https://ru.wikipedia.org/wiki/%D0%A4%D0%BE%D1%80%D0%B4,_%D0%9B%D0%B5%D1%81%D1%82%D0%B5%D1%80). Алгоритм Форда-Беллмана позволяет найти кратчайшие пути из одной вершины графа до всех остальных, даже для графов, в которых веса ребер могут быть отрицательными. Тем не менее, в графе не должно быть циклов отрицательного веса. При этом алгоритм Форда-Беллмана позволяет определить наличие циклов отрицательного веса, достижимых из начальной вершины. Алгоритм Форда-Беллмана использует динамическое программирование.

## Задача для демонстрации алгоритма будет задана графом

![Граф]( https://beeimg.com/images/v68200284243.png "Граф")
Требуется определить минимальный путь от точки 1 до точки 9. Для более удобной работы с данными, граф будет представлен списком ребер.

## Программный расчёт
![Программный расчёт]( https://beeimg.com/images/f29587803112.png "Итерации")

## Пояснение работы кода

Исходные данные для работы алгоритма указываются в `data.cpp`. 
```C++
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
```
`NumPoints` задает общие колличество точек, `StartPoint` задает начальную точку маршрута, а `EndPoint` конечную. Список ребер `Edges` заполняется на основе графа.

Структура `Edge` имеет следующие описание:
```C++
struct Edge
{
    uint8_t start;
    uint8_t end;
    float_t cost;
};
```

Сам алгоритм содержится в `main.cpp` и состоит из нескольких частей: 

### Первичная инициализация
```C++
std::array<float_t, data::NumPoints + 1> PointsCost;
std::fill(PointsCost.begin(), PointsCost.end(), inf);
PointsCost[data::StartPoint] = 0.0;
// variable PointsCost[0] is not used because numbering starts from one
std::deque<uint8_t> PathPoints;
PathPoints.emplace_back(data::EndPoint);
```

### Расчёт минимальной стоимости путей относительно `StartPoint`
```C++
for (size_t i = 0; i < data::NumPoints - 1; i++)
        for (Edge edge : data::Edges)
            if(PointsCost[edge.start] < inf)
                PointsCost[edge.end] = 
                    std::min(PointsCost[edge.end], PointsCost[edge.start] + edge.cost);
printf("\nMinimum costs from all points to point %d:\n", data::StartPoint);
for (size_t i = 1; i < data::NumPoints + 1; i++) printf("%f\t", PointsCost[i]);
```
Результатом этого блока является заполненный массив `PointsCost` который содержит минимальные стоимости путей.

### Восстановление минимального пути
```C++
for (size_t i = 0; i < data::NumPoints - 1; i++)
       for(Edge edge : data::Edges)
            if(PointsCost[edge.start] + edge.cost == PointsCost[PathPoints.front()])
                if(edge.end == PathPoints.front()) PathPoints.emplace_front(edge.start);
printf("\n\nMinimum path from point %d to point %d: ", data::StartPoint, data::EndPoint);
for (uint8_t i : PathPoints) printf("%d ", i);
```
Результатом этого блока является очередь `PathPoints` которая содержит точки образующие минимальный путь.

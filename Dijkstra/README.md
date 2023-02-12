# Алгоритм Дейкстры

[Эдсгер Вибе Дейкстра](https://en.wikipedia.org/wiki/Edsger_W._Dijkstra) — нидерландский учёный, разработал алгоритм поиска кратчайшего пути на графе, ставший известным как [«алгоритм Дейкстры»](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm). Лауреат [Премии Тьюринга](https://en.wikipedia.org/wiki/Turing_Award) в 1972.

## Метод Дейкстры состоит из выполнения следующих шагов

1. Начинаем с непосредственных расстояний, с длины в одно ребро от заданного узла i до всех остальных узлов. 
2. Затем выбираем наименьшее из них в качестве «постоянного» наименьшего расстояния, фиксируя узел, до которого наименьшее расстояние, в качестве нового узла.
3. Далее добавляем это наименьшее расстояние к длинам ребер от нового узла до всех остальных узлов. 
4. Сравниваем эту сумму с предыдущим расстоянием от узла до остальных узлов и заменяем прежнее расстояние, если новое меньше. 
5. Затем новый узел удаляем из списка узлов, до которых еще не определены кратчайшие расстояния, и ему присваиваем «постоянную» метку. 

Затем шаги 1...5 повторяем, присоединяя новое кратчайшее расстояние к списку «постоянных» узлов и т.д., пока конечный узел j не окажется соединенным с узлом i путем из выделенных ребер.

## Задача для демонстрации алгоритма будет задана графом

![Граф]( https://beeimg.com/images/v68200284243.png "Граф")
Требуется определить минимальный путь от точки 1 до точки 9. Для более удобной работы с данными, граф можно представить в виде матрицы расстояний. Стоит отметить, что значения по диагонали у такой матрицы должны равняться нулю.

## Матрица расстояний будет иметь следующий вид

![Матрица расстояний]( https://beeimg.com/images/h69605290063.png "Матрица расстояний")

## Ручной расчёт

![Итерации]( https://beeimg.com/images/k24088174054.png "Итерации")
Исходя из последний итерации минимальная стоимость пути будет составлять 13 единиц, а путь будет следующим: 1 &rarr; 2 &rarr; 3 &rarr; 7 &rarr; 10

## Программный расчёт
![Программный расчёт]( https://beeimg.com/images/s27383604021.png "Итерации")

Таким образом ручной и программный расчет сошлись.

## Пояснение работы кода

Исходные данные для работы алгоритма указываются в `data.cpp`. 
```C++
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
```
`NumPoints` задает общие колличество точек, `StartPoint` задает начальную точку маршрута, а `EndPoint` конечную. Матрица растояний `DistanceMatrix` заполняется на основе графа.

Сам алгоритм содержится в `main.cpp` и состоит из нескольких частей: 

### Объявление переменных
```C++
std::deque<uint8_t> PathPoints, VisitedPoint, AvailablePoints;
std::array<float_t, data::NumPoints> PointsCost;
```
### Востановление смещения
```C++
data::StartPoint--; data::EndPoint--;
```
Требуется для корректной работы коллекций т.к. отсчет ведется с нуля, а заполнение `StartPoint` и `EndPoint` в `data.cpp` начинается с единицы (для удобства).    

### Первичная инициализация
```C++
std::fill(PointsCost.begin(), PointsCost.end(), inf);
PointsCost[data::StartPoint] = 0.0;
VisitedPoint.emplace_back(data::StartPoint);
PathPoints.emplace_back(data::EndPoint);
for (uint8_t i = 0; i < data::NumPoints; i++) if(i != data::StartPoint) AvailablePoints.emplace_back(i);
```

### Расчёт минимальной стоимости путей относительно `StartPoint`
```C++
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
```
Результатом этого блока является заполненный массив `PointsCost` который содержит минимальные стоимости путей.

### Восстановление минимального пути
```C++
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
```
Результатом этого блока является очередь `PathPoints` которая содержит точки образующие минимальный путь.

# Material-point-planning
Methods of optimization project 2 course ITMP

## Цель работы 
Изучение применимости генетических алгоритмов для планирования движения материальной точки.

## Постановка задачи
![image](https://user-images.githubusercontent.com/29158476/60630190-ae6c4d80-9e01-11e9-8e4b-bdee460f2936.png)

## Генетический алгоритм
Для решения поставленной задачи используется способ создания генетического алгоритма, т.е. метод многомерной оптимизации, который основан на принципах эволюционной биологии. Сама суть метода проста и «украдена» у природы: есть какая-то популяция (набор векторов), которая размножается, на которую воздействуют мутации и производится естественный отбор. Каждое следующее поколение превосходит предыдущее по требуемым параметрам.
Так отбор необходимых видов может привести к решению(оптимальному). В данной задаче стоит опираться на несколько вещей, которые мы хотим оптимизировать.

* Расстояние до конечной точки
Данная характеристика будет указывать на расстояние между конечной точкой и нашим положением в момент расчета, т.е. после того, как мы прошли путь, предложенный хромосомой. Высчитывается как Евклидово расстояние между (1, 1) и последней точкой маршрута
* Длина всего пути
Характеристика показывает, сколько было пройдено точкой в целом. Данная характеристика должна быть стремиться к минимальному значению при оптимизации. 
Считается как сумму пройденных расстояний за каждый dt.
* Хромосомы и аллели
Аллель –  единичное действие, которое совершает точка. А хромосома – набор таких аллелей, то есть это последовательность действий, которая совершает точка. 
* Функция оценки
Функция оценки поможет алгоритму определить насколько предложенное решение соответствует желаемому решению, она должна качественно оценивать хромосомы в популяции. 

## Операции по изменению популяции
Для получения необходимого результата необходимо не только оценить текущий результат, но и требуется изменить популяцию для возможной её оптимизации.
Для этого использовано несколько алгоритмов изменения хромосом и их аллелей. 

### Отбор 
Суть проста: после того, как совершается оценка хромосом, происходит сортировка. И те хромосомы, что показали лучший результат и будут использованы для генерирования последующих популяций, а хромосомы с плохим результатом – удаляются.
### Кроссовер
Процесс обмена генами в биологии, работает примерно так же и для данного алгоритма, с некоторыми изменениями, потому что длина хромосомы переменна. Если сказать просто, то берётся две хромосомы и значения их аллелей перетасовывается. Берется некоторое значение аллей меньшей хромосомы, передается в новую, затем, с этого же индекса берутся все оставшиеся аллели второй хромосомы и передаются в новую.
### Мутации 
Мутация происходит путем не самого сильного изменения значения случайной аллели в хромосоме. Изменение происходит за счет добавления или убавления некоторого случайного числа.
### Добавление и удаление 
Так как путь нужно прокладывать, необходимо определить операции вставки и удаления аллели. Будем брать некоторую случайную позицию в хромосоме и вставлять/удалять элемент в этой позиции.

## Организация кода 
Алгоритм реализован на языке C++ и разбит на классы: Chromosome (хранит набор аллелей), Map (содержит итоговую, начальную точку), Tournament (содержащий основную логику алгоритма). Последний класс отвечает, как за процесс отбора, так и за генерацию результатов функции оценки.

Выбранный алгоритм действий: 
1.	Создается случайная популяция из n видов. Изначально каждая хромосома состоит из одной аллели. 
2.	Проведем оценку и отсортируем по значению функции оценки. 
3.	Удаляем «слабую» половину и начинаем генерировать новое поколение:
*	Скрещиваем первого со средним, второго со следующим после среднего с некоторым шансом добавления/удаления/не изменения хромосомы. Так мы заполним n/4 популяции. 
*	Вторую четверть получим из мутации лучших в данный момент видов. Будем повторять некоторое количество раз. 
Также всегда проходит проверка на условие поставленной задачи, то есть точка не должна выходить за изначальный квадрат и не должна проходить через данные окружности. 

Полученные результаты позволяют говорить о том, что алгоритм позволяет решать поставленную задачу. 

## Результаты работы 
Рис. 1: График зависимости расстояния до точки от длины пути. Первого решения
![](https://user-images.githubusercontent.com/29158476/60630191-af9d7a80-9e01-11e9-8354-88498b05e3f2.png)

Рис. 2: График зависимости расстояния до точки от длины пути. Для лучшего представителя второй популяции
![](https://user-images.githubusercontent.com/29158476/60630195-b0cea780-9e01-11e9-8156-70bb2d0e2e8e.png)

Рис. 3: График зависимости расстояния до точки от длины пути. Для трех лучших представителей второй популяции
![](https://user-images.githubusercontent.com/29158476/60630197-b1ffd480-9e01-11e9-8ad3-bd0c7a241bcb.png)

Рис. 4: График зависимости расстояния до точки от длины пути. Для лучшего и 10-го
![](https://user-images.githubusercontent.com/29158476/60630200-b3310180-9e01-11e9-9e61-c6c312bcb75f.png)

Рис. 5: Один из вариантов маршрут
![](https://user-images.githubusercontent.com/29158476/60630202-b4622e80-9e01-11e9-9030-adae853f830d.jpg)


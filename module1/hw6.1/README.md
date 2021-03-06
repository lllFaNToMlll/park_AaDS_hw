# HW1
Дано множество целых чисел из [0..10^9] размера n. 
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
- 10%  перцентиль
- медиана
- 90%  перцентиль

Требования: 
- К дополнительной памяти: O(n). 
- Среднее время работы: O(n)
- Должна быть отдельно выделенная функция partition. 
- Рекурсия запрещена. 
- Решение должно поддерживать передачу функции сравнения снаружи.

Формат ввода
Сначала вводится кол-во элементов массива n. После сам массив.

Формат вывода
Параметры множества в порядке:

- 10% перцентиль
- медиана
- 90% перцентиль

Пример
(Ввод)
10
1 2 3 4 5 6 7 8 9 10 
(Вывод)
2 6 10

Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. Описание для случая прохода от начала массива к концу:
- Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
- Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
- Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
- Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
- Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
- В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

6_1. Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.


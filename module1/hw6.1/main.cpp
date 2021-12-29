/*Дано множество целых чисел из [0..10^9] размера n.
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

Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
Описание для случая прохода от начала массива к концу:
- Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
- Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
  Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы.
  Последним элементом лежит опорный.
- Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
- Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
- Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
- В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

6_1. Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition реализуйте методом
прохода двумя итераторами от начала массива к концу.*/

#include <iostream>
#include <sstream>
#include <cassert>
#include <fstream>

template <class T>
class DefaultComparator {
public:
    bool operator()(const T& l, const T& r) const {
        return l < r;
    }
};

template <class T, class Compare = DefaultComparator<T> >
int MedianOfThree(T* arr, int l, int r, const Compare& Cmp = DefaultComparator<T>() ) {
    if (Cmp(arr[l], arr[r]) && Cmp(arr[(l + r) / 2], arr[l])) {
        return l;
    }
    if (Cmp(arr[r], arr[l]) && Cmp(arr[(l + r) / 2], arr[r])) {
        return r;
    }
    return (l + r) / 2;
}

template <class T, class Compare = DefaultComparator<T>>
int Partition(T* arr, int l, int r, const Compare& Cmp = DefaultComparator<T>() ) {
    int medianIndex = MedianOfThree(arr, l, r);
    std::swap(arr[medianIndex], arr[r]);
    int i = l - 1;
    for (int j = l; j < r; ++j) {
        if (Cmp(arr[j], arr[r])) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i+1], arr[r]);
    return i+1;
}

template <class T, class Compare = DefaultComparator<T> >
T FindKthStat(T* arr, int size, int kth, const Compare& Cmp = DefaultComparator<T>() ) {
    int l = 0;
    int r = size - 1;
    while (true) {
        int pivotIndex = Partition(arr, l, r);
        if (pivotIndex == kth) {
            return arr[pivotIndex];
        }
        else if (Cmp(pivotIndex, kth)) {
            l = pivotIndex + 1;
        }
        else {
            r = pivotIndex - 1;
        }
    }
}


void FindAllStat(std::istream& in, std::ostream& out) {
    int size = 0;
    in >> size;
    int* arr = new int[size];
    for (int i = 0; i < size; ++i) {
        in >> arr[i];
    }
    int k10 = 10 * size / 100;
    out << FindKthStat(arr, size, k10) << "\n";
    int k50 = 50 * size / 100;
    out << FindKthStat(arr, size, k50) << "\n";
    int k90 = 90 * size / 100;
    out << FindKthStat(arr, size, k90);
    delete [] arr;
}

void testLogic() {
    {
        std::stringstream in;
        std::stringstream out;
        in << "10" << std::endl;
        in << "1 2 3 4 5 6 7 8 9 10" << std::endl;
        FindAllStat(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "2\n6\n10");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "10" << std::endl;
        in << "10 8 2 4 3 7 5 1 6 9" << std::endl;
        FindAllStat(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "2\n6\n10");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "10" << std::endl;
        in << "5 5 5 5 5 5 5 5 5 5" << std::endl;
        FindAllStat(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "5\n5\n5");
    }

    {
        std::ifstream file("/home/ivan/park_AaDS_hw/hw6.1/024");
        if (file) {
            std::stringstream in;
            std::stringstream out;
            in << file.rdbuf();
            file.close();
            FindAllStat(in, out);
            std::cout << out.str() << std::endl;
            assert(out.str() == "100001\n500001\n900001");
        }
    }
}

int main() {
    //FindAllStat(std::cin,std::cout);
    testLogic();
    return 0;
}

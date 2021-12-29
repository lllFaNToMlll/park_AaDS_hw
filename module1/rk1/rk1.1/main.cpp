#include <iostream>
#include <sstream>
#include <assert.h>
#include <vector>

int DEFAULT_SIZE = 8;

/*
Дан массив, который получен путем нескольких циклических сдвигов исходного
 отсортированного массива. Нужно найти индекс элемента, с которого начинался исходный массив.
Примеры:
[12, 14, 16, 17, 1, 3, 5, 7] (исходный массив [1, 3, 5, 7, 12, 14, 16, 17])
Ответ: 4
[5, 5, 5, 1] (исходный массив [1, 5, 5, 5])
Ответ: 3
Требование: сложность O(logN)
Формат ввода
Вначале вводится n - число элементов массива.
Затем n целых чисел элементов массива.
Формат вывода
Целое число - индекс элемента, с которого начинался исходный массив.
 */

template <class T_>
int binSearch(T_* array, T_ number, T_ lowIndex, T_ highIndex) {
    int middleIndex = 0;
    while (lowIndex < highIndex) {
        middleIndex = (lowIndex + highIndex) / 2;
        if (array[middleIndex] >= number)
            lowIndex = middleIndex + 1;
        else
            highIndex = middleIndex;
    }
    if (array[lowIndex] - number >= number - array[lowIndex - 1])
        return lowIndex - 1;
    else
        return lowIndex;
}

template <class T_>
int expAndBinSearch(T_* array, T_ size) {
    int number = array[0];
    int index = 1;
    if (array[index] < number)
        return 1;
    index = 2;
    while (index < size && array[index] >= number)
        index *= 2;
    return binSearch(array, number, index/2, std::min(index, size - 1));
}

void findIndex(std::istream& in, std::ostream& out) {
    int arrSize = 0;

    in >> arrSize;
    int* arr = new int[arrSize];
    for (int i = 0; i < arrSize; ++i) {
        in >> arr[i];
    }

    int index = expAndBinSearch(arr, arrSize);


    out << index;
    delete[] arr;
}

void testLogic() {
    {
        std::stringstream in;
        std::stringstream out;
        in << "8" << std::endl;
        in << "12 14 16 17 1 3 5 7" << std::endl;
        findIndex(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "4");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "4" << std::endl;
        in << "5 5 5 1" << std::endl;
        findIndex(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "3");
    }
}

int main() {
    //findIndex(std::cin,std::cout);
    testLogic();
    return 0;
}

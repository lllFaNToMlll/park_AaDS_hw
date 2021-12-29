#include <iostream>
#include <sstream>
#include <assert.h>
/*
Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
Требования: Время работы поиска для каждого элемента B[i]: O(log(k)).
Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон
для бинарного поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
 */

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

template <class T_>
int binSearch(T_* array, T_ number, T_ lowIndex, T_ highIndex) {
    int middleIndex = 0;
    while (lowIndex < highIndex) {
        middleIndex = (lowIndex + highIndex) / 2;
        if (array[middleIndex] < number)
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
int expAndBinSearch(T_* array, T_ size, T_ number) {
    int index = 0;
    if (array[index] >= number)
        return 0;
    index = 1;
    while (index < size && array[index] <= number)
        index *= 2;
    return binSearch(array, number, index/2, MIN(index, size - 1));
}

void findTwin(std::istream& in, std::ostream& out) {
    int lengthA = 0, lengthB = 0;

    in >> lengthA;
    int* A = new int[lengthA];
    for (int i = 0; i < lengthA; ++i) {
        in >> A[i];
    }

    in >> lengthB;
    int* B = new int[lengthB];
    for (int i = 0; i < lengthB; ++i) {
        in >> B[i];
    }

    int* result = new int[lengthB];

    for (int i = 0; i < lengthB; ++i) {
        result[i] = expAndBinSearch(A, lengthA, B[i]);
    }

    for (int i = 0; i < lengthB; ++i) {
        out << result[i] << " ";
    }
    delete[] A;
    delete[] B;
    delete[] result;
}

void testLogic() {
    {
        std::stringstream in;
        std::stringstream out;
        in << "3" << std::endl;
        in << "10 20 30" << std::endl;
        in << "3" << std::endl;
        in << "9 15 35" << std::endl;
        findTwin(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "0 0 2 ");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "3" << std::endl;
        in << "10 20 30" << std::endl;
        in << "4" << std::endl;
        in << "8 9 10 32" << std::endl;
        findTwin(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "0 0 0 2 ");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "4" << std::endl;
        in << "10 20 30 32" << std::endl;
        in << "4" << std::endl;
        in << "25 34 30 32" << std::endl;
        findTwin(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "1 3 2 3 ");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "4" << std::endl;
        in << "5 23 26 34" << std::endl;
        in << "4" << std::endl;
        in << "132 4 21 32" << std::endl;
        findTwin(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "3 0 1 3 ");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "14" << std::endl;
        in << "1 2 5 8 11 13 14 17 20 23 26 29 32 33" << std::endl;
        in << "7" << std::endl;
        in << "14 21 23 10 12 13 13" << std::endl;
        findTwin(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "6 8 9 4 4 5 5 ");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "10" << std::endl;
        in << "15 32 37 41 45 56 64 65 72 93" << std::endl;
        in << "10" << std::endl;
        in << "53 7 97 80 21 10 75 46 62 52" << std::endl;
        findTwin(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "5 0 9 8 0 0 8 4 6 5 ");
    }
}

int main() {
    //findTwin(std::cin,std::cout);
    testLogic();
    return 0;
}

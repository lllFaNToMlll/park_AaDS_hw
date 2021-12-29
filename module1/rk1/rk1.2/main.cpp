#include <iostream>
#include <sstream>
#include <assert.h>
#include <cstring>

/*
ВНИМАНИЕ! Для решения данной задачи нужно использовать структуру данных стек!
Дана последовательность, состоящая из символов '(' и ')'. Требуется определить,
является ли данная последовательность правильной скобочной последовательностью.
Длина исходной последовательности ≤ 800000.
Формат ввода
Строка, содержащая символы '(' и ')'.
Формат вывода
YES или NO, в зависимости от того, является ли скобочная последовательность правильной.
 */

int DEFAULT_SIZE = 8;

template<class T>
class MyStack
{
public:
    MyStack() : arr(nullptr), arrSize(0), upperElementIndex(-1) {}
    explicit MyStack(int size) : arrSize(size), upperElementIndex(-1)
    {
        arr = new int[arrSize];
    }

    MyStack(const MyStack&) = delete;
    MyStack& operator=(const MyStack&) = delete;
    MyStack(MyStack&&) = delete;
    MyStack& operator=(MyStack&& st) = delete;

    ~MyStack() {
        delete[] arr;
    }

    void push(const T& elem) {
        if (arr == nullptr) {
            arrSize = 1;
            arr = new T[arrSize];
            upperElementIndex = 1;
        }
        if (upperElementIndex + 1 >= arrSize)
            resize();
        arr[++upperElementIndex] = elem;
    }

    void resize() {
        int newArrSize = std::max(arrSize * 2, DEFAULT_SIZE);
        T* newArr = new T[newArrSize];
        for (int i = 0; i < arrSize; ++i) {
            newArr[i] = arr[i];
        }
        delete [] arr;
        arr = newArr;
        arrSize = newArrSize;
    }

    T pop() {
        if (upperElementIndex != -1)
            return arr[upperElementIndex--];
        else
            return -1;
    }

    bool isEmpty() const {
        return upperElementIndex == -1;
    }

private:
    T* arr;
    int arrSize;
    int upperElementIndex;
};


void isTrueSeq(std::istream& in, std::ostream& out) {
    char str[100000];
    in >> str;
    MyStack<char> stack;
    size_t strSize = strlen(str);
    for (size_t i = 0; i < strSize; ++i) {
        if (str[i] == '(') {
            stack.push('(');
        }
        if (str[i] == ')') {
            if (stack.isEmpty()) {
                out << "NO";
                return;
            }
            stack.pop();
        }
    }
    if (!stack.isEmpty()) {
        out << "NO";
        return;
    }
    out << "YES";
}

void testLogic() {
    {
        std::stringstream in;
        std::stringstream out;
        in << "()" << std::endl;
        isTrueSeq(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "YES");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << ")(" << std::endl;
        isTrueSeq(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "NO");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "(()()))" << std::endl;
        isTrueSeq(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "NO");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "(()())" << std::endl;
        isTrueSeq(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "YES");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "((())))" << std::endl;
        isTrueSeq(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "NO");
    }
}


int main() {
    //isTrueSeq(std::cin,std::cout);
    testLogic();
    return 0;
}

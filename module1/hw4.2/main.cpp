#include <iostream>
#include <sstream>
#include <assert.h>
#include <vector>

int DEFAULT_SIZE = 8;

/*
4.2 Топ K пользователей из лога
Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в
порядке возрастания посещаемости. Количество заходов и идентификаторы пользователей не повторяются.
Требования: время работы O(N * logK), где N - кол-во пользователей
Формат входных данных: Сначала вводятся N и K, затем пары (Идентификатор пользователя, посещаемость сайта).
Формат выходных данных: Идентификаторы пользователей в порядке возрастания посещаемости
Требования:
Время работы O(N * logK)
Куча должна быть реализована в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.
Куча должна быть динамической.
В insert у вас нет просеивания вверх. У вас все работает, потому что вы сразу после вставки extractMin вызываете.

Посмотрите, пожалуйста, как в лекции сделано. У вас после insert должна быть корректная куча с точки зрения выполнения свойств кучи для каждого элемента.
 */


template <class T>
class MyVector {
private:
    T* vector;
    int vector_capacity;
    int vector_size;

    // Выделить новую память
    void resize() {
        int new_vector_capacity = std::max(vector_capacity * 2, DEFAULT_SIZE);
        T* new_vector = new T[new_vector_capacity];

        for (int i = 0; i < vector_capacity; ++i) {
            new_vector[i] = vector[i];
        }

        delete [] vector;
        vector = new_vector;
        vector_capacity = new_vector_capacity;
    }

public:
    MyVector(): vector(nullptr),vector_capacity(0), vector_size(0) {}

    ~MyVector() {
        delete [] vector;
    }

    // Удалить последний элемент
    void pop_back() {
        --vector_size;
    }

    // Проверить на пустоту
    bool is_empty() const {
        return vector_size == 0;
    }

    // Узнать количество элементов
    int size() const {
        return vector_size;
    }

    const T& operator[](int index) const {
        return vector[index];
    }

    T& operator[](int index) {
        return vector[index];
    }

    // Показать первый элемент
    T& front() const{
        return vector[0];
    }

    // Показать последний элемент
    T& back() {
        if (vector_capacity == 0) {
            throw ("ERROR: MyVector isn't initialise");
        }
        return vector[vector_size - 1];
    }

    // Добавить элемент в конец
    void push_back(const T& element) {
        if (vector_size == vector_capacity) {
            resize();
        }
        vector[vector_size] = element;
        vector_size++;
    }
};


struct userInfo {
    int userID; // ID пользователя (его уникальный номер)
    int visitCounter; // количество посещений
    userInfo()
    {
        userID = visitCounter = 0.0;
    }
    userInfo(const userInfo &copy) = default;

    bool operator> (const userInfo& r) const {
        return this->visitCounter > r.visitCounter;
    }

    bool operator< (const userInfo& r) const {
        return this->visitCounter < r.visitCounter;
    }

    bool operator == (const userInfo &r) const {
        return this->visitCounter == r.visitCounter;
    }

    userInfo& operator= (const userInfo& r) {
        this->visitCounter = r.visitCounter;
        this->userID = r.userID;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const userInfo &elem);
};

std::ostream& operator<<(std::ostream& out, const userInfo &elem) {
    out << elem.userID;
    return out;
}


// делаю минимальную кучу, чтобы не создавать кучу из N элементов,
// а использовать только K. Выводить буду в обратном порядке,
// чтобы выводить топ по убыванию
template <class T>
class DefaultComparator {
public:
    bool operator() (const T& l, const T& r) {
        return l > r;
    }
};


template <class T, class Comparator = DefaultComparator<T> >
class MyHeap {
private:
    MyVector<T> myVec;
    Comparator cmp;

    // Построить кучу
    void buildHeap() {
        for( int i = myVec.size() / 2 - 1; i >= 0; --i ) {
            siftDown( i );
        }
    }

    // Просеять вверх кучу
    void siftUp( int index ) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (cmp(myVec[index], myVec[parentIndex])) {
                return;
            }
            std::swap(myVec[index], myVec[parentIndex]);
            index = parentIndex;
        }
    }

    // Просеять вниз кучу
    void siftDown( int index ) {
        while (1)
        {
            int leftChildIndex = 2 * index + 1;
            int rightChildIndex = 2 * index + 2;
            int smallest = index;

            if (leftChildIndex < myVec.size() && cmp(myVec[smallest], myVec[leftChildIndex])) {
                smallest = leftChildIndex;
            }

            if (rightChildIndex < myVec.size() && cmp(myVec[smallest], myVec[rightChildIndex])) {
                smallest = rightChildIndex;
            }

            if (smallest == index) {
                break;
            }
            std::swap(myVec[index],myVec[smallest]);
            index = smallest;
        }
    }

public:
    MyHeap() = default;

    explicit MyHeap( const MyVector<T>& vec ) {
        for (int i = 0; i < vec.size(); ++i) {
            myVec.push_back(vec[i]);
        }
        buildHeap();
    }
    MyHeap(const MyHeap&) = delete;
    MyHeap& operator=(const MyHeap&) = delete;
    MyHeap(MyHeap&&) = delete;
    MyHeap& operator=(MyHeap&& st) = delete;

    ~MyHeap() = default;

    // Добавить элемент в кучу вместо минимального элемента
    // и просеиваем его вверх, чтобы хранить ровно K пользователей
    void insert( T element ) {
        myVec.push_back(element);
        siftUp(myVec.size()-1);
    }

    // Извлечь минимум из кучи
    T extractMin() {
        T min = myVec.front();;
        myVec.front() = myVec.back();
        myVec.pop_back();
        if (!myVec.is_empty()) {
            siftDown(0);
        }
        return min;
    }

    // Посмотреть значение минимума в куче
    T getMin() const {
        return myVec.front();
    }

    // Проверить на пустоту
    bool is_empty() const {
        return myVec.is_empty();
    }
};


void topLog(std::istream& in, std::ostream& out) {
    MyVector<userInfo> valuesForHeap;
    userInfo buf;
    int N = 0, K = 0;
    in >> N;
    in >> K;
    if (K == 0)
        out << " ";
    else {
        // заполняю первые K элементов в кучу
        for (int i = 0; i < K; ++i) {
            in >> buf.userID;
            in >> buf.visitCounter;
            valuesForHeap.push_back(buf);
        }
        MyHeap myHeap(valuesForHeap);
        // заполняю кучу только нужными элементами
        for (int i = K; i < N; ++i) {
            in >> buf.userID;
            in >> buf.visitCounter;
            if (buf.visitCounter > myHeap.getMin().visitCounter) {
                myHeap.insert(buf);
                myHeap.extractMin();
            }
        }

        MyVector<userInfo> valuesForAnswer;
        for (int i = 0; i < K; ++i) {
            out << myHeap.extractMin() << " ";
        }
    }
}

void testLogic() {
    {
        std::stringstream in;
        std::stringstream out;
        in << "3 3" << std::endl;
        in << "36 36" << std::endl;
        in << "3 3" << std::endl;
        in << "5 5" << std::endl;
        topLog(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "3 5 36 ");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "10 3" << std::endl;
        in << "10 10" << std::endl;
        in << "1 1" << std::endl;
        in << "4 4" << std::endl;
        in << "5 5" << std::endl;
        in << "33 33" << std::endl;
        in << "2 2" << std::endl;
        in << "6 6" << std::endl;
        in << "32 32" << std::endl;
        in << "7 7" << std::endl;
        in << "8 8" << std::endl;
        topLog(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "10 32 33 ");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "10 1" << std::endl;
        in << "10 10" << std::endl;
        in << "1 1" << std::endl;
        in << "4 4" << std::endl;
        in << "5 5" << std::endl;
        in << "33 33" << std::endl;
        in << "2 2" << std::endl;
        in << "6 6" << std::endl;
        in << "32 32" << std::endl;
        in << "7 7" << std::endl;
        in << "8 8" << std::endl;
        topLog(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "33 ");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "10 5" << std::endl;
        in << "6 6" << std::endl;
        in << "1 1" << std::endl;
        in << "5 5" << std::endl;
        in << "4 4" << std::endl;
        in << "8 8" << std::endl;
        in << "2 2" << std::endl;
        in << "32 32" << std::endl;
        in << "7 7" << std::endl;
        in << "10 10" << std::endl;
        in << "33 33" << std::endl;
        topLog(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "7 8 10 32 33 ");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << "10 10" << std::endl;
        in << "6 6" << std::endl;
        in << "1 1" << std::endl;
        in << "5 5" << std::endl;
        in << "4 4" << std::endl;
        in << "8 8" << std::endl;
        in << "2 2" << std::endl;
        in << "32 32" << std::endl;
        in << "7 7" << std::endl;
        in << "10 10" << std::endl;
        in << "33 33" << std::endl;
        topLog(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "1 2 4 5 6 7 8 10 32 33 ");
    }
}

int main() {
    //topLog(std::cin,std::cout);
    testLogic();
    return 0;
}

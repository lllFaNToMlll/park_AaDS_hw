/*
Написать алгоритм для решения игры в “пятнашки”. Решением задачи является приведение к виду:
[ 1  2  3  4 ]
[ 5  6  7  8 ]
[ 9  10 11 12]
[ 13 14 15 0 ]
где 0 задает пустую ячейку.
Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.
Формат входных данных
Начальная расстановка.
Формат выходных данных
Если решение существует, то в первой строке выходного файла выведите минимальное число перемещений костяшек,
которое нужно сделать, чтобы достичь выигрышной конфигурации, а во второй строке выведите соответствующую
последовательность ходов: L означает, что костяшка сдвинулась влево, R – вправо, U – вверх, D – вниз.
Если таких последовательностей несколько, то выведите любую из них. Если же выигрышная конфигурация недостижима,
то выведите в выходной файл одно число −1.
 */
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <set>

static const size_t LINE_SIZE = 4;
static const size_t FIELD_SIZE = LINE_SIZE * LINE_SIZE;
static const double K = 5.0;

using FieldArray = std::array<uint8_t, FIELD_SIZE>;

static const FieldArray EMPTY_FIELD = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
};

static const FieldArray GOAL_FIELD = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 0
};

class FieldState {
private:
    FieldArray arrState;
    size_t zeroPos;

    void moveLeft() {
        std::swap(arrState[zeroPos], arrState[zeroPos - 1]);
        --zeroPos;
    }


    void moveRight() {
        std::swap(arrState[zeroPos], arrState[zeroPos + 1]);
        ++zeroPos;
    }


    void moveUp() {
        std::swap(arrState[zeroPos], arrState[zeroPos - LINE_SIZE]);
        zeroPos -= LINE_SIZE;
    }


    void moveDown() {
        std::swap(arrState[zeroPos], arrState[zeroPos + LINE_SIZE]);
        zeroPos += LINE_SIZE;
    }


    void init(const FieldArray& arr) {
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == 0) {
                zeroPos = i;
            }
            arrState[i] = arr[i];
        }
    }

public:
    FieldState() {
        init(EMPTY_FIELD);
    }

    FieldState(const FieldArray& arr) {
        init(arr);
    }

    FieldState(const FieldState&) = default;

    FieldState& operator=(const FieldState&) = default;

    bool operator <(const FieldState& r) const {
        return arrState < r.arrState;
    }

    bool operator ==(const FieldState& r) const {
        return arrState == r.arrState;
    }


    std::vector<FieldState> GetNextVertices() const {
        std::vector<FieldState> res;

        if (zeroPos % LINE_SIZE != 0) {
            FieldState st(*this);
            st.moveLeft();
            res.push_back(st);
        }

        if ((zeroPos + 1) % LINE_SIZE != 0) {
            FieldState st(*this);
            st.moveRight();
            res.push_back(st);
        }

        if (zeroPos >= LINE_SIZE) {
            FieldState st(*this);
            st.moveUp();
            res.push_back(st);
        }

        if (zeroPos < FIELD_SIZE - LINE_SIZE) {
            FieldState st(*this);
            st.moveDown();
            res.push_back(st);
        }

        return res;
    }


    size_t ManhattanDistance() const {
        size_t counter = 0;
        for (size_t i = 0; i < FIELD_SIZE; ++i) {
            if (arrState[i] == 0) {
                counter += abs(static_cast<int>(LINE_SIZE) - static_cast<int>(i / LINE_SIZE + 1)) + abs(static_cast<int>(LINE_SIZE) - static_cast<int>(i % LINE_SIZE + 1));
            } else {
                counter += abs(static_cast<int>(arrState[i] / LINE_SIZE) - static_cast<int>((i + 1) / LINE_SIZE)) +
                           abs(static_cast<int>(arrState[i] % LINE_SIZE) - static_cast<int>((i + 1) % LINE_SIZE));
            }
        }
        return counter;
    }


    void print() const {
        for (size_t i = 0; i < arrState.size(); ++i) {
            std::cout << static_cast<int>(arrState[i]) << " ";
            if ((i + 1) % LINE_SIZE == 0) {
                std::cout << std::endl;
            }
        }
    }


    bool isValid() {
        size_t counter = 0;
        for (size_t i = 1; i < FIELD_SIZE; ++i) {
            if (arrState[i] == 0) {
                continue;
            }
            for (size_t j = 0; j < i; ++j) {
                if (arrState[j] > arrState[i]) {
                    ++counter;
                }
            }
        }
        counter += (zeroPos / LINE_SIZE) + 1;
        return counter % 2 == 0;
    }


    static std::string TranslateSolution(std::vector<FieldState>& states) {
        std::string res;
        for (int i = states.size() - 1; i > 0; --i) {
            FieldState curState = states[i];
            FieldState nextState = states[i-1];

            if (curState.zeroPos % LINE_SIZE != 0) {
                FieldState st(curState);
                st.moveLeft();
                if (st == nextState) {
                    res += "R";
                    continue;
                }
            }

            if ((curState.zeroPos + 1) % LINE_SIZE != 0) {
                FieldState st(curState);
                st.moveRight();
                if (st == nextState) {
                    res += "L";
                    continue;
                }
            }

            if (curState.zeroPos >= LINE_SIZE) {
                FieldState st(curState);
                st.moveUp();
                if (st == nextState) {
                    res += "D";
                    continue;
                }
            }

            if (curState.zeroPos < FIELD_SIZE - LINE_SIZE) {
                FieldState st(curState);
                st.moveDown();
                if (st == nextState) {
                    res += "U";
                    continue;
                }
            }
        }
        return res;
    }


    ~FieldState() = default;
};


std::vector<FieldState> bfs(const FieldState& start) {
    const FieldState emptyState(EMPTY_FIELD);
    const FieldState goalState(GOAL_FIELD);
    std::set< std::tuple<double, FieldState, size_t> > priorityQueue;
    std::map<FieldState, FieldState> used;
    priorityQueue.insert(std::make_tuple(start.ManhattanDistance(), start, 0));
    used.insert(std::make_pair(start, emptyState));
    FieldState curState(EMPTY_FIELD);
    size_t iters = 0;

    while (!priorityQueue.empty()) {
        ++iters;
        auto it = priorityQueue.begin();
        curState = std::get<FieldState>(*it);
        size_t currentPath = std::get<size_t>(*it);
        priorityQueue.erase(it);

        if (curState == goalState) break;

        std::vector<FieldState> children = curState.GetNextVertices();
        for (FieldState& child: children) {
            if (used.find(child) == used.end()) {
                priorityQueue.insert(std::make_tuple(child.ManhattanDistance() * K + currentPath + 1, child, currentPath + 1));
                used.insert(std::make_pair(child, curState));
            }
        }
    }

    std::vector<FieldState> res;
    if (curState == goalState) {
        while (!(curState == emptyState)) {
            res.push_back(curState);
            curState = used.find(curState)->second;
        }
    }
    return res;
}


int main() {
    FieldArray arr;
    int buf = 0;
    for (size_t i = 0; i < FIELD_SIZE; ++i) {
        std::cin >> buf;
        arr[i] = buf;
    }
    FieldState start(arr);
    if (!start.isValid()) {
        std::cout << "no win combination" << std::endl;
        return -1;
    }
    auto res = bfs(start);
    /*for (int i = 0; i < res.size(); ++i) {
        std::cout << i+1 << " FieldState" << std::endl;
        res[i].print();
        std::cout << "===================" << std::endl;
    }*/
    //std::cout << "win combination" << std::endl;
    std::cout << res.size() - 1 << std::endl;
    std::cout << FieldState::TranslateSolution(res) << std::endl;
    return 0;
}

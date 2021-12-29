#include <iostream>
#include <string>
#include <vector>

/*
    Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
    Хранимые строки непустые и состоят из строчных латинских букв.
    Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
    Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
    когда коэффициент заполнения таблицы достигает 3/4.
    Структура данных должна поддерживать операции добавления строки в множество,
    удаления строки из множества и проверки принадлежности данной строки множеству.
    1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
    g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
 */

constexpr size_t DEFAULT_HASH_TABLE_SIZE = 8;

enum class CellStatus {
    Empty,
    Data,
    Deleted,
};

// Хеш-функция строки.
struct HashStr {
    unsigned int operator()(const std::string& str) const {
        unsigned int hash = 0;
        unsigned int hashMultiplier = 7;

        for (unsigned int i = 0; i < str.size(); ++i)
            hash = (hash * hashMultiplier + str[i]);

        return hash;
    }
};


template <class T, class H>
class HashTable {
private:
    struct Cell {
        T data;

        unsigned int absoluteHash;

        CellStatus status;

        Cell(): absoluteHash(0), status(CellStatus::Empty) {}

        Cell(const T& data, unsigned int absoluteHash): data(data), absoluteHash(absoluteHash), status(CellStatus::Data) {}
    };

    H hasher_;

    std::vector<Cell> table_;

    int keysCount_;

    void GrowTable();

public:
    explicit HashTable(const H& hasher);

    HashTable(const HashTable& table) = delete;

    HashTable& operator=(const HashTable& table) = delete;

    bool Add(const T& data);

    bool Delete(const T& data);

    bool Has(const T& data) const;
};


template <class T, class H>
HashTable<T, H>::HashTable(const H& hasher): hasher_(hasher), keysCount_(0) {
    table_.resize(0);
}


template <class T, class H>
void HashTable<T, H>::GrowTable() {
    std::vector<Cell> newTable(std::max(DEFAULT_HASH_TABLE_SIZE, table_.size() * 2));

    for (int i = 0; i < table_.size(); ++i) {
        if (table_[i].status == CellStatus::Data) {
            unsigned int absoluteHash = table_[i].absoluteHash;
            unsigned int hash = absoluteHash;
            unsigned int j = 0;

            while (newTable[hash % newTable.size()].status == CellStatus::Data) {
                hash += j + 1;
                ++j;
            }

            newTable[hash % newTable.size()] = table_[i];
        }
    }

    table_ = std::move(newTable);
}


template <class T, class H>
bool HashTable<T, H>::Add(const T &data) {
    if (4 * keysCount_ >= table_.size() * 3) {
        GrowTable();
    }

    unsigned int absoluteHash = hasher_(data);
    unsigned int hash = absoluteHash;
    unsigned int curPos = hash % table_.size();

    Cell* firstDel = nullptr;
    for (unsigned int i = 0; i < table_.size(); ++i) {
        if (table_[curPos].status == CellStatus::Deleted && !firstDel) {
            firstDel = &(table_[curPos]);
        }

        if (table_[curPos].status == CellStatus::Data && table_[curPos].data == data) {
            return false;
        }

        if (table_[curPos].status == CellStatus::Empty) {
            table_[curPos] = Cell(data, absoluteHash);
            ++keysCount_;
            return true;
        }

        hash += i + 1;
        curPos = hash % table_.size();
    }

    if (firstDel) {
        ++keysCount_;
        *firstDel = Cell(data, absoluteHash);
        return true;
    }

    return false;
}


template <class T, class H>
bool HashTable<T, H>::Delete(const T &data) {
    unsigned int hash = hasher_(data);
    unsigned int curPos = hash % table_.size();

    for (int i = 0; i < table_.size(); ++i) {
        if (table_[curPos].status == CellStatus::Data && table_[curPos].data == data) {
            table_[curPos].status = CellStatus::Deleted;
            --keysCount_;
            return true;
        }

        if (table_[curPos].status == CellStatus::Empty) {
            return false;
        }

        hash += i + 1;
        curPos = hash % table_.size();
    }

    return false;
}


template <class T, class H>
bool HashTable<T, H>::Has(const T &data) const {
    unsigned int hash = hasher_(data);
    unsigned int curPos = hash % table_.size();

    for (int i = 0; i < table_.size(); ++i) {
        if (table_[curPos].status == CellStatus::Data && table_[curPos].data == data) {
            return true;
        }

        if (table_[curPos].status == CellStatus::Empty) {
            return false;
        }

        hash += i + 1;
        curPos = hash % table_.size();
    }

    return false;
}


int main() {
    HashStr hasher;
    HashTable<std::string, HashStr> table(hasher);
    char operation = 0;
    std::string data = "";
    while (std::cin >> operation >> data) {
        switch (operation) {
            case '+':
                std::cout << (table.Add(data) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (table.Delete(data) ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                std::cout << (table.Has(data) ? "OK" : "FAIL") << std::endl;
                break;
        }
    }
    return 0;
}

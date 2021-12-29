#include <iostream>

/*
Требование для всех вариантов Задачи 4
Решение должно поддерживать передачу функции сравнения снаружи.
4_2. Порядковые статистики. Дано число N и N строк. Каждая строка
содержит команду добавления или удаления натуральных чисел, а также
запрос на получение k-ой порядковой статистики. Команда добавления числа A
задается положительным числом A, команда удаления числа A задается отрицательным
числом “-A”. Запрос на получение k-ой порядковой статистики задается числом k.
Требования: скорость выполнения запроса - O(log n).
 */


template <class T>
struct DefaultComparator {
    int operator()(const T& l, const T& r) {
        if (l < r) {
            return -1;
        } else if (l > r) {
            return 1;
        }
        return 0;
    }
};


template <class T, class Comparator = DefaultComparator<T> >
class AVLTree {
private:
    struct Node {

        Node* left;

        Node* right;

        T data;

        uint8_t height;

        int count;

        explicit Node(const T& data)
        : data(data)
        , left(nullptr)
        , right(nullptr)
        , height(1)
        , count(1) {}
    };

    Node* root_;

    Comparator cmp_;

    void DestroyTree(Node* node);

    bool HasInternal(const T& data, Node* node);

    Node* AddInternal(const T& data, Node* node);

    Node* DeleteInternal(const T &data, Node *node);

    Node* FindAndRemoveMin(Node* node, Node*& min);

    Node* FindAndRemoveMax(Node* node, Node*& max);

    Node* DoBalance(Node* node);

    Node* RotateLeft(Node* node);

    Node* RotateRight(Node* node);

    uint8_t GetHeight(Node* node) {
        return node ? node->height : 0;
    }

    void FixHeight(Node* node) {
        node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
    }

    int GetCount(Node* node) {
        return node ? node->count : 0;
    }

    void FixCount(Node* node) {
        node->count = GetCount(node->left) + GetCount(node->right) + 1;
    }

    int GetBalance(Node* node) {
        return GetHeight(node->right) - GetHeight(node->left);
    }

    T GetKOrdinalStatistic(Node* node, int k);

public:
    AVLTree() : root_(nullptr) {}

    ~AVLTree() {
        DestroyTree(root_);
    }

    bool Has(const T& data) {
        return HasInternal(data, root_);
    }

    void Add(const T& data) {
        root_ = AddInternal(data, root_);
    }

    void Delete(const T& data) {
        root_ = DeleteInternal(data, root_);
    }

    T GetKOrdinalStatistic(int k) {
        return GetKOrdinalStatistic(root_, k);
    }
};


template <class T, class Comparator>
void AVLTree<T, Comparator>::DestroyTree(Node* node) {
    if (node) {
        DestroyTree(node->left);
        DestroyTree(node->right);
        delete node;
    }
}


template <class T, class Comparator>
bool AVLTree<T, Comparator>::HasInternal(const T &data, Node *node) {
    Node* tmp = root_;

    while (tmp) {
        if (tmp->data == data) {
            return true;
        }

        int cmpRes = cmp_(data, tmp->data);
        if (cmpRes == -1) {
            tmp = tmp->left;
        } else {
            tmp = tmp->right;
        }
    }

    return false;

}


template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::AddInternal(const T &data, Node *node) {
    if (!node) {
        return new Node(data);
    }

    int cmpRes = cmp_(data, node->data);

    if (cmpRes == -1) {
        node->left = AddInternal(data, node->left);
    } else {
        node->right = AddInternal(data, node->right);
    }

    return DoBalance(node);
}


template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::RotateLeft(Node *node) {
    Node* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    FixHeight(node);
    FixCount(node);

    FixHeight(tmp);
    FixCount(tmp);

    return tmp;
}


template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::RotateRight(Node *node) {
    Node* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    FixHeight(node);
    FixCount(node);

    FixHeight(tmp);
    FixCount(tmp);

    return tmp;
}


template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::DoBalance(Node *node) {
    FixHeight(node);
    FixCount(node);

    int getBValue = GetBalance(node);
    if (getBValue == 2) {
        if (GetBalance(node->right) < 0) {
            node->right = RotateRight(node->right);
        }
        return RotateLeft(node);
    } else if (getBValue == -2) {
        if (GetBalance(node->left) > 0) {
            node->left = RotateLeft(node->left);
        }
        return RotateRight(node);
    }

    return node;
}


template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::FindAndRemoveMin(Node *node, Node*& min) {
    if (!node->left) {
        min = node;
        return node->right;
    }

    node->left = FindAndRemoveMin(node->left, min);
    return DoBalance(node);
}


template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::FindAndRemoveMax(Node *node, Node*& max) {
    if (!node->right) {
        max = node;
        return node->left;
    }

    node->right = FindAndRemoveMax(node->right, max);
    return DoBalance(node);
}


template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::DeleteInternal(const T &data, Node *node) {
    if (!node) {
        return nullptr;
    }

    int cmpRes = cmp_(data, node->data);
    if (cmpRes == -1) {
        node->left = DeleteInternal(data, node->left);
    } else if (cmpRes == 1) {
        node->right = DeleteInternal(data, node->right);
    } else {
        Node* left = node->left;
        Node* right = node->right;
        delete node;

        if (!right) {
            return left;
        }

        if (GetHeight(right) > GetHeight(left)) {
            Node* min;
            ///////////////////////////////////
            Node* tmp = FindAndRemoveMin(right, min);
            min->right = tmp;
            min->left = left;

            return DoBalance(min);
        } else {
            Node* max;
            ///////////////////////////////////
            Node* tmp = FindAndRemoveMax(left, max);
            max->left = tmp;
            max->right = right;

            return DoBalance(max);
        }
    }

    return DoBalance(node);
}


template <class T, class Comparator>
T AVLTree<T, Comparator>::GetKOrdinalStatistic(Node* node, int k) {
    int leftNodeCount = GetCount(node->left);
    if (leftNodeCount == k) {
        return node->data;
    }

    if (leftNodeCount > k) {
        return GetKOrdinalStatistic(node->left, k);
    }

    return GetKOrdinalStatistic(node->right, k - leftNodeCount - 1);
}


int main() {
    AVLTree<int> tree;
    int operations = 0;
    std::cin >> operations;
    int value = 0;
    int k = 0;
    for (int i = 0; i < operations; ++i) {
        std::cin >> value >> k;
        if (value < 0) {
            tree.Delete(std::abs(value));
        } else {
            tree.Add(value);
        }
        std::cout << tree.GetKOrdinalStatistic(k) << std::endl;
    }
    return 0;
}

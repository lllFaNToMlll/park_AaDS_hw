#include <iostream>
#include <stack>
#include <queue>
#include <vector>

/*
Задача 2. Порядок обхода (4 балла)
Обязательная задача
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
2_4. Выведите элементы в порядке level-order (по слоям, “в ширину”).
*/


template <class T>
struct Node {
    T data;

    Node* left;

    Node* right;

    explicit Node(const T& data): data(data), left(nullptr), right(nullptr) {}

};

template <class T>
struct DefaultComparator {
    bool operator()(const T& l, const T& r) {
        return l < r;
    }
};

template <class T, class Comparator = DefaultComparator<T> >
class BinaryTree {
private:
    Node<T>* root_;

    Comparator cmp_;

    void PostOrder(void (*callback)(Node<T>* node));

    void LevelOrder(void (*callback)(Node<T>* node));


    void DeleteNode(Node<T>*& node);

public:
    BinaryTree(): root_(nullptr) {};

    ~BinaryTree();

    void Add(const T& data);

    bool Delete(const T& data);

    bool Has(const T& data);

    void LevelOrderOutput();
};


template <class T, class Comp>
void BinaryTree<T, Comp>::LevelOrder(void (*callback)(Node<T>* node)) {
    if (!root_) {
        return;
    }

    std::queue<Node<T>* > queue1;
    std::queue<Node<T>* > queue2;
    queue1.push(root_);

    while (!queue1.empty()) {
        Node<T>* node = queue1.front();
        queue1.pop();
        queue2.push(node);

        if (node->left) {
            queue1.push(node->left);
        }
        if (node->right) {
            queue1.push(node->right);
        }
    }

    while (!queue2.empty()) {
        callback(queue2.front());
        queue2.pop();
    }
}


template <class T, class Comp>
void BinaryTree<T, Comp>::PostOrder(void (*callback)(Node<T>* node)) {
    if (!root_) {
        return;
    }

    std::stack<Node<T>* > stack1;
    std::stack<Node<T>* > stack2;
    stack1.push(root_);

    while (!stack1.empty()) {
        Node<T>* node = stack1.top();
        stack1.pop();
        stack2.push(node);

        if (node->left) {
            stack1.push(node->left);
        }
        if (node->right) {
            stack1.push(node->right);
        }
    }

    while (!stack2.empty()) {
        callback(stack2.top());
        stack2.pop();
    }
}


template <class T, class Comp>
BinaryTree<T, Comp>::~BinaryTree() {
    PostOrder([](Node<T>* node) {
        delete node;
    });
}


template <class T, class Comp>
void BinaryTree<T, Comp>::LevelOrderOutput() {
    LevelOrder([](Node<T>* node) {
        std::cout << node->data << " ";
    });
}


template <class T, class Comp>
void BinaryTree<T, Comp>::Add(const T& data) {
    auto newNode = new Node<T>(data);

    if (!root_) {
        root_ = newNode;
        return;
    }

    Node<T>* curNode = root_;
    Node<T>* parentNode = root_;

    while (curNode) {
        parentNode = curNode;
        if (cmp_(data, curNode->data)) {
            curNode = curNode->left;
        } else {
            curNode = curNode->right;
        }
    }

    if (cmp_(data, parentNode->data)) {
        parentNode->left = newNode;
    } else {
        parentNode->right = newNode;
    }
}


template <class T, class Comp>
bool BinaryTree<T, Comp>::Has(const T& data) {
    if (!root_) {
        return false;
    }

    Node<T>* curNode = root_;
    while (curNode && curNode->data != data) {
        if (cmp_(data, curNode->data)) {
            curNode = curNode->left;
        } else {
            curNode = curNode->right;
        }
    }

    if (!curNode) {
        return false;
    }

    return true;
}


template <class T, class Comp>
void BinaryTree<T, Comp>::DeleteNode(Node<T>*& node) {
    if (node->left == nullptr) {
        Node<T>* right = node->right;
        delete node;
        node = right;
    } else if (node->right == nullptr) {
        Node<T>* left = node->left;
        delete node;
        node = left;
    } else {
        Node<T>* minParent = node;
        Node<T>* min = node->right;

        while (min->left != nullptr) {
            minParent = min;
            min = min->left;
        }

        node->data = min->data;
        (minParent->left == min ? minParent->left : minParent->right) = min->right;

        delete min;
    }
}


template <class T, class Comp>
bool BinaryTree<T, Comp>::Delete(const T& data) {
    if (!root_) {
        return false;
    }

    Node<T>** curNode = &root_;
    while (*curNode && (*curNode)->data != data) {
        if (cmp_(data, (*curNode)->data)) {
            curNode = &(*curNode)->left;
        } else {
            curNode = &(*curNode)->right;
        }
    }

    if (!*curNode) {
        return false;
    }

    DeleteNode(*curNode);
    return true;
}


int main() {
    int elem = 0;
    std::cin >> elem;

    BinaryTree<int> tree;
    int value;
    for (int i = 0; i < elem; ++i) {
        std::cin >> value;
        tree.Add(value);
    }
    tree.LevelOrderOutput();

    return 0;
}

/*
Copyright 2019 Сергей Меликян АПО-12
Дано число N < 10^6 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root,
если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое
поддерево root. Требования: Рекурсия запрещена. Решение должно поддерживать
передачу функции сравнения снаружи. 2_1. Выведите элементы в порядке in-order
(слева направо).
*/

#include <cassert>
#include <climits>
#include <iostream>
#include <functional>
#include <sstream>
#include <vector>

using std::size_t;

template <class T> struct Comporator {
    bool operator()(const T &lhs, const T &rhs) const { return lhs > rhs; }
};

template <class T> struct node {
    node *Left;
    node *Right;
    unsigned char Height;
    T Data;

    explicit node(const T &_d)
        : Left(nullptr), Right(nullptr), Height(1), Data(_d) {}
};

template <class T, class C> class AvlTree {
  public:
    typedef node<T> treeNode;
    explicit AvlTree(const C &_comp);
    AvlTree(const C &_comp, T _d);
    ~AvlTree();

    void Add(const T &key);
    void Delete(const T &key);
    T StatK(unsigned pos) const;
    std::vector<T> InOrder();

  private:
    treeNode *treeHead;
    C comparator;

    inline unsigned char height(treeNode *n);
    inline int bFactor(treeNode *n);
    inline void fixHeight(treeNode *n);
    inline treeNode *rotateLeft(treeNode *n);
    inline treeNode *rotateRight(treeNode *n);
    inline treeNode *balance(treeNode *n);
    treeNode *insert(treeNode *n, T key);
    void deleteTree(treeNode *n);
    treeNode *deleteNode(treeNode *n, const T &key);
};

template <class T, class C>
AvlTree<T, C>::AvlTree(const C &_comp, T _d) : comparator(_comp) {
    treeHead = new treeNode(_d);
}

template <class T, class C>
AvlTree<T, C>::AvlTree(const C &_comp) : treeHead(nullptr), comparator(_comp) {}

template <class T, class C> void AvlTree<T, C>::deleteTree(treeNode *n) {
    if (n) {
        deleteTree(n->Left);
        deleteTree(n->Right);
        delete (n);
    }
    return;
}

template <class T, class C> AvlTree<T, C>::~AvlTree() { deleteTree(treeHead); }

template <class T, class C>
typename AvlTree<T, C>::treeNode *AvlTree<T, C>::insert(treeNode *n, T key) {
    if (!n)
        return new treeNode(key);
    if (comparator(key, n->Data)) {
        n->Right = insert(n->Right, key);
    } else {
        n->Left = insert(n->Left, key);
    }
    return balance(n);
}

template <class T, class C> void AvlTree<T, C>::Add(const T &key) {
    treeHead = insert(treeHead, key);
}

template <class T, class C>
typename AvlTree<T, C>::treeNode *AvlTree<T, C>::deleteNode(treeNode *n,
                                                            const T &key) {
    if (!n)
        return nullptr;
    if (comparator(key, n->Data)) {
        n = deleteNode(n->Right, key);
    } else if (!comparator(key, n->Data)) {
        n = deleteNode(n->Left, key);
    } else {
        treeNode *l = n->Left;
        treeNode *r = n->Right;

        delete (n);

        if (!l)
            return r;
        treeNode *maxLeft = [l]() {
            while (l->Right) {
                l = l->Right;
            }
            return l;
        };
        std::function<>
    }

    return balance(n);
}

template <class T, class C> void AvlTree<T, C>::Delete(const T &key) {
    treeHead = deleteNode(treeHead, key);
}

template <class T, class C> std::vector<T> AvlTree<T, C>::InOrder() {
    treeNode *current = treeHead;
    std::vector<treeNode *> stack;
    std::vector<T> retVal;
    while (!stack.empty() || current) {
        if (!stack.empty()) {
            current = stack.back();
            stack.pop_back();
            retVal.push_back(current->Data);
            if (current->Right) {
                current = current->Right;
            } else {
                current = nullptr;
            }
        }
        while (current) {
            stack.push_back(current);
            current = current->Left;
        }
    }
    return std::move(retVal);
}

template <class T, class C> unsigned char AvlTree<T, C>::height(treeNode *n) {
    return n ? n->Height : 0;
}

template <class T, class C> int AvlTree<T, C>::bFactor(treeNode *n) {
    return height(n->Right) - height(n->Left);
}

template <class T, class C> void AvlTree<T, C>::fixHeight(treeNode *n) {
    unsigned char hl = height(n->Left);
    unsigned char hr = height(n->Right);
    n->Height = (hl > hr ? hl : hr) + 1;
}

template <class T, class C>
typename AvlTree<T, C>::treeNode *AvlTree<T, C>::rotateLeft(treeNode *q) {
    treeNode *p = q->Right;
    q->Right = p->Left;
    p->Left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

template <class T, class C>
typename AvlTree<T, C>::treeNode *AvlTree<T, C>::rotateRight(treeNode *p) {
    treeNode *q = p->Left;
    p->Left = q->Right;
    q->Right = p;
    fixHeight(q);
    fixHeight(p);
    return q;
}

template <class T, class C>
typename AvlTree<T, C>::treeNode *AvlTree<T, C>::balance(treeNode *n) {
    fixHeight(n);
    if (bFactor(n) == 2) {
        if (bFactor(n->Right) < 0)
            n->Right = rotateRight(n->Right);
        return rotateLeft(n);
    }
    if (bFactor(n) == -2) {
        if (bFactor(n->Left) > 0)
            n->Left = rotateLeft(n->Left);
        return rotateRight(n);
    }
    return n;
}

template <class T> void run(std::istream &input, std::ostream &output) {
    size_t n = 0;
    input >> n;
    assert(n > 0 && n <= 1000000);
    Comporator<T> c;
    AvlTree<T, Comporator<T>> at(c);
    for (size_t i = 0; i < n; i++) {
        T data;
        // unsigned pos;
        // input >> data >> pos;
        input >> data;
        assert(data >= INT_MIN && data <= INT_MAX);
        if (c(data, static_cast<T>(0))) {
            at.Add(data);
            // output << at.StatK(pos) << std::endl;
        } else {
            at.Delete(-data);
            // output << at.StatK(pos) << std::endl;
        }
    }
    std::vector<T> ord = at.InOrder();
    for (size_t i = 0; i < n - 1; i++) {
        output << ord[i] << " ";
    }
    output << ord[n - 1];
}

void test() {
    // 1-й тест из условия
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 2 1 3";
        run<int>(input, output);
        assert(output.str() == "1 2 3");
    }
    // 2-й тест
    {
        std::stringstream input;
        std::stringstream output;
        input << "5 2 1 3 6 7";
        run<int>(input, output);
        assert(output.str() == "1 2 3 6 7");
    }
    // 3-й тест
    {
        std::stringstream input;
        std::stringstream output;
        input << "10\n9 10 4 3 2 7 8 5 1 6";
        run<int>(input, output);
        assert(output.str() == "1 2 3 4 5 6 7 8 9 10");
    }
    // 4-й тест
    {
        std::stringstream input;
        std::stringstream output;
        input << "10\n4 7 5 10 3 2 8 1 6 9";
        run<int>(input, output);
        assert(output.str() == "1 2 3 4 5 6 7 8 9 10");
    }
    // 5-й тест
    {
        std::stringstream input;
        std::stringstream output;
        input << "10\n2 3 6 1 10 8 4 9 7 5";
        run<int>(input, output);
        assert(output.str() == "1 2 3 4 5 6 7 8 9 10");
    }
    // 6-й тест
    {
        std::stringstream input;
        std::stringstream output;
        input << "8 E D H F B G C A";
        run<char>(input, output);
        assert(output.str() == "A B C D E F G H");
    }
    // 7-й тест
    {
        std::stringstream input;
        std::stringstream output;
        size_t n = 100;
        input << n << std::endl;
        for (size_t i = n; i > 0; i--) {
            input << i << " ";
        }
        std::string ethalon;
        for (size_t j = 1; j < 100; j++) {
            ethalon += std::to_string(j) + " ";
        }
        ethalon += std::to_string(n);
        run<int>(input, output);
        assert(output.str() == ethalon);
    }
}

int main(int argc, char **argv) {
    if (argc >= 2) {
        std::string s(argv[1]);
        if (s == "test") {
            test();
            return 0;
        }
    }
    run<int>(std::cin, std::cout);
    return 0;
}

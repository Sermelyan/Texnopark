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
#include <sstream>
#include <vector>

using std::size_t;

template <class T> struct Comporator {
    bool operator()(const T &lhs, const T &rhs, char oper) const {
        switch (oper) {
        case '>':
            return lhs > rhs;
        case '!':
            return lhs != rhs;
        default:
            return false;
        }
    }
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
    T StatK(unsigned pos);
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
    treeNode *deleteMaxLeft(treeNode *n);
    treeNode *findPos(treeNode *n, const unsigned &pos, unsigned *cPos);
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
typename AvlTree<T, C>::treeNode *AvlTree<T, C>::deleteMaxLeft(treeNode *n) {
    if (!n->Right) {
        return n->Left;
    }
    n->Right = deleteMaxLeft(n->Right);
    return balance(n);
}

template <class T, class C>
typename AvlTree<T, C>::treeNode *AvlTree<T, C>::deleteNode(treeNode *n,
                                                            const T &key) {
    if (!n)
        return nullptr;
    if (comparator(key, n->Data, '>')) {
        n->Right = deleteNode(n->Right, key);
    } else if (!comparator(key, n->Data, '>') &&
               comparator(key, n->Data, '!')) {
        n->Left = deleteNode(n->Left, key);
    } else {
        treeNode *l = n->Left;
        treeNode *r = n->Right;

        delete (n);

        if (!l)
            return r;

        treeNode *maxLeft = l;
        while (maxLeft->Right) {
            maxLeft = maxLeft->Right;
        }
        maxLeft->Left = deleteMaxLeft(l);
        maxLeft->Right = r;

        return balance(maxLeft);
    }

    return balance(n);
}

template <class T, class C> void AvlTree<T, C>::Delete(const T &key) {
    treeHead = deleteNode(treeHead, key);
}

template <class T, class C>
typename AvlTree<T, C>::treeNode *
AvlTree<T, C>::findPos(treeNode *n, const unsigned &pos, unsigned *cPos) {
    if (!n)
        return nullptr;

    treeNode *l = findPos(n->Left, pos, cPos);
    if (l)
        return l;

    if (pos == (*cPos)++)
        return n;

    treeNode *r = findPos(n->Right, pos, cPos);
    return r ? r : nullptr;
}

template <class T, class C> T AvlTree<T, C>::StatK(unsigned pos) {
    unsigned cPos = 0;
    treeNode *n = findPos(treeHead, pos, &cPos);
    return n ? n->Data : static_cast<T>(-1);
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
        unsigned pos;
        input >> data >> pos;
        assert(data >= INT_MIN && data <= INT_MAX);
        if (c(data, static_cast<T>(0))) {
            at.Add(data);
            output << at.StatK(pos) << std::endl;
        } else {
            at.Delete(-data);
            output << at.StatK(pos) << std::endl;
        }
    }
}

void test() {
    // 1-й тест из условия
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 1 0 2 0 -1 0";
        run<int>(input, output);
        assert(output.str() == "1\n1\n2\n");
    }
    // 1-й тест из условия
    {
        std::stringstream input;
        std::stringstream output;
        input << "5 40 0 10 1 4 1 -10 0 50 2";
        run<int>(input, output);
        assert(output.str() == "40\n40\n10\n4\n50\n");
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

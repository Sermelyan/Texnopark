/*
Copyright 2019 Сергей Меликян АПО-12
Дано число N < 10^6 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root,
если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
2_1. Выведите элементы в порядке in-order (слева направо).
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <climits>

using std::size_t;

template<class T>
struct Comporator {
    bool operator() (const T& lhs, const T& rhs) const {
        return lhs >= rhs;
    }
};

template<class T>
struct node {
    node *Parent;
    node *Left;
    node *Right;
    T Data;
    
    node(node *_p, const T& _d) : Parent(_p), Left(nullptr),
            Right(nullptr), Data(_d) {};
};

template<class T, class C>
class DecartTree {
 public:
    typedef node<T> treeNode;
    DecartTree(C _comp);
    DecartTree(C _comp, T _d);
    ~DecartTree();

    void Add(const T& data);
    std::vector<T> InOrder();
 private:
    treeNode *treeHead;
    C comparator;
};

template <class T, class C>
DecartTree<T, C>::DecartTree(C _comp, T _d) : comparator(_comp) {
    treeHead = new treeNode(nullptr, _d);
}

template <class T, class C>
DecartTree<T, C>::DecartTree(C _comp) : treeHead(nullptr), comparator(_comp) {}

template <class T, class C>
DecartTree<T, C>::~DecartTree() {
    treeNode *current = treeHead;
    while (current) {
        if (current->Left) {
            current = current->Left;
        } else if (current->Right) {
            current = current->Right;
        } else {
            treeNode *temp = current;
            current = current->Parent;
            if (current) {
                if (current->Left == temp) {
                    current->Left = nullptr;
                } else {
                    current->Right = nullptr;
                }
            }
            delete(temp);
        }
    }
}


template <class T, class C>
void DecartTree<T, C>::Add(const T& key) {
    treeNode *current = treeHead;
    if (current) {
        while (true) {
            if (comparator(key, current->Data)) {
                if (current->Right) {
                    current = current->Right;
                } else {
                    current->Right = new treeNode(current, key);
                    break;
                }
            } else {
                if (current->Left) {
                    current = current->Left;
                } else {
                    current->Left = new treeNode(current, key);
                    break;
                }
            }
        }
    } else {
        treeHead = new treeNode(nullptr, key);
    }
}

template <class T, class C>
std::vector<T> DecartTree<T, C>::InOrder() {
    treeNode *current = treeHead;
    std::vector<treeNode*> stack;
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

template<class T>
void run(std::istream& input, std::ostream& output) {
    size_t n = 0;
    input >> n;
    assert(n > 0 && n <= 1000000);
    T temp;
    input >> temp;
    Comporator<T> c;
    DecartTree<T, Comporator<T>> bt(c, temp);
    for (size_t i = 0; i < n - 1; i++) {
        input >> temp;
        assert(temp >= INT_MIN && temp <=INT_MAX);
        bt.Add(temp);
    }
    std::vector inOrd(bt.InOrder());
    for (size_t j = 0; j < inOrd.size() - 1; j++) {
        output << inOrd[j] << " ";
    }
    output << inOrd.back();
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

int main(int argc, char** argv) {
    if (argc >=  2) {
        std::string s(argv[1]);
        if (s == "test") {
            test();
            return 0;
        }
    }
    run<int>(std::cin, std::cout);
    std::cout << std::endl;
    return 0;
}

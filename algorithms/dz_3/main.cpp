/*
Copyright 2019 Сергей Меликян АПО-12
3_1. Реализовать очередь с динамическим зацикленным буфером.
Требования: Очередь должна быть реализована в виде класса.
*/


#include <cassert>
#include <iostream>
#include <sstream>

template<class T>
class Queue {
 public:
    Queue();
    ~Queue();

    void Enqueue(const T& data);
    T Dequeue();
    [[nodiscard]] bool IsEmpty() const;

    Queue(const Queue&) = delete;
    Queue(const Queue&&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue& operator=(const Queue&&) = delete;

 private:
    T* buffer;

    size_t head;
    size_t tail;
    size_t count;
    size_t size;

    void growUp();
};

template<class T>
Queue<T>::Queue() : buffer(nullptr), head(0), tail(0), count(0), size(4) {
    buffer = new T[size];
}

template<class T>
Queue<T>::~Queue() {
    delete[] buffer;
}

template<class T>
void Queue<T>::Enqueue(const T& data) {
    if (count + 1 > size)
        growUp();
    buffer[tail] = data;
    tail = (tail + 1) % size;
    count++;
}

template<class T>
T Queue<T>::Dequeue() {
    assert(!IsEmpty());
    T temp = buffer[head];
    head = (head + 1) % size;
    count--;
    return temp;
}

template<class T>
bool Queue<T>::IsEmpty() const {
    return count == 0;
}

template<class T>
void Queue<T>::growUp() {
    size_t prevSize = size;
    size *= 2;
    T* temp = new T[size];
    for (size_t i = 0; i < tail; i++) {
        temp[i] = buffer[i];
    }
    head = size - (prevSize - head);
    for (size_t j = size - 1, o = prevSize - 1; j >= head; j--, o--) {
        temp[j] = buffer[o];
    }
    delete[] buffer;
    buffer = temp;
}

void run(std::istream& input, std::ostream& output) {
    Queue<int> q;
    int n = 0;
    input >> n;
    assert(n < 1000000);
    bool result = true;
    for (int i = 0; i < n; i++) {
        int command = 0;
        int data = 0;
        input >> command >> data;
        switch (command) {
            case 2:
                if (q.IsEmpty()) {
                    result = result && data == -1;
                } else {
                    result = result && data == q.Dequeue();
                }
                break;
            case 3:
                q.Enqueue(data);
                break;
            default:
                assert(false);
        }
    }
    if (!result) {
        output << ("NO");
    } else {
        output << ("YES");
    }
}

void test() {
    {
        Queue<int> q;
        assert(q.IsEmpty());
        for (int i = 0; i < 10; i++)
            q.Enqueue(i);
        assert(!q.IsEmpty());
        for (int i = 0; i < 10; i++)
            assert(q.Dequeue() == i);
        assert(q.IsEmpty());
    }
    //  1-й тест из условия
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 3 44 3 50 2 44";
        run(input, output);
        assert(output.str() == "YES");
    }
    //  3-й тест из условия
    {
        std::stringstream input;
        std::stringstream output;
        input << "2 3 44 2 66";
        run(input, output);
        assert(output.str() == "NO");
    }
    //  проверка на пустую очередь
    {
        std::stringstream input;
        std::stringstream output;
        input << "1 2 -1";
        run(input, output);
        assert(output.str() == "YES");
    }
    //  проверка на большое количество операций
    {
        std::stringstream input;
        std::stringstream output;
        int count = 10000;
        input << count * 2 << std::endl;
        for (int i = 0; i < count; i++)
            input << "3 " << i << std::endl;
        for (int i = 0; i < count; i++)
            input << "2 " << i << std::endl;
        run(input, output);
        assert(output.str() == "YES");
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
    run(std::cin, std::cout);
    std::cout << std::endl;
    return 0;
}

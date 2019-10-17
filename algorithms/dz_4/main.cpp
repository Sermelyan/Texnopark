#include <iostream>
#include <cstring>
#include <cassert>
#include <sstream>
//Считаю сумму двух минимумов. Накапливаю ее и пихаю в кучу. Пока куча не опустеет.

template<class T>
class Vector {
 public:
    Vector() : size(4), pointer(0) {
        buffer = new T[size];
    }

    explicit Vector(std::size_t n) : size(n), pointer(0) {
        buffer = new T[size];
    }

    ~Vector() {
        delete[] buffer;
    }

    void PushBack(const T& element) {
        if (pointer == size)
            growUp();
        buffer[pointer++] = element;
    }

    T PopBack() {
        assert(pointer != 0);
        return buffer[--pointer];
    }

    [[nodiscard]] std::size_t Size() const {
        return pointer;
    }

    [[nodiscard]] bool IsEmpty() const {
        return pointer == 0;
    }

    T operator[](std::size_t n)  const {
        assert(n <= pointer);
        return buffer[n];
    }

    T& operator[](std::size_t n) {
        assert(n <= pointer);
        return buffer[n];
    }

    void Resize(std::size_t newSize) {
        assert(newSize > size);
        T* temp = new T[newSize];
        memcpy(temp, buffer, sizeof(T)*size);
        size = newSize;
        delete[] buffer;
        buffer = temp;
    }

    Vector(const Vector& v) : pointer(v.pointer), size(v.size) {
        buffer = new T[size];
        memcpy(buffer, v.buffer, sizeof(T)*pointer);
    }

    Vector(const Vector&&) = delete;
    Vector& operator=(const Vector&) = delete;
    Vector& operator=(const Vector&&) = delete;

 private:
    std::size_t size;
    std::size_t pointer;
    T *buffer;
    void growUp() {
        T* temp = new T[(size + 1)*2];
        memcpy(temp, buffer, sizeof(T)*size);
        size = (size + 1)*2;
        delete[] buffer;
        buffer = temp;
    }
};

template <class T>
class Heap {
 public:
    Heap() = default;
    explicit Heap(const Vector<T> _arr) : arr(_arr) {
        for (int64_t i = arr.Size() / 2 - 1; i >= 0; i--) {
            siftDown(i);
        }
    }
    ~Heap() = default;

    void Insert(T element) {
        arr.PushBack(element);
        siftUp(arr.Size() - 1);
    }

    T ExtractMin() {
        assert(!arr.IsEmpty());
        T result = arr[0];
        arr[0] = arr.PopBack();
        if(!arr.IsEmpty()) {
            siftDown(0);
        }
        return result;
    }

    [[nodiscard]] bool IsEmpty() const {
        return arr.IsEmpty();
    }
 private:
    Vector<T> arr;
    void siftDown(std::size_t i) {
        std::size_t left = 2 * i + 1;
        std::size_t right = 2 * i + 2;
        std::size_t smallest = i;
        if(left < arr.Size() && arr[left] < arr[i])
            smallest = left;
        if(right < arr.Size() && arr[right] < arr[smallest])
            smallest = right;
        if(smallest != i) {
            std::swap(arr[i], arr[smallest]);
            siftDown(smallest);
        }
    }

    void siftUp(std::size_t index) {
        while(index > 0) {
            std::size_t parent = (index - 1) / 2;
            if(arr[index] >= arr[parent])
                return;
            std::swap(arr[index], arr[parent]);
            index = parent;
        }
    }
};

unsigned int calcTime(Heap<unsigned int>& h) {
    unsigned int sum = 0;
    while (!h.IsEmpty()) {
        unsigned int temp = h.ExtractMin();
        if (!h.IsEmpty()) {
            temp += h.ExtractMin();
        }
        if (!h.IsEmpty()) {
            h.Insert(temp);
        }
        sum += temp;
    }
    return sum;
}

void run(std::istream& input, std::ostream& output) {
    Heap<unsigned int> h;
    std::size_t n = 0;
    input >> n;
    assert(n < 100);
    for (std::size_t i = 0, sum = 0; i < n; i++) {
        unsigned int temp;
        input >> temp;
        assert(temp > 0 && temp < 1000000000);
        sum += temp;
        assert(sum < 2000000000);
        h.Insert(temp);
    }
    output << calcTime(h);
}

void test() {
    {
        Vector<int> v;
        assert(v.IsEmpty());
        for (int i = 9; i > -1; i--) {
            v.PushBack(i);
        }
        assert(!v.IsEmpty());
        Heap<int> h(v);
        for (int i = 0; i < 10; i++)
            assert(h.ExtractMin() == i);
        assert(h.IsEmpty());
    }
    {
        Heap<int> h;
        assert(h.IsEmpty());
        for (int i = 9; i > -1; i--)
            h.Insert(i);
        assert(!h.IsEmpty());
        for (int i = 0; i < 10; i++)
            assert(h.ExtractMin() == i);
        assert(h.IsEmpty());
    }
    //  1-й тест из условия
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 3 2 1";
        run(input, output);
        assert(output.str() == "9");
    }
    //  2-й тест из условия
    {
        std::stringstream input;
        std::stringstream output;
        input << "5 5 2 3 4 6";
        run(input, output);
        assert(output.str() == "45");
    }
    //  3-й тест из условия
    {
        std::stringstream input;
        std::stringstream output;
        input << "5 3 7 6 1 9";
        run(input, output);
        assert(output.str() == "56");
    }
    // Тест на сокрость
    {
        std::stringstream input;
        std::stringstream output;
        input << 99 << std::endl;
        for (size_t i = 1; i < 100 ; i++) {
            input << i << " ";
        }
        run(input, output);
        std::cout << output.str();
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

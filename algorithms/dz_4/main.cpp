#include <iostream>
#include <cstring>
#include <cassert>
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
    Heap() {};
    explicit Heap(const Vector<T> _arr) : arr(_arr){
        for(long i = arr.Size() / 2 - 1; i >= 0; i--) {
            siftDown(i);
        }
    }
    ~Heap() {};

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

int main() {
    Vector<int> v;
    for (int i = 10000; i >= 0; i--) {
        v.PushBack(i);
    }
    Heap<int> h(v);
    while (!h.IsEmpty()) {
        std::cout << h.ExtractMin() << std::endl;
    }
    
    return 0;
}

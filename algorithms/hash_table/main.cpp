/*
Copyright 2019 Сергей Меликян АПО-12

*/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <sstream>

using std::size_t;

typedef enum condition {
    Deleted,
    Nil,
    Used
} State;

template<class T>
struct ArrayElement {
    T Data;
    State Cond;

    ArrayElement() : Cond(Nil) {}
};

template<class T, class H>
class HashTable {
 public:
    explicit HashTable(const H& hasher, size_t _size = 8);
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    ~HashTable() = default;

    bool Add(const T& data);
    bool Has(const T& data);
    bool Delete(const T& data);
 private:
    std::vector<ArrayElement<T>> table;
    H hasher;
    int keysCount;
    size_t size;

    void growTable();
};

template<class T, class H>
HashTable<T, H>::HashTable(const H& _hasher, size_t _size) :
        hasher(_hasher),
        table(_size),
        size(_size),
        keysCount(0) {}

template<class T, class H>
bool HashTable<T, H>::Add(const T& data) {
    if (keysCount > (2 * size) / 3)
        growTable();

    size_t i = 0;
    size_t rawHash = hasher(data);
    size_t hash = rawHash % size;
    size_t firstHash = hash;
    long pos = -1;

    while (table[hash].Cond != Nil) {
        if (table[hash].Cond == Deleted) {
            pos = (pos == -1) ? hash : pos;
        } else if (table[hash].Data == data) {
            return false;
        }
        i++;
        hash = (rawHash + (i * (i + 1)) / 2) % size;
        if (hash == firstHash) {
            assert( pos != -1 );
            break;
        }
    }
    pos = (pos == -1) ? hash : pos;
    table[pos].Data = data;
    table[pos].Cond = Used;

    ++keysCount;
    return true;
}

template<class T, class H>
void HashTable<T, H>::growTable() {
    size_t nSize = size * 2;
    std::vector<ArrayElement<T>> newTable(nSize);
    for (size_t i = 0; i < size; i++) {
        if (table[i].Cond != Used)
            continue;

        T data = table[i].Data;
        size_t j = 0; 
        size_t rawHash = hasher(data);
        size_t hash = rawHash % nSize;

        while (newTable[hash].Cond == Used) {
            j++;
            hash = (rawHash + (j * (j + 1)) / 2) % nSize;
        }
        newTable[hash].Data = data;
        newTable[hash].Cond = Used;
    }
    table = std::move(newTable);
    size = nSize;
}

template<class T, class H>
bool HashTable<T, H>::Has(const T& data) {
    size_t i = 0;
    size_t rawHash = hasher(data);
    size_t hash = rawHash % size;
    size_t firstHash = hash;

    while (table[hash].Cond != Nil) {
        if (table[hash].Cond != Deleted && table[hash].Data == data) {
            return true;
        }

        i++;
        hash = (rawHash + (i * (i + 1)) / 2) % size;
        if (hash == firstHash) {
            return false;
        }
    }

    return false;
}

template<class T, class H>
bool HashTable<T, H>::Delete(const T& data) {
    if (!this->Has(data))
        return false;

    size_t i = 0;
    size_t rawHash = hasher(data);
    size_t hash = rawHash % size;
    size_t firstHash = hash;

    while (table[hash].Cond != Used && table[hash].Data != data) {
        i++;
        hash = (rawHash + (i * (i + 1)) / 2) % size;
        if (hash == firstHash) {
            return false;
        }
    }

    table[hash].Cond = Deleted;
    --keysCount;
    return true;
}

struct Hasher {
    int operator()(const std::string& data) const {
        int hash = 0;
        for (int i = 0; i < data.length(); i++)
            hash = hash * 278345579051 + data[i];
        return hash;
    }
};

void run(std::istream& input, std::ostream& output) {
    Hasher h;
    HashTable<std::string, Hasher> table(h, 100000);
    char operation;
    std::string word;
    while (input >> operation >> word) {
        switch (operation) {
        case '+':
            output << (table.Add(word) ? "OK" : "FAIL") << std::endl;
            break;
        case '?':
            output << (table.Has(word) ? "OK" : "FAIL") << std::endl;
            break;
        case '-':
            output << (table.Delete(word) ? "OK" : "FAIL") << std::endl;
            break;
        default:
            output << "Invalid command" << std::endl;
            break;
        }
    }
}

void test() {
    //  1-й тест из условия
    {
        std::stringstream input;
        std::stringstream output;
        input << "+ hello\n+ bye\n? bye\n+ bye\n- bye\n? bye\n? hello\n";
        run(input, output);
        assert(output.str() == "OK\nOK\nOK\nFAIL\nOK\nFAIL\nOK\n");
    }
    {
        Hasher h;
        HashTable<std::string, Hasher> table(h);
        std::string t = "test";
        for (size_t i = 0; i < 1000; i++) {
            assert(table.Add(t + std::to_string(i)));
        }
        for (size_t i = 0; i < 1000; i++) {
            assert(table.Has(t + std::to_string(i)));
        }
        for (size_t i = 0; i < 1000; i++) {
            std::cout << i << std::endl;
            assert(table.Delete(t + std::to_string(i)));
        }
        for (size_t i = 0; i < 1000; i++) {
            assert(!table.Has(t + std::to_string(i)));
        }
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
    return 0;
}

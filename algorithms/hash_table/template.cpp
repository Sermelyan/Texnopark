
//
// Created by ser on 14.11.2019.
//

#include<iostream>
#include<vector>
#include<assert.h>
#include<string>

using std::vector;
using std::string;
using std::cin;
using std::cout;

template<class T>
struct HashTableNode {
    T Data;
    HashTableNode* Next;

    HashTableNode() : Next(nullptr) {}
    HashTableNode(const T& data, HashTableNode* next) : Data(data), Next(next) {}
};

template<class T, class H>
class HashTable {
public:
    HashTable(const H& hasher);
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    ~HashTable();

    bool Add(const T& data);
    bool Has(const T& data);
    bool Delete(const T& data);

private:
    H hasher;
    vector<HashTableNode<T>*> table;
    int keysCount;

    void growTable();
};

template<class T, class H>
HashTable<T, H>::HashTable(const H& _hasher) :
        hasher(_hasher),
        table(8, nullptr),
        keysCount(0)
{
}

template<class T, class H>
HashTable<T, H>::~HashTable()
{
    for (int i = 0; i < table.size(); i++) {
        HashTableNode<T>* node = table[i];
        while (node != nullptr) {
            HashTableNode<T>* nextNode = node->Next;
            delete node;
            node = nextNode;
        }
    }
}

template<class T, class H>
bool HashTable<T, H>::Add(const T& data)
{
    if (keysCount > 3 * table.size())
        growTable();

    int hash = hasher(data) % table.size();
    HashTableNode<T>* node = table[hash];
    while (node != nullptr && node->Data != data) {
        node = node->Next;
    }

    if (node != nullptr)
        return false;

    table[hash] = new HashTableNode<T>(data, table[hash]);
    ++keysCount;
}

template<class T, class H>
void HashTable<T, H>::growTable()
{
    vector<HashTableNode<T>*> newTable(table.size() * 2, nullptr);
    for (int i = 0; i < table.size(); i++) {
        HashTableNode<T>* node = table[i];
        while (node != nullptr) {
            HashTableNode<T>* nextNode = node->Next;
            int newHash = hasher(node->Data) % newTable.size();
            node->Next = newTable[newHash];
            newTable[newHash] = node;
            // Переходит к следующему узлу
            node = nextNode;
        }
    }
    table = std::move(newTable);
}

template<class T, class H>
bool HashTable<T, H>::Has(const T& data)
{
    int hash = hasher(data) % table.size();
    HashTableNode<T>* node = table[hash];
    while (node != nullptr && node->Data != data) {
        node = node->Next;
    }
    return node != nullptr;
}

template<class T, class H>
bool HashTable<T, H>::Delete(const T& data)
{
    int hash = hasher(data) % table.size();
    HashTableNode<T>* node = table[hash];

    HashTableNode<T>* prevNode = nullptr;
    while (node != nullptr && node->Data != data) {
        prevNode = node;
        node = node->Next;
    }
    if (node == nullptr)
        return false;

    if (prevNode == nullptr) { // node первый в списке
        table[hash] = node->Next;
    } else {
        prevNode->Next = node->Next;
    }
    delete node;
    --keysCount;
    return true;
}

struct Hasher
{
    int operator()(const string& data) const
    {
        int hash = 0;
        for (int i = 0; i < data.length(); i++)
            hash = hash * 7 + data[i];
        return hash;
    }
};

int main()
{
    Hasher h;
    HashTable<string, Hasher> table(h);
    char operation;
    string word;
    while (cin >> operation >> word) {
        if (operation == '+')
            cout << (table.Add(word) ? "OK" : "FAIL") << std::endl;
        if (operation == '?')
            cout << (table.Has(word) ? "OK" : "FAIL") << std::endl;
        if (operation == '-')
            cout << (table.Delete(word) ? "OK" : "FAIL") << std::endl;
    }
    return 0;
}

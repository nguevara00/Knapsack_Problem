#include "HashTable.h"

int HashTable::hash(int i, int j, int& opCount){
    return ((i-1) * W + j) % k;
    opCount++;
}

HashTable::HashTable(const int& k, const int& W){
    this->k = k;
    this->W = W;

    buckets.resize(k, nullptr);
}

void HashTable::insert(int i, int j, int value){
    int index = hash(i,j);
    Node* newNode = new Node;
    newNode->i = i;
    newNode->j = j;
    newNode->value = value;
    newNode->next = buckets[index];
    buckets[index] = newNode;
    }

int HashTable::lookup(int i, int j, int& opCount){
    int index = hash(i,j);
    Node* current = buckets[index];
    while (current != nullptr){
        opCount++;
        if (current->i == i && current->j == j) {
            return current->value;
        }
        current = current->next;    
    }
    return -1;
}

HashTable::~HashTable(){
    for (size_t i = 0; i < buckets.size(); i++){
        Node* current = buckets[i];
        while (current != nullptr){
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
}

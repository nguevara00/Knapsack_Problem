#include "HashTable.h"

int HashTable::hash(int i, int j){
    return ((i-1) * W + j) % k;
}

HashTable::HashTable(const int& k, const int& W, const int& n){
    this->k = k;
    this->W = W;
    buckets.resize(k, nullptr);
    this->n = n;
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

int HashTable::lookup(int i, int j, int& basicOps){
    basicOps++;
    int index = hash(i,j);
    Node* current = buckets[index];
    while (current != nullptr){
        basicOps++;
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

//int HashTable::hash(int i, int j){
//    int b_n = static_cast<int>(ceil(log2(n+1)));
//    int b_w = static_cast<int>(ceil(log2(W+1)));
//

//    return static_cast<int>((((std::pow(2, b_n)) + i) * std::pow(2, b_w) +j)) % k;
//}
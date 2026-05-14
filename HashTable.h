#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>

class HashTable{
private:
    struct Node{
        int i;
        int j;
        int value;
        Node* next;
    };

    std::vector<Node*> buckets;
    int k;
    int W;

    //returns the hash for i,j to choose bucket
    int hash(int i, int j, int& opCount);

public:
    //builds a hashtable with k buckets
    HashTable(const int& k, const int& W);

    //inserts cell(i,j) with its value into the hash table
    void insert(int i, int j, int value);

    //returns the value if it is found, or -1 if it is not found
    int lookup(int i, int j, int& opCount);

    //destructor to clean up allocated memory
    ~HashTable();
};
#endif

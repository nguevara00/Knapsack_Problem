#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <cmath>

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
    int n;

    //returns the hash for i,j to choose bucket
    int hash(int i, int j);

public:
    //builds a hashtable with k buckets
    HashTable(const int& k, const int& W, const int& n);

    //inserts cell(i,j) with its value into the hash table
    void insert(int i, int j, int value);

    //returns the value if it is found, or -1 if it is not found
    int lookup(int i, int j, int& basicOps);

    //destructor to clean up allocated memory
    ~HashTable();
};
#endif

//
// Created by Yuval on 01/01/2018.
//

#ifndef COLOSSEUM2_HASHTABLE_H
#define COLOSSEUM2_HASHTABLE_H

#include <exception>
#include "AVL.h"
/*
 * an open addressing hashtable. expand_factor and initial size must be coprime with r(x)
 */
class ElementAlreadyExists : public std::exception{};
class ElementDoesntExist : public std::exception{};
// important note: only objects that have the == overloaded operator can be used.
template<class T>
class HashTable {
    AVLTree<T> **table;
    int max_size;
    int current_size;
    int expand_factor;
    int h(const T& x);
    void expand();
public:
    HashTable(int initial_size,int expand_factor);
    void insert(const T& x);
    void deleteElement(const T& x);
    bool member(const T& x);
};
template <class T>
int HashTable::h(const T &x) {
    return x%max_size;
}
template <class T>
void HashTable::expand() {
    AVLTree<T>** new_table=new AVLTree<T> *[max_size*expand_factor];
    for(int i=0;i<max_size*expand_factor;i++){
        new_table[i]= nullptr;
    }
    max_size=max_size*expand_factor;
    for(int i=0;i<max_size/expand_factor;i++){
        if(table[i]!= nullptr) {
            int size;
            T* table_array;
            table[i]->ToArray(table_array,&size);
            for(int i=0;i<size;i++){
                new_table[h(table_array[i])]->Add(table_array[i]);
            }
            delete[](table_array);
            delete(table[i]);
        }
    }
    delete[] table;
    table=new_table;
}
template<class T>
HashTable::HashTable(int initial_size, int expand_factor) : max_size(initial_size),
                                                            expand_factor(expand_factor),
                                                            current_size(0),
                                                            table(new AVLTree<T>*[initial_size]){
    for (int i = 0; i < initial_size; ++i) {
        table[i] = nullptr;
    }
}

template <class T>
void HashTable::insert(const T &x) {
    int position=h(x);
    if(table[position] == nullptr){
        table[position]=new AVLTree<T>(x);
    }
    if(table[position]->Add(x)==false){
        throw ElementAlreadyExists();
    }
}

template <class T>
void HashTable::deleteElement(const T &x) {
    int position=h(x);
    if(table[position]== nullptr){
        throw ElementDoesntExist();
    }
    if(table[position]->Remove(x)== false){
        throw ElementDoesntExist();
    }
}

template <class T>
bool HashTable::member(const T &x) {
    int position=h(x);
    if(table[position] == nullptr){
        return false;
    }
    if(table[position]->find())
}

#endif //COLOSSEUM2_HASHTABLE_H

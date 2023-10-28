#include "dllist.h"
#include <cassert>
#include <iostream>

template <typename T>
struct dllnode
{
    T data;
    dllnode *next, *prev;
};


template<typename T>
void printdll(dllnode<T>* list) {
    while (list != nullptr) {
        std::cout << list->data << " -> ";
        if (list->next != nullptr && list->next->prev != list) {
            std::cerr << "\nERROR IN LIST POINTERS FOR ELEMENTS "
                      << list->data
                      << " and "
                      << list->next->data
                      << "\n";
                      
        }
        list = list->next;
    }
    std::cout << "NULL\n";
}


template <typename T>
int count(dllnode<T>* l, const T& x) {
    int counter = 0;
    while(l != nullptr) {
        if(l->data == x) {
            counter++;
        }
        l = l->next;
    }
    return counter;
}

dllnode<int>* range(int x, int y) {
    if(x > y) {
        return nullptr;
    }
    dllnode<int>* first = new dllnode<int>{y,nullptr,nullptr};
    for(--y; y >= x; --y)
    {
        first->prev = new dllnode<int>{y, first, nullptr};
        first = first->prev;
    }
    return first;
}

void testRange() {
    // Test 1: Basic test
    dllnode<int>* list1 = range(1, 5);
    dllnode<int>* curr = list1;
    for (int i = 1; i <= 5; ++i) {
        assert(curr->data == i);
        curr = curr->next;
    }

    // Test 2: Range with only one number
    dllnode<int>* list2 = range(3, 3);
    assert(list2->data == 3);
    assert(list2->next == nullptr);
    assert(list2->prev == nullptr);

    // Test 3: Range with negative numbers
    dllnode<int>* list3 = range(-2, 2);
    curr = list3;
    for (int i = -2; i <= 2; ++i) {
        assert(curr->data == i);
        curr = curr->next;
    }
}

template <typename T>
void removeAll (dllnode<T>*& l,const T& x) {
    if (l == nullptr)
    {
        return;
    }

    dllnode<T> * curr = l;
    while(curr) {
        if (curr->data == x) {

            if (curr->prev != nullptr) {
                curr->prev->next = curr->next;
            } else {
                l = l->next;
            }

            if (curr->next != nullptr) {
                curr->next->prev = curr->prev;
            }
            dllnode<T>* toBeDel = curr;
            curr = curr->next;
            delete toBeDel;
            // OR
            // delete std::exchange(curr, curr->next);
        } else {
            curr = curr->next;
        }
    }
    
}

void testCount() {
    dllnode<int>* n1 = new dllnode<int>{1, nullptr, nullptr};
    dllnode<int>* n2 = new dllnode<int>{2, nullptr, nullptr};
    dllnode<int>* n3 = new dllnode<int>{2, nullptr, nullptr};
    dllnode<int>* n4 = new dllnode<int>{4, nullptr, nullptr};
    dllnode<int>* n5 = new dllnode<int>{4, nullptr, nullptr};
    dllnode<int>* n6 = new dllnode<int>{4, nullptr, nullptr};
    // Linking the nodes
    n1->prev = nullptr;
    n1->next = n2;
    n2->prev = n1;
    n2->next = n3;
    n3->prev = n2;
    n3->next = n4;
    n4->prev = n3;
    n4->next = n5;
    n5->prev = n4;
    n5->next = n6;
    n6->prev = n5;
    n6->next = nullptr;

    assert(count(n1, 1) == 1);
    assert(count(n1, 2) == 2);
    assert(count(n1, 4) == 3);
    assert(count(n1, 3) == 0);
}

void testRemoveAll() {
    // Test 1: Remove element from the middle
    dllnode<int>* list1 = range(1, 5);
    removeAll(list1, 1);
    assert(list1->data == 2);
    assert(list1->next->data == 3);
    assert(list1->next->next->data == 4);
    assert(list1->next->next->next->data == 5);
    assert(list1->next->next->next->next == nullptr);
}

template<typename T>
dllnode<T>* copyList(dllnode<T>* l)
{
    if(l == nullptr)
    {
        return l; 
    }
    dllnode<T>* iter = new dllnode<T>{l->data, nullptr,nullptr};
    dllnode<T>* firstNew = iter; 
    while(l->next != nullptr)
    {
        iter->next = new dllnode<T>{l->next->data,nullptr,iter};
        l = l->next;
        iter = iter->next;
    }

    return firstNew;
}

template<typename T>
void append(dllnode<T>*& l1, dllnode<T>* l2) {
    
    if(l1 == nullptr)
    {
        l1 = copyList(l2);
        return;
    }
    dllnode<T>* l2Copy = copyList(l2);
    dllnode<T>* iter = l1;
    while (iter->next != nullptr)
    {
        iter = iter->next;
    }

    iter->next = l2Copy;
    l2Copy->prev = iter;
    
}

void testAppend() {
    dllnode<int>* n1 = new dllnode<int>{1, nullptr, nullptr};
    dllnode<int>* n2 = new dllnode<int>{2, nullptr, nullptr};
    dllnode<int>* n3 = new dllnode<int>{2, nullptr, nullptr};
    dllnode<int>* n4 = new dllnode<int>{4, nullptr, nullptr};
    dllnode<int>* n5 = new dllnode<int>{4, nullptr, nullptr};
    dllnode<int>* n6 = new dllnode<int>{4, nullptr, nullptr};
    // Linking the nodes
    n1->next = n2;
    n2->prev = n1;
    n2->next = n3;
    n3->prev = n2;

    n4->next = n5;
    n5->prev = n4;
    n5->next = n6;
    n6->prev = n5;

    printdll(n1);
    printdll(n4);

    append(n1, n4);

    printdll(n1);

    dllnode<int>* empty = nullptr;

    append(empty, n1);
    printdll(empty);
}

template <typename T>
dllnode<T>* concat(dllnode<T>* l1, dllnode<T>* l2) {
    dllnode<T>* result = copyList(l1);
    append(result, l2);
    return result;
}


void testConcat() {
    auto l1 = range(1, 3);
    auto l2 = range(4, 6);
    auto concatenated = concat(l1, l2);
    assert(l1 != concatenated);
    assert(l1->next->next->next != concatenated->next->next->next);
}

template <typename T>
void removeDuplicates (dllnode<T> *&l) {
    if(l==nullptr || l->next==nullptr){ return; }

    dllnode<T>* first = l;

    while(first->next!=nullptr) {
        dllnode<T>* second = first->next;
        while(second!=nullptr) {
            if(first->data == second->data){
                second->prev->next = second->next;
                if(second->next != nullptr){
                    second->next->prev = second->prev;
                }
                delete std::exchange(second, second->next);
            } else {
                second = second->next;
            }
        }
        first = first->next;
        
    }
}


void testRemoveDuplicates() {
    dllnode<int>* n1 = new dllnode<int>{1, nullptr, nullptr};
    dllnode<int>* n2 = new dllnode<int>{1, nullptr, nullptr};
    dllnode<int>* n3 = new dllnode<int>{1, nullptr, nullptr};
    dllnode<int>* n4 = new dllnode<int>{1, nullptr, nullptr};
    dllnode<int>* n5 = new dllnode<int>{2, nullptr, nullptr};
    dllnode<int>* n6 = new dllnode<int>{1, nullptr, nullptr};
    // Linking the nodes
    n1->prev = nullptr;
    n1->next = n2;
    n2->prev = n1;
    n2->next = n3;
    n3->prev = n2;
    n3->next = n4;
    n4->prev = n3;
    n4->next = n5;
    n5->prev = n4;
    n5->next = n6;
    n6->prev = n5;
    n6->next = nullptr;
    
    removeDuplicates(n1);
    printdll(n1);
}


int main() {
    testRemoveDuplicates();
    return 0;
    testAppend();
    testRange();
    testRemoveAll();

    DLList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    DLList<int> list2;


    // for(int x : list ) {
    //     std::cout <<x << std::endl;
    // }
    // list.reverse();

    
    // for(int x : list ) {
    //     std::cout <<x << std::endl;
    // }
}
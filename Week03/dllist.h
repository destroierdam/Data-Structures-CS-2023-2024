#pragma once

template <typename T>
class DLList
{
    public:
    DLList();
    DLList(const DLList&);
    DLList(DLList&&);

    void push_front(const T&);
    void push_back(const T&);
    unsigned int size() const;

    bool pop_back();
    bool pop_front();

    private:
    struct node
    {
        T data;
        node *next, *prev;
    };

    public:
    class iterator
    {
        public:

        iterator(node *ptr, node* const *);

        T operator*() const;
        iterator& operator++();
        iterator& operator--();
        bool operator != (const iterator&);
        bool operator == (const iterator&);

        private:
        node* current;
        node* const* ptr_to_last;
    };

    iterator begin();
    iterator end();
    
    void remove(const iterator&);
    void reverse();
    void operator+=(const DLList<T>& other) {
        for(DLList<T>::iterator it = other.begin(); it != other.end(); ++it) {
            this->push_back(*it);
        }
        // ILI
        // for(const T& element : other) {
        //     this->push_back(element);
        // }
    }
    DLList<T> operator+(const DLList<T>& other) const {
        DLList<T> result = *this;
        result += other;
        return result;
    }

    ~DLList();
    
private:
    node *first, *last;
    unsigned count;
};

#include "dllist.imp"

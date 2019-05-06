#ifndef SET_H
#define SET_H

#include <string>
#include <iostream>
#include <cstdlib>

// use a type alias
using ItemType = std::string;

class Set
{
public:
    Set();
    // Create an empty set with the given capacity.
    
    bool empty() const;  // Return true if the set is empty, otherwise false.
    int size() const;    // Return the number of items in the set.
    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    
    bool erase(const ItemType& value);
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the set, otherwise false.
    
    bool get(int pos, ItemType& value) const;
    // If 0 <= pos < size(), copy into value the item in the set that is
    // strictly greater than exactly pos items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    
    void swap(Set& other);
    // Exchange the contents of this set with the other one.
    
    // Housekeeping functions
    ~Set();
    Set(const Set& other);
    Set& operator=(const Set& rhs);
    
private:
    int       m_size;        // the number of items in the set
    // At any time, the elements of m_data indexed from 0 to m_size-1
    // are in use and are stored in increasing order.
    struct Node    //struct for Nodes of the linked lists
    {
        // Node();
        ItemType data;
        Node* next;
        Node* prev;
        //~Node();
    };
    Node* head;
    Node* tail;
};

// Inline implementations

inline
int Set::size() const
{
    return m_size;
}

inline
bool Set::empty() const
{
    return size() == 0;
}

inline
bool Set::contains(const ItemType& value) const
{
    if (size() <= 0)
    {
        return false;
    }
    Node *p;
    for (p = head; p != nullptr && p->data != value; p = p->next) //go through linked list
    {
        ;
    }
    if (p == nullptr)  //does not contain
    {
        return false;
    }
    
    else {
        return true;
        
    }
}
void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif // SET_H

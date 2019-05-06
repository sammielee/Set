#include "Set.h"
#include <iostream>
using namespace std;

//#include <string>

Set::Set()
: m_size(0)
{
    head = nullptr;
    tail = nullptr;
}

bool Set::insert(const ItemType& value)
{
    if (contains(value))
        return false;
    Node *n = new Node();  //create new Node and assign it
    n->data = value;
    if (m_size == 0)  //set the first item as the head and tail
    {
        head = n;
        tail = n;
        n->next = nullptr;
        n->prev = nullptr;
        m_size++;
        return true;
    }
    else if (head->data > n->data)  //if it is the smallest item in the set, make it the head
    {
        head->prev = n;
        n->next = head;
        head = n;
        head->prev = nullptr;
        m_size++;
        return true;
    }
    else if (tail->data < n->data) //if it is the largest item make it the tail
    {
        tail->next = n;
        n->next = nullptr;
        n->prev = tail;
        tail = n;
        m_size++;
        return true;
    }
    else {   //if it is somewhere in the middle
        Node *p;
        for (p = head->next; p != nullptr; p = p->next)
        {
            if (p->prev->data < n->data && p->data > n->data)  //find where the last node is smaller and
            {                                                   //the current node is larger
                p->prev->next = n;
                n->next = p;
                p->next->prev = n;  //insert node
                m_size++;
            }
        }
        return true;
    }
    return false;
}

bool Set::erase(const ItemType& value)
{
    Node *p = head;
    for (; p != nullptr && p->data != value; p = p->next) //go through the linked list
    {
        ;
    }
    if (p == nullptr)   //means the node is not in the set
    {
        return false;
    }
    if (m_size == 1)
    {
        m_size--;
        delete p;
        return true;
    }
    if (p == head)
    {
        p->next->prev = nullptr;
        head = p->next;
        
        delete p;
        m_size--;
        return true;
    }
    if (p == tail)
    {
        p->prev->next = nullptr;
        tail = p->prev;
        
        delete p;
        m_size--;
        return true;
    }
    else {
        p->prev->next = p->next;    //reallocate pointers
        p->next->prev = p->prev;
        if (p != nullptr)
            delete p;
        m_size--;
        return true;
    }
}

bool Set::get(int pos, ItemType& value) const
{
    if (pos < 0  ||  pos >= m_size)
        return false;
    int count = 0;
    Node *p = head;
    for (; p != nullptr && count <= pos; p = p->next)  //traverse linked list
    {
        if (count == pos)
        {
            value = p->data;  //linked list is in order so return the pointer when count = pos
            return true;
        }
        count++;
    }
    return false;
}

void Set::swap(Set& other)
{
    Node *temp;
    temp = head;
    head = other.head;
    other.head = temp;
    
    temp = tail;
    tail = other.tail;
    other.tail = temp;
    
    // Swap sizes
    
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}

Set::~Set() //destructor
{
    if(head != nullptr)
    {
        if(m_size == 1)//2. there's only one element in the linked list
        {
            delete head;
        }
        else //3. there's multiple element
        {
            Node* p  = head;
            while(p!= nullptr)
            {
                Node* die = p;
                p = p -> next;
                delete die;
            }
        }
    }
    
}

Set::Set(const Set& other)
: m_size(other.m_size)
{
    Node *p;
    Node *q;
    head = new Node();
    head->data = other.head->data;
    q = head;
    for (p = other.head->next; p != nullptr; p = p->next)  //go through other's linked list
    {
        Node *n = new Node();  //create new Nodes and assign them to the same values as other
        n->data = p->data;
        n->prev = q;
        q->next = n;
        q = n;
        
    }
}

Set& Set::operator=(const Set& rhs)
{
    ItemType traverse;
    while (m_size > 0)
    {
        get(0, traverse);
        erase(traverse);
    }
    
    m_size = 0;
    
    if (this != &rhs) //check if they are the same
    {
        head = new Node();
        m_size++;
        head->data = rhs.head->data;
        Node *p;
        Node *q;
        q = head;
        for (p = rhs.head->next; p != nullptr; p = p->next)
        {
            Node *n = new Node();
            m_size++;
            n->data = p->data;
            n->prev = q;
            q->next = n;
            q = n;
        }
    }
    return *this;
}

void unite(const Set& s1, const Set& s2, Set& result)  //insert items from both sets into result
{
    ItemType traverse;
    while (result.size() > 0)
    {
        result.get(0, traverse);
        result.erase(traverse);
    }
    for (int i = 0; i < s1.size(); i++)  //insert all items from s1
    {
        s1.get(i, traverse);
        result.insert(traverse);
    }
    for (int j = 0; j < s2.size(); j++)  //insert all items from s2
    {
        s2.get(j, traverse);
        result.insert(traverse);
    }
}

void subtract(const Set& s1, const Set& s2, Set& result) //insert all items in s1 but not s2 in result
{
    ItemType traverse;
    while (result.size() > 0)
    {
        result.get(0, traverse);
        result.erase(traverse);
    }
    for (int i = 0; i < s1.size(); i++)
    {
        s1.get(i, traverse);
        if (!s2.contains(traverse))  //for each item in s1, check if s2 contains it
        {
            result.insert(traverse);  //if not insert it in result
        }
    }
}

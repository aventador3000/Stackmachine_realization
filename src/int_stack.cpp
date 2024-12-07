////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include <stdexcept>
#include "int_stack.h"

// TODO: add necessary headers here
// #include <...

namespace xi
{

// TODO: add method definitions here
    IntStack::IntStack(size_t sz)
    {
        _head = 0;
        _ssize = sz;
        _stack = new int[sz];

    }

    IntStack::~IntStack()
    {
        delete[] _stack;

    }

    //IntStack::IntStack(const xi::IntStack &copy)
    //{
      //  _head = copy._head;
        //_ssize = copy._ssize;
        //_stack = copy._stack;

    //}

    //IntStack &IntStack::operator=(const xi::IntStack &other)
    //{
      //  _head = other._head;
        //_ssize = other._ssize;
        //_stack = other._stack;

    //}

    bool IntStack::isEmpty() const
    {
        return _head == 0;

    }

    bool IntStack::isFull() const
    {
        return _head == _ssize;
    }

    void IntStack::push(int el)
    {
        if (isFull())
            throw std::logic_error("Stack is full");
        _stack[_head++] = el;

    }

    int IntStack::pop()
    {
        if (isEmpty())
            throw std::logic_error("Stack is empty");
        return _stack[--_head];
    }

    int IntStack::top()
    {
        if (isEmpty())
            throw std::logic_error("Stack is empty");
        return _stack[_head - 1];

    }

    void IntStack::clear()
    {
        _head = 0;

    }

} // namespace xi


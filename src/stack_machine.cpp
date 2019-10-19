////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>

namespace xi
{

//==============================================================================
// Free functions -- helpers
//==============================================================================

// TODO: if you need any free functions, add their definitions here.

//==============================================================================
// class PlusOp
//==============================================================================


    int PlusOp::operation(char op, int a, int b,
                          int c) // < just commented unused argument. This does not affect the code anyhow.
    {
        if (op != '+')
            throw std::logic_error("Operation other than Plus (+) are not supported");

        // here we just ignore unused operands
        return a + b;
    }

    IOperation::Arity PlusOp::getArity() const
    {
        return arDue;
    }


//==============================================================================
// class StackMachine
//==============================================================================


// TODO: put StackMachine methods implementation here

    int ChoiceOp::operation(char op, int a, int b, int c)
    {
        if (op != '?')
            throw std::logic_error("Operation other than  (?) are not supported");

        return a ? b : c;
    }

    IOperation::Arity ChoiceOp::getArity() const
    {
        return arTre;
    }

    int AssignOp::operation(char op, int a, int b, int c)
    {
        if (op != '=')
            throw std::logic_error("Operation other than Not (?) are not supported");
        return a;
    }

    IOperation::Arity AssignOp::getArity() const
    {
        return arUno;
    }

    int SigChangeOp::operation(char op, int a, int b, int c)
    {
        if (op != '!')
            throw std::logic_error("Operation other than Plus (?) are not supported");

        return -a;
    }

    IOperation::Arity SigChangeOp::getArity() const
    {
        return arUno;
    }

    void StackMachine::registerOperation(char symb, xi::IOperation *oper)
    {
        if (_opers[symb] != nullptr)
        {
            throw std::logic_error("Symbol is already registered");
        }
        _opers[symb] = oper;
    }

    IOperation *StackMachine::getOperation(char symb)
    {
        if (!_opers[symb])
            return nullptr;
        return _opers[symb];

    }

    int StackMachine::calculate(const std::string &expr, bool clearStack)
    {//Check if the stack consists el
        if (clearStack)
            _s.clear();
        int x = 0;
        //main cycle to go for the array
        for (int i = 0; i < expr.length(); i++)
        {//check if the el is number,with a help of(-'0') parse char to int
            if (expr[i] - '0' >= 0 && expr[i] - '0' <= 9)
                x = x * 10 + (expr[i] - '0');//if number bigger than 9
            else
            {
                if (expr[i] == ' ' && expr[i - 1] - '0' >= 0 && expr[i - 1] - '0' <= 9)
                {//put the wright value if previous el in array is number
                    _s.push(x);
                    x = 0;
                }
                else if(expr[i]!=' ')
                {
                    if (getOperation(expr[i]) == nullptr)
                        throw std::logic_error("Symbol is not registered here");

                    int a = 0;
                    int b = 0;
                    int c = 0;
                    //put the value to arity,to identify the operation
                    int arity = getOperation(expr[i])->getArity();
                    if (arity == IOperation::arUno)
                    {
                        a = _s.pop();//take value from stack
                        _s.push(getOperation(expr[i])->operation(expr[i], a, b, c));
                    }
                    if (arity == IOperation::arDue)
                    {//reverse order to take wright values from stack
                        b = _s.pop();
                        a = _s.pop();
                        _s.push(getOperation(expr[i])->operation(expr[i], a, b, c));
                    }
                    if (arity == IOperation::arTre)
                    {
                        c = _s.pop();
                        b = _s.pop();
                        a = _s.pop();
                        _s.push(getOperation(expr[i])->operation(expr[i], a, b, c));
                    }
                }
            }
        }
        return _s.top();//returns the value from the top of stack
    }

}



// namespace xi

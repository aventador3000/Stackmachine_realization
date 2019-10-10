////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit tests for xi::StackMachine class
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      23.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Gtest-based unit test.
/// The naming conventions imply the name of a unit-test module is the same as 
/// the name of the corresponding tested module with _test suffix
///
/// Note the issue about including point modules here (ask the trainer about).
/// 
////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include <climits>   // INT_MAX

#include "stack_machine.h"



/// Fixture class for testing stack machine
class StackMachineTest : public testing::Test {


protected:
    
    /// Invoked before each test
    virtual void SetUp()
    {
#ifdef PLUS_OP
        _sm.registerOperation('+', &_plusOp);
#endif
#ifdef MINUS_OP
        _sm.registerOperation('-', &_minusOp);
#endif
#ifdef MULT_OP
        _sm.registerOperation('*', &_multOp);
#endif
#ifdef DIV_OP
        _sm.registerOperation('/', &_divOp);
#endif
#ifdef CHOICE_OP
        _sm.registerOperation('?', &_choiceOp);
#endif
#ifdef ASSIGN_OP
        _sm.registerOperation('=', &_assignOp);
#endif
#ifdef SIG_CHANGE_OP
        _sm.registerOperation('!', &_sigChangeOp);
#endif
#ifdef INVER_OP
        _sm.registerOperation('~', &_inverOp);
#endif
#ifdef AND_OP
        _sm.registerOperation('&', &_andOp);
#endif
#ifdef OR_OP
        _sm.registerOperation('|', &_orOp);
#endif
#ifdef POW_OP
        _sm.registerOperation('^', &_powOp);
#endif
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown() { }

protected:
    xi::StackMachine _sm;           // stack machine itself
    // add here all operation to be registered for a specific instance of the stack machine,
    // it depends on the individual assignment
#ifdef PLUS_OP
    xi::PlusOp _plusOp;
#endif
#ifdef MINUS_OP
    xi::MinusOp _minusOp;
#endif
#ifdef MULT_OP
    xi::MultOp _multOp;
#endif
#ifdef DIV_OP
    xi::DivOp _divOp;
#endif
#ifdef CHOICE_OP
    xi::ChoiceOp _choiceOp;
#endif
#ifdef ASSIGN_OP
    xi::AssignOp _assignOp;
#endif
#ifdef SIG_CHANGE_OP
    xi::SigChangeOp _sigChangeOp;
#endif
#ifdef INVER_OP
    xi::InverOp _inverOp;
#endif
#ifdef AND_OP
    xi::AndOp _andOp;
#endif
#ifdef OR_OP
    xi::OrOp _orOp;
#endif
#ifdef POW_OP
    xi::PowOp _powOp;
#endif

}; // class TestMachineTest



TEST_F(StackMachineTest, simplest)
{
    using namespace xi;

    xi::StackMachine sm;
}


#ifdef PLUS_OP
// tests with the fixture class
TEST_F(StackMachineTest, plusOp1)
{
    int res = _sm.calculate("7 8 10 + +");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 25);
    EXPECT_EQ(r1, 25);
}


TEST_F(StackMachineTest, plusOp2)
{
    int res = _sm.calculate("8 10 + 7 +");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 25);
    EXPECT_EQ(r1, 25);
}
#endif // PLUS_OP


TEST_F(StackMachineTest, undefOper1)
{
    // for undefined operation (let it be >) must raise an exception
    EXPECT_THROW(_sm.calculate("10 8 >"), std::exception);
}

TEST_F(StackMachineTest, undefOper2)
{
    // any undefined substring should be regarded as an exception
    EXPECT_THROW(_sm.calculate("10 3 -hello"), std::exception);
}


#ifdef MINUS_OP
TEST_F(StackMachineTest, minusOp1)
{
    int res = _sm.calculate("10 8 -");      // x = 10, y = 8
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 2);
    EXPECT_EQ(r1, 2);
}
#endif // MINUS_OP

#ifdef MULT_OP
TEST_F(StackMachineTest, multiOp1)
{
    int res = _sm.calculate("2 3 *");      
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 6);
    EXPECT_EQ(r1, 6);
}
#endif // MULT_OP

#ifdef DIV_OP
TEST_F(StackMachineTest, divOp1)
{
    int res = _sm.calculate("10 2 /");      // x = 10, y = 2
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 5);
    EXPECT_EQ(r1, 5);


    res = _sm.calculate("10 0 /");      // x = 10, y = 0 (see definition!)
    r1 = _sm.getStack().top();
    EXPECT_EQ(res, INT_MAX);            // !! there was a typo in the task definition !!
    EXPECT_EQ(r1, INT_MAX);
}
#endif // DIV_OP

#ifdef CHOICE_OP
TEST_F(StackMachineTest, choiceOp1)
{
    int res = _sm.calculate("1 2 3 ?");     // x = 1, y = 2, z = 3
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 2);
    EXPECT_EQ(r1, 2);

    res = _sm.calculate("0 2 3 ?");         // x = 0, y = 2, z = 3
    r1 = _sm.getStack().top();
    EXPECT_EQ(res, 3);
    EXPECT_EQ(r1, 3);
}
#endif // CHOICE_OP

#ifdef ASSIGN_OP
TEST_F(StackMachineTest, assOp1)
{

    // note here an operand must be poped from a stack and the result pushed to the stack back
    // it can be checked in the further tests

    int res = _sm.calculate("1 =");     
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 1);
    EXPECT_EQ(r1, 1);
}
#endif // ASSIGN_OP

#ifdef SIG_CHANGE_OP
TEST_F(StackMachineTest, sigChangeOp1)
{

    int res = _sm.calculate("1 !");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, -1);
    EXPECT_EQ(r1, -1);
}
#endif // SIG_CHANGE_OP

#ifdef INVER_OP
TEST_F(StackMachineTest, inverOp1)
{

    int res = _sm.calculate("0 ~");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, ~0);
    EXPECT_EQ(r1, ~0);                  // real inversion operator
}
#endif // INVER_OP

#ifdef AND_OP
TEST_F(StackMachineTest, andOp1)
{

    int res = _sm.calculate("1 3 &");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 1 & 3);
    EXPECT_EQ(r1, 1 & 3);                  
}
#endif // AND_OP

#ifdef OR_OP
TEST_F(StackMachineTest, orOp1)
{

    int res = _sm.calculate("1 3 |");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 1 | 3);
    EXPECT_EQ(r1, 1 | 3);
}
#endif // OR_OP

#ifdef POW_OP
TEST_F(StackMachineTest, powOp1)
{

    int res = _sm.calculate("2 3 ^");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 8);
    EXPECT_EQ(r1, 8);
}
#endif // POW_OP


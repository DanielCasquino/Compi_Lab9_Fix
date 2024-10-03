#include <iostream>
#include "exp.h"

using namespace std;
BinaryExp::BinaryExp(Exp *l, Exp *r, BinaryOp op) : left(l), right(r), op(op) {}
NumberExp::NumberExp(int v) : value(v) {}
IdentifierExp::IdentifierExp(const string &n) : name(n) {}
IfExp::IfExp(Exp *c, Exp *l, Exp *r) : cond(c), left(l), right(r) {}
NotExp::NotExp(Exp *e) : inner(e) {}

Exp::~Exp() {}
BinaryExp::~BinaryExp()
{
    delete left;
    delete right;
}
NumberExp::~NumberExp() {}
IdentifierExp::~IdentifierExp() {}

IfExp::~IfExp()
{
    delete cond;
    delete left;
    delete right;
}

NotExp::~NotExp()
{
    delete inner;
}

AssignStatement::AssignStatement(string id, Exp *e) : id(id), rhs(e) {}
AssignStatement::~AssignStatement()
{
    delete rhs;
}
PrintStatement::PrintStatement(Exp *e) : e(e) {}
PrintStatement::~PrintStatement()
{
    delete e;
}

IfStatement::IfStatement(Exp *c, list<Stm *> t, list<Stm *> e) : condition(c), then(t), els(e) {}
IfStatement::~IfStatement()
{
    delete condition;
    for (Stm *s : then)
    {
        delete s;
    }
    for (Stm *s : els)
    {
        delete s;
    }
}

WhileStatement::WhileStatement(Exp *c, list<Stm *> slst) : condition(c), slist(slst) {}
WhileStatement::~WhileStatement()
{
    delete condition;
    for (Stm *s : slist)
    {
        delete s;
    }
}

ForStatement::ForStatement(Exp *sta, Exp *sto, Exp *ste, list<Stm *> sl) : start(sta), stop(sto), step(ste), slist(sl) {}
ForStatement::~ForStatement()
{
    delete start;
    delete stop;
    delete step;
    for (Stm *s : slist)
    {
        delete s;
    }
}

Program::Program() {}
void Program::add(Stm *s)
{
    slist.push_back(s);
}
Program::~Program()
{
    for (Stm *s : slist)
    {
        delete s;
    }
}
Stm::~Stm() {}
string Exp::binopToChar(BinaryOp op)
{
    string c;
    switch (op)
    {
    case ADD_OP:
        c = "+";
        break;
    case SUB_OP:
        c = "-";
        break;
    case MUL_OP:
        c = "*";
        break;
    case DIV_OP:
        c = "/";
        break;
    case LESS_OP:
        c = "<";
        break;
    case EQUAL_OP:
        c = "==";
        break;
    case GREATER_OP:
        c = ">";
        break;
    case LESS_EQUAL_OP:
        c = "<=";
        break;
    case GREATER_EQUAL_OP:
        c = ">";
        break;
    case AND_OP:
        c = "and";
        break;
    case OR_OP:
        c = "or";
        break;
    default:
        c = "$";
    }
    return c;
}
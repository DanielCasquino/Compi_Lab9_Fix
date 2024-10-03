#ifndef EXP_H
#define EXP_H

#include <string>
#include <unordered_map>
#include <list>
#include "visitor.h"
using namespace std;
enum BinaryOp
{
    ADD_OP,
    SUB_OP,
    MUL_OP,
    DIV_OP,
    LESS_OP,
    EQUAL_OP,
    GREATER_OP,
    LESS_EQUAL_OP,
    GREATER_EQUAL_OP,
    AND_OP,
    OR_OP
};

class Exp
{
public:
    virtual int accept(Visitor *visitor) = 0;
    virtual ~Exp() = 0;
    static string binopToChar(BinaryOp op);
};

class BinaryExp : public Exp
{
public:
    Exp *left, *right;
    BinaryOp op;
    BinaryExp(Exp *l, Exp *r, BinaryOp op);
    int accept(Visitor *visitor);
    ~BinaryExp();
};

class NumberExp : public Exp
{
public:
    int value;
    NumberExp(int v);
    int accept(Visitor *visitor);
    ~NumberExp();
};

class IdentifierExp : public Exp
{
public:
    std::string name;
    IdentifierExp(const std::string &n);
    int accept(Visitor *visitor);
    ~IdentifierExp();
};

class IfExp : public Exp
{
public:
    Exp *cond, *left, *right;
    IfExp(Exp *cond, Exp *left, Exp *right);
    int accept(Visitor *visitor);
    ~IfExp();
};

class NotExp : public Exp
{
public:
    Exp *inner;
    NotExp(Exp *exp);
    int accept(Visitor *visitor);
    ~NotExp();
};

class Stm
{
public:
    virtual int accept(Visitor *visitor) = 0;
    virtual ~Stm() = 0;
};

class AssignStatement : public Stm
{
public:
    std::string id;
    Exp *rhs;
    AssignStatement(std::string id, Exp *e);
    int accept(Visitor *visitor);
    ~AssignStatement();
};

class PrintStatement : public Stm
{
public:
    Exp *e;
    PrintStatement(Exp *e);
    int accept(Visitor *visitor);
    ~PrintStatement();
};

class IfStatement : public Stm
{
public:
    Exp *condition;
    list<Stm *> then;
    list<Stm *> els;
    IfStatement(Exp *condition, list<Stm *> then, list<Stm *> els);
    int accept(Visitor *visitor);
    ~IfStatement();
};

class WhileStatement : public Stm
{
public:
    Exp *condition;
    list<Stm *> slist;
    WhileStatement(Exp *condition, list<Stm *> slist);
    int accept(Visitor *visitor);
    ~WhileStatement();
};

class ForStatement : public Stm
{
public:
    Exp *start, *stop, *step;
    list<Stm *> slist;
    ForStatement(Exp *start, Exp *stop, Exp *step, list<Stm *> slist);
    int accept(Visitor *visitor);
    ~ForStatement();
};

class Program
{
public:
    std::list<Stm *> slist;
    Program();
    void add(Stm *s);
    ~Program();
};

#endif // EXP_H
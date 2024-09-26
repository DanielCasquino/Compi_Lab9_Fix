#ifndef EXP_H
#define EXP_H

#include <string>
#include <unordered_map>
#include <list>

#include "visitor.h"

using namespace std;

enum BinaryOp
{
    // arithmetic ops
    PLUS_OP,
    MINUS_OP,
    MUL_OP,
    DIV_OP,
};

enum BooleanOp
{
    // boolean ops
    LESS_THAN_OP,
    GREATER_THAN_OP,
    EQUALS_OP,
    LESS_EQUALS_OP,
    GREATER_EQUALS_OP
};

class Exp
{
public:
    virtual int accept(Visitor *visitor) = 0;
    virtual ~Exp() = 0;
    static char binopToChar(BinaryOp op);
    static string boolOpToString(BooleanOp op);
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

class BooleanExp : public Exp
{
public:
    Exp *left, *right;
    BooleanOp op;
    BooleanExp(Exp *l, Exp *r, BooleanOp op);
    int accept(Visitor *visitor);
    ~BooleanExp();
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

class Program
{
public:
    std::list<Stm *> slist;
    Program();
    void add(Stm *s);
    ~Program();
};

#endif // EXP_H
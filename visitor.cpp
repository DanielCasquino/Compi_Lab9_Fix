#include <iostream>
#include <unordered_map>

#include "exp.h"
#include "visitor.h"

using namespace std;

unordered_map<std::string, int> memoria;
///////////////////////////////////////////////////////////////////////////////////
int BinaryExp::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int BooleanExp::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int NumberExp::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int IdentifierExp::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int AssignStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int PrintStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////

int PrintVisitor::visit(BinaryExp *exp)
{
    exp->left->accept(this);
    cout << ' ' << Exp::binopToChar(exp->op) << ' ';
    exp->right->accept(this);
    return 0;
}

int PrintVisitor::visit(BooleanExp *exp)
{
    exp->left->accept(this);
    cout << ' ' << Exp::boolOpToString(exp->op) << ' ';
    exp->right->accept(this);
    return 0;
}

int PrintVisitor::visit(NumberExp *exp)
{
    cout << exp->value;
    return 0;
}

int PrintVisitor::visit(IdentifierExp *exp)
{
    cout << exp->name;
    return 0;
}

void PrintVisitor::visit(AssignStatement *stm)
{
    cout << stm->id << " = ";
    stm->rhs->accept(this);
    cout << ";";
}

void PrintVisitor::visit(PrintStatement *stm)
{
    cout << "print(";
    stm->e->accept(this);
    cout << ");";
}

void PrintVisitor::imprimir(Program *program)
{
    for (Stm *s : program->slist)
    {
        s->accept(this);
        cout << "\n";
    }
};

///////////////////////////////////////////////////////////////////////////////////
int EVALVisitor::visit(BinaryExp *exp)
{
    int result;
    int v1 = exp->left->accept(this);
    int v2 = exp->right->accept(this);
    switch (Exp::binopToChar(exp->op))
    {
    case '+':
        result = v1 + v2;
        break;
    case '-':
        result = v1 - v2;
        break;
    case '*':
        result = v1 * v2;
        break;
    case '/':
        if (v2 != 0)
            result = v1 / v2;
        else
        {
            cout << "Error: división por cero" << endl;
            result = 0;
        }
        break;
    default:
        cout << "Operador desconocido" << endl;
        result = 0;
    }
    return result;
}

int EVALVisitor::visit(BooleanExp *exp)
{
    int result;
    int v1 = exp->left->accept(this);
    int v2 = exp->right->accept(this);
    string opString = Exp::boolOpToString(exp->op);
    if (opString == "<")
    {
        result = v1 < v2;
    }
    else if (opString == ">")
    {
        result = v1 > v2;
    }
    else if (opString == "==")
    {
        result = v1 == v2;
    }
    else if (opString == "<=")
    {
        result = v1 <= v2;
    }
    else if (opString == ">=")
    {
        result = v1 >= v2;
    }
    else
    {
        cout << "Operador desconocido" << endl;
        result = 0;
    }
    return result;
}

int EVALVisitor::visit(NumberExp *exp)
{
    return exp->value;
}

int EVALVisitor::visit(IdentifierExp *exp)
{
    return memoria[exp->name];
}

void EVALVisitor::visit(AssignStatement *stm)
{
    memoria[stm->id] = stm->rhs->accept(this);
}

void EVALVisitor::visit(PrintStatement *stm)
{
    cout << "printeo " << stm->e->accept(this);
}
void EVALVisitor::ejecutar(Program *program)
{
    for (Stm *s : program->slist)
    {
        s->accept(this);
    }
};
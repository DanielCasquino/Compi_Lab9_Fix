#include <iostream>
#include <stdexcept>

#include "token.h"
#include "scanner.h"
#include "exp.h"
#include "parser.h"

using namespace std;

bool Parser::match(Token::Type ttype)
{
    if (check(ttype))
    {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype)
{
    if (isAtEnd())
        return false;
    return current->type == ttype;
}

bool Parser::advance()
{
    if (!isAtEnd())
    {
        Token *temp = current;
        if (previous)
            delete previous;
        current = scanner->nextToken();
        previous = temp;
        if (check(Token::ERR))
        {
            cout << "Analysis error, unrecognized character: " << current->text << "\n";
            exit(1);
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd()
{
    return (current->type == Token::END);
}

Parser::Parser(Scanner *sc) : scanner(sc)
{
    previous = NULL;
    current = scanner->nextToken();
    if (current->type == Token::ERR)
    {
        cout << "Error at first token: " << current->text << "\n";
        exit(1);
    }
}

Program *Parser::parseProgram()
{
    Program *p = new Program();
    try
    {
        while (!isAtEnd())
        {
            p->add(parseStatement());
            if (!isAtEnd() && !match(Token::SEMICOLON))
            {
                throw runtime_error("Error: se esperaba ';' al final de la declaración.");
            }
        }
    }
    catch (const exception &e)
    {
        cout << "Error durante el parsing: " << e.what() << endl;
        delete p;
        exit(1);
    }
    return p;
}

Stm *Parser::parseStatement()
{
    Stm *s = NULL;
    Exp *e;

    if (current == NULL)
    {
        cout << "Error: Token actual es NULL" << endl;
        exit(1);
    }

    if (match(Token::ID))
    {
        string lex = previous->text;

        if (!match(Token::ASSIGN))
        {
            cout << "Error: se esperaba un '=' después del identificador." << endl;
            exit(1);
        }
        e = parseBoolExpression();
        s = new AssignStatement(lex, e);
    }
    else if (match(Token::PRINT))
    {
        if (!match(Token::LEFT_PARENTHESIS))
        {
            cout << "Error: se esperaba un '(' después de 'print'." << endl;
            exit(1);
        }
        e = parseBoolExpression();
        if (!match(Token::RIGHT_PARENTHESIS))
        {
            cout << "Error: se esperaba un ')' después de la expresión." << endl;
            exit(1);
        }
        s = new PrintStatement(e);
    }
    else
    {
        cout << "Error: Se esperaba un identificador o 'print', pero se encontró: " << *current << endl;
        exit(1);
    }
    return s;
}

Exp *Parser::parseBoolExpression()
{
    Exp *left = parseExpression();
    while (match(Token::LESS_THAN) || match(Token::EQUALS) || match(Token::GREATER_THAN) || match(Token::GREATER_EQUALS) || match(Token::LESS_EQUALS))
    {
        BooleanOp op;
        if (previous->type == Token::LESS_THAN)
        {
            op = LESS_THAN_OP;
        }
        else if (previous->type == Token::EQUALS)
        {
            op = EQUALS_OP;
        }
        else if (previous->type == Token::GREATER_THAN)
        {
            op = GREATER_THAN_OP;
        }
        else if (previous->type == Token::GREATER_EQUALS)
        {
            op = GREATER_EQUALS_OP;
        }
        else if (previous->type == Token::LESS_EQUALS)
        {
            op = LESS_EQUALS_OP;
        }
        Exp *right = parseExpression();
        left = new BooleanExp(left, right, op);
    }
    return left;
}

Exp *Parser::parseExpression()
{
    Exp *left = parseTerm();
    while (match(Token::ADD) || match(Token::SUB))
    {
        BinaryOp op;
        if (previous->type == Token::ADD)
        {
            op = PLUS_OP;
        }
        else if (previous->type == Token::SUB)
        {
            op = MINUS_OP;
        }
        Exp *right = parseTerm();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp *Parser::parseTerm()
{
    Exp *left = parseFactor();
    while (match(Token::MUL) || match(Token::DIV))
    {
        BinaryOp op;
        if (previous->type == Token::MUL)
        {
            op = MUL_OP;
        }
        else if (previous->type == Token::DIV)
        {
            op = DIV_OP;
        }
        Exp *right = parseFactor();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp *Parser::parseFactor()
{
    Exp *e;
    if (match(Token::NUM))
    {
        return new NumberExp(stoi(previous->text));
    }
    else if (match(Token::ID))
    {
        return new IdentifierExp(previous->text);
    }
    else if (match(Token::LEFT_PARENTHESIS))
    {
        e = parseExpression();
        if (!match(Token::RIGHT_PARENTHESIS))
        {
            cout << "Falta paréntesis derecho" << endl;
            exit(0);
        }
        return e;
    }
    cout << "Error: se esperaba un número o identificador." << endl;
    exit(0);
}

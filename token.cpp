#include <iostream>

#include "token.h"

using namespace std;

Token::Token(Type type) : type(type) { text = ""; }

Token::Token(Type type, char c) : type(type) { text = string(1, c); }

Token::Token(Type type, const string &source, int first, int last) : type(type)
{
    text = source.substr(first, last);
}

std::ostream &operator<<(std::ostream &outs, const Token &tok)
{
    outs << "TOKEN(";
    switch (tok.type)
    {
    case Token::ADD:
        outs << "ADD";
        break;
    case Token::SUB:
        outs << "SUB";
        break;
    case Token::MUL:
        outs << "MUL";
        break;
    case Token::DIV:
        outs << "DIV";
        break;
    case Token::NUM:
        outs << "NUM";
        break;
    case Token::ERR:
        outs << "ERR";
        break;
    case Token::RIGHT_PARENTHESIS:
        outs << "RIGHT_PARENTHESIS";
        break;
    case Token::LEFT_PARENTHESIS:
        outs << "LEFT_PARENTHESIS";
        break;
    case Token::END:
        outs << "END";
        break;
    case Token::ID:
        outs << "ID";
        break;
    case Token::PRINT:
        outs << "PRINT";
        break;
    case Token::ASSIGN:
        outs << "ASSIGN";
        break;
    case Token::SEMICOLON:
        outs << "SEMICOLON";
        break;
    case Token::LESS_THAN:
        outs << "LESS_THAN";
        break;
    case Token::GREATER_THAN:
        outs << "GREATER_THAN";
        break;
    case Token::EQUALS:
        outs << "EQUALS";
        break;
    case Token::LESS_EQUALS:
        outs << "LESS_EQUALS";
        break;
    case Token::GREATER_EQUALS:
        outs << "GREATER_EQUALS";
        break;
    default:
        outs << "UNKNOWN";
        break;
    }
    outs << ")";
    return outs;
}

std::ostream &operator<<(std::ostream &outs, const Token *tok)
{
    return outs << *tok;
}
#include <iostream>
#include "token.h"

using namespace std;

Token::Token(Type type) : type(type) { text = ""; }

Token::Token(Type type, char c) : type(type) { text = string(1, c); }

Token::Token(Type type, string s) : type(type) { text = s; }

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
        outs << "PLUS";
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
        outs << "PD";
        break;
    case Token::LEFT_PARENTHESIS:
        outs << "PI";
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
        outs << "PC";
        break;
    case Token::COMMA:
        outs << "COMA";
        break;
    case Token::LESS:
        outs << "LT";
        break;
    case Token::GREATER:
        outs << "GT";
        break;
    case Token::EQUAL:
        outs << "EQ";
        break;
    case Token::LESS_EQUAL:
        outs << "LE";
        break;
    case Token::GREATER_EQUAL:
        outs << "GE";
        break;
    case Token::AND:
        outs << "AND";
        break;
    case Token::OR:
        outs << "OR";
        break;
    case Token::NOT:
        outs << "NOT";
        break;
    case Token::IF:
        outs << "IF";
        break;
    case Token::THEN:
        outs << "THEN";
        break;
    case Token::ELSE:
        outs << "ELSE";
        break;
    case Token::ENDIF:
        outs << "ENDIF";
        break;
    case Token::WHILE:
        outs << "WHILE";
        break;
    case Token::DO:
        outs << "DO";
        break;
    case Token::ENDWHILE:
        outs << "ENDWHILE";
        break;
    case Token::FOR:
        outs << "FOR";
        break;
    case Token::ENDFOR:
        outs << "ENDFOR";
        break;
    case Token::IFEXP:
        outs << "IFEXP";
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
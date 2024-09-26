#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
public:
    enum Type
    {
        ADD,
        SUB,
        MUL,
        DIV,
        NUM,
        ERR,
        RIGHT_PARENTHESIS,
        LEFT_PARENTHESIS,
        END,
        ID,
        PRINT,
        ASSIGN,
        SEMICOLON,
        LESS_THAN,
        GREATER_THAN,
        EQUALS,
        LESS_EQUALS,
        GREATER_EQUALS
    };

    Type type;
    std::string text;

    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const std::string &source, int first, int last);

    friend std::ostream &operator<<(std::ostream &outs, const Token &tok);
    friend std::ostream &operator<<(std::ostream &outs, const Token *tok);
};

#endif // TOKEN_H
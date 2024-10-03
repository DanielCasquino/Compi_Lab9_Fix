#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

class Token
{
public:
    enum Type
    {
        // arithmetic ops
        ADD,
        SUB,
        MUL,
        DIV,
        NUM,
        // misc
        ERR,
        RIGHT_PARENTHESIS,
        LEFT_PARENTHESIS,
        END,
        ID,
        SEMICOLON,
        COMMA,
        // boolean ops
        LESS,
        GREATER,
        EQUAL,
        LESS_EQUAL,
        GREATER_EQUAL,
        AND,
        OR,
        NOT,
        // conditionals
        IF,
        THEN,
        ELSE,
        ENDIF,
        // reserved
        PRINT,
        ASSIGN,
        // loops
        WHILE,
        DO,
        ENDWHILE,
        FOR,
        ENDFOR,
        // extra
        IFEXP
    };

    Type type;
    std::string text;

    Token(Type type);
    Token(Type type, char c);
    Token(Type type, string s);
    Token(Type type, const std::string &source, int first, int last);

    friend std::ostream &operator<<(std::ostream &outs, const Token &tok);
    friend std::ostream &operator<<(std::ostream &outs, const Token *tok);
};

#endif // TOKEN_H
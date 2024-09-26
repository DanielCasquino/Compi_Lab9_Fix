#include <iostream>
#include <cstring>

#include "token.h"
#include "scanner.h"

using namespace std;

Scanner::Scanner(const char *s) : input(s), first(0), current(0) {}

Token *Scanner::nextToken()
{
    Token *token;

    while (current < input.length() && (input[current] == ' ' || input[current] == '\n'))
        current++;

    if (current >= input.length())
        return new Token(Token::END);

    char c = input[current];
    first = current;

    if (isdigit(c))
    {
        current++;
        while (current < input.length() && isdigit(input[current]))
            current++;
        token = new Token(Token::NUM, input, first, current - first);
    }
    else if (isalpha(c))
    {
        current++;

        while (current < input.length() && isalnum(input[current]))
            current++;

        string word = input.substr(first, current - first);

        if (word == "print")
            token = new Token(Token::PRINT, word, 0, word.length());
        else
            token = new Token(Token::ID, word, 0, word.length());
    }
    else if (strchr("+-*/()=;<>", c))
    {
        switch (c)
        {
        case '+':
            token = new Token(Token::ADD, c);
            break;
        case '-':
            token = new Token(Token::SUB, c);
            break;
        case '*':
            token = new Token(Token::MUL, c);
            break;
        case '/':
            token = new Token(Token::DIV, c);
            break;
        case '(':
            token = new Token(Token::LEFT_PARENTHESIS, c);
            break;
        case ')':
            token = new Token(Token::RIGHT_PARENTHESIS, c);
            break;
        case '=':
            token = new Token(Token::ASSIGN, c);
            break;
        case ';':
            token = new Token(Token::SEMICOLON, c);
            break;
        case '<':
            token = new Token(Token::LESS_THAN, c);
            break;
        case '>':
            token = new Token(Token::GREATER_THAN, c);
            break;
        default:
            cout << "Scanner error. Recognized unrecognized symbol. How did we get here?" << "\n";
            token = new Token(Token::ERR, c);
        }
        current++;
        if (current < input.length()) // check for <=. ==; or >=
        {
            if (input[current] == '=')
            {
                switch (token->type)
                {
                case Token::LESS_THAN:
                    token = new Token(Token::LESS_EQUALS, c + input[current]);
                    break;
                case Token::ASSIGN:
                    token = new Token(Token::EQUALS, c + input[current]);
                    break;
                case Token::GREATER_THAN:
                    token = new Token(Token::GREATER_EQUALS, c + input[current]);
                    break;
                default:
                    cout << "Scanner error. Attempted to recognize = symbol after <, =, or >, and something different than = was found." << "\n";
                    token = new Token(Token::ERR, c);
                }
                current++;
            }
        }
    }
    else
    {
        token = new Token(Token::ERR, c);
        current++;
    }
    return token;
}

void Scanner::reset()
{
    first = 0;
    current = 0;
}

Scanner::~Scanner() {}

void test_scanner(Scanner *scanner)
{
    Token *current;

    cout << "Starting scanner." << "\n";

    while ((current = scanner->nextToken())->type != Token::END)
    {
        if (current->type == Token::ERR)
        {
            cout << "Scanner error. Invalid character: " << current->text << "\n";
            break;
        }
        else
        {
            cout << *current << "\n";
        }
        delete current;
    }

    cout << "TOKEN(END)" << endl;

    delete current;
}
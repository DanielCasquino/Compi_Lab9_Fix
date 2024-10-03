#include <iostream>
#include <cstring>
#include <unordered_map>

#include "token.h"
#include "scanner.h"

using namespace std;

unordered_map<std::string, Token::Type> tokenMap = {
    {"+", Token::ADD},
    {"-", Token::SUB},
    {"*", Token::MUL},
    {"/", Token::DIV},
    {"(", Token::LEFT_PARENTHESIS},
    {")", Token::RIGHT_PARENTHESIS},
    {";", Token::SEMICOLON},
    {",", Token::COMMA},
    {"=", Token::ASSIGN},
    {"<", Token::LESS},
    {">", Token::GREATER},
    {"&", Token::AND},
    {"|", Token::OR}};

unordered_map<std::string, Token::Type> binaryTokenMap = {
    {"==", Token::EQUAL},
    {"<=", Token::LESS_EQUAL},
    {">=", Token::GREATER_EQUAL}};

unordered_map<std::string, Token::Type> reservedWordMap = {
    {"print", Token::PRINT},
    {"if", Token::IF},
    {"then", Token::THEN},
    {"else", Token::ELSE},
    {"endif", Token::ENDIF},
    {"while", Token::WHILE},
    {"do", Token::DO},
    {"endwhile", Token::ENDWHILE},
    {"ifexp", Token::IFEXP},
    {"and", Token::AND},
    {"or", Token::OR},
    {"for", Token::FOR},
    {"endfor", Token::ENDFOR},
    {"not", Token::NOT}};

Scanner::Scanner(const char *s) : input(s), first(0), current(0) {}

bool is_white_space(char c)
{
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

Token *Scanner::nextToken()
{
    Token *token;
    while (current < input.length() && is_white_space(input[current]))
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
        if (reservedWordMap.find(word) != reservedWordMap.end())
            token = new Token(reservedWordMap.at(word), word, 0, word.length());
        else
            token = new Token(Token::ID, word, 0, word.length());
    }
    else if (tokenMap.find(string(1, c)) != tokenMap.end())
    {
        token = new Token(tokenMap.at(string(1, c)), c);
        current++;
        if (current < input.length() && input[current] == '=') // check for <=. ==; or >=
        {
            if (binaryTokenMap.find(string(1, c) + string(1, input[current])) != binaryTokenMap.end())
            {
                Token::Type newTokenType = binaryTokenMap.at(string(1, c) + string(1, input[current]));
                token = new Token(newTokenType, string(1, c) + string(1, input[current]));
                current++;
            }
            else
            {
                cout << "Scanner error. Attempted to recognize = symbol after <, =, or >, and something different than = was found." << "\n";
                token = new Token(Token::ERR, c);
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
    cout << "Iniciando Scanner:" << endl
         << endl;
    while ((current = scanner->nextToken())->type != Token::END)
    {
        if (current->type == Token::ERR)
        {
            cout << "Error en scanner - carácter inválido: " << current->text << endl;
            break;
        }
        else
        {
            cout << *current << endl;
        }
        delete current;
    }
    cout << "TOKEN(END)" << endl;
    delete current;
}
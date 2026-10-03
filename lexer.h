#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "token.h"

struct Token
{
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};

class Lexer
{
private:
    const std::string& source;
    size_t position {};
    int line = 1;
    int column = 1;

    char peek() const;
    char peek_next() const;
    char advance();

    void skip_whitespace();
    void skip_comment();

    Token scan_identifier_or_keyword();
    Token scan_number();
    Token scan_string();
    Token scan_operator_or_symbol();

public:
    explicit Lexer(const std::string& source);

    std::vector<Token> tokenize();
};

#endif
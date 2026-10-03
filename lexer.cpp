#include <unordered_map>
#include <string>
#include "lexer.h"
#include <unordered_map>


enum class TokenType
{
    // Keywords
    kw_int,
    kw_double,
    kw_float,
    kw_char,
    kw_bool,
    kw_void,
    kw_string,
    kw_if,
    kw_else,
    kw_elif,
    kw_for,
    kw_while,
    kw_return,
    kw_alloc,

    // Literals
    identifier,
    integer_literal,
    double_literal,
    string_literal,

    // Operators
    plus,
    minus,
    asterisk,
    slash,
    modulo,
    assignment,
    equal_equal,
    less,
    greater,
    not_equal,
    less_equal,
    greater_equal,

    // Symbols
    left_paren,
    right_paren,
    left_brace,
    right_brace,
    lef_sq,
    right_sq,
    semicolon,
    comma,

    eof
};


//Hash Map to easily fetch tokens using iterators
const std::unordered_map<std::string, TokenType> token_map = {{"int", TokenType::kw_int},
                                                           {"double", TokenType::kw_double},
                                                           {"float", TokenType::kw_float},
                                                           {"char", TokenType::kw_char},
                                                           {"bool", TokenType::kw_bool},
                                                           {"void", TokenType::kw_void},
                                                           {"string", TokenType::kw_string},
                                                           {"if", TokenType::kw_if},
                                                           {"else", TokenType::kw_else},
                                                           {"elif", TokenType::kw_elif},
                                                           {"for", TokenType::kw_for},
                                                           {"while", TokenType::kw_while},
                                                           {"return", TokenType::kw_return},
                                                           {"alloc", TokenType::kw_alloc},
                                                           {"+", TokenType::plus},
                                                           {"-", TokenType::minus},
                                                           {"*", TokenType::asterisk},
                                                           {"/", TokenType::slash},
                                                           {"%", TokenType::modulo},
                                                           {"=", TokenType::assignment},
                                                           {"==", TokenType::equal_equal},
                                                           {"<", TokenType::less},
                                                           {">", TokenType::greater},
                                                           {"!=", TokenType::not_equal},
                                                           {"<=", TokenType::less_equal},
                                                           {">=", TokenType::greater_equal},
                                                           {"{", TokenType::left_brace},
                                                           {"}", TokenType::right_brace},
                                                           {"(", TokenType::left_paren},
                                                           {")", TokenType::right_paren},
                                                           {"[", TokenType::left_sq},
                                                           {"]", TokenType::right_sq},
                                                           {",", TokenType::comma},
                                                           {";", TokenType::semicolon},
                                                        };
                                             

char Lexer::peek() const
{
    if (position >= source.length())
        return '\0';

    return source[position];
}             

char Lexer::peek_next() const
{
    if (position + 1 >= source.length())
        return '\0';
    
    return source[position+1];
}

char Lexer::advance()
{
    if (position >= source.length())
        return '\0';


    if (source[position++] == '\n')
    {
        line++;
        column = 1;
    }
    else
    {
        column++;
    }

    return source[position - 1];
}

void Lexer::skip_whitespace()
{
    while (position < source.length() && (source[position] == ' ' || source[position] == '\r' || source[position] == '\t' || source[position] == '\n'))
    {
        advance();
    }
}

void Lexer::skip_comment()
{
    if (position + 1 < source.length() && source[position] == '/' && source[position + 1] == '/')
    {
        while (position < source.length() && source[position] != '\n')
        {
            advance();
        }
    }
}

Token Lexer::scan_identifier_or_keyword()
{
    size_t start = position;

    while (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_')
    {
        advance();
    }

    std::string_view lexeme = std::string_view(source).substr(start, position - start);

    if (auto it = token_map.find(std::string(lexeme)); it != token_map.end())
    {
        return {it->second, std::string(lexeme), line, column};
    }

    return {TokenType::identifier, std::string(lexeme), line, column};
}

Token Lexer::scan_number()
{
    size_t start = position;
    bool is_double = false;

    while (std::isdigit(static_cast<unsigned char>(peek())))
    {
        advance();
    }

    if (peek() == '.' && std::isdigit(static_cast<unsigned char>(peek_next())))
    {
        is_double = true;
        advance();

        while (std::isdigit(static_cast<unsigned char>(peek())))
        {
            advance();
        }
    }

    std::string_view lexeme = std::string_view(source).substr(start, position - start);

    if (is_double)
        return {TokenType::double_literal, std::string(lexeme), line, column};

    return {TokenType::integer_literal, std::string(lexeme), line, column};
}

Token Lexer::scan_string()
{
    size_t start = position;
    advance();

    while (peek() != '"' && peek() != '\0')
    {
        advance();
    }

    if (peek() == '"')
    {
        advance();
    }

    std::string_view lexeme = std::string_view(source).substr(start, position - start);

    return {TokenType::string_literal, std::string(lexeme), line, column};
}

Token Lexer::scan_operator_or_symbol()
{
    size_t start = position;

    std::string_view two = std::string_view(source).substr(start, 2);

    if (two == "==" || two == "!=" || two == "<=" || two == ">=")
    {
        advance();
        advance();

        auto it = token_map.find(std::string(two));

        return {it->second, std::string(two), line, column};
    }

    char current = peek();
    advance();

    std::string_view one = std::string_view(source).substr(start, 1);

    auto it = token_map.find(std::string(one));

    if (it != token_map.end())
    {
        return {it->second, std::string(one), line, column};
    }

    return {TokenType::eof, "", line, column};
}
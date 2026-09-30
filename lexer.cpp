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
                                             
                                                              

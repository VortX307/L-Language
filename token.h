#ifndef TOKEN_H
#define TOKEN_H

enum class TokenType
{
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

    identifier,
    integer_literal,
    double_literal,
    string_literal,

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

    left_paren,
    right_paren,
    left_brace,
    right_brace,
    left_sq,
    right_sq,
    semicolon,
    comma,

    eof
};

#endif
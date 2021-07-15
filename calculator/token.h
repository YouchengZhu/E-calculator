//词法分析模块，处理词法单元，提供负数处理
//date:2021-03-28

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <tuple>

enum class TokenType {
    number,
    end,
    error,
    add = '+',
    sub = '-',
    mul = '*',
    div = '/',
    lp = '(',
    rp = ')',
    pr = '%'
};

struct Token {
    TokenType type;
    double value = 0;
};

//token返回的一个，string 返回后面的
std::tuple<Token, std::string> tokenize(std::string input);

#endif // TOKEN_H

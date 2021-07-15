//语法分析模块，按+-，*/%,()运算优先级不同进行语法分析，构建语法分析树
//date:2021-03-28

#ifndef PARSEEXPRESS_H
#define PARSEEXPRESS_H


#include <string>
#include <tuple>

std::tuple<double,std::string> parseExpress(std::string input);

#endif // PARSEEXPRESS_H

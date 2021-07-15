//词法分析模块，完成词法分析，能够处理负数
//date:2021-03-28

#include "token.h"
#include <stdexcept>
#include <iostream>

int flag = 0;//用于判断下个字符是否为负数，1表示下个字符为负数
int num = 0;//字符下标位置

//处理整数和小数
static std::tuple<double, std::string> parseNumber(std::string input)
{
    std::string numstr;
    bool firstDot = true;
    while (1) {
        if(input.empty()) {
            break;
        }

        char ch =input.front();
        if((ch >= '0' && ch <= '9') || ( ch == '.' && firstDot)) {//处理数字和小数
            numstr.push_back(ch);
            input.erase(input.begin());
            if(ch == '.') {
                firstDot = false;
            }
        }else {
            break;
        }
    }

    return  {std::stod(numstr), input};
}

//用于处理负数
static std::tuple<double, std::string> XparseNumber(std::string input)
{
    std::string numstr;
    bool firstDot = true;

    input.erase(input.begin());//已知是负数，直接移除第一个符号即负号

    while (1) {
        if(input.empty()) {
            break;
        }

        char ch =input.front();


        if((ch >= '0' && ch <= '9') || ( ch == '.' && firstDot)) {
            numstr.push_back(ch);
            input.erase(input.begin());

            if(ch == '.') {
                firstDot = false;
            }
        }else {
            break;
        }
    }


    return  {0-std::stod(numstr), input};
}

//词法处理
std::tuple<Token, std::string> tokenize(std::string input)
{
    Token tk;
    char ch;
    do
    {
        if(input.empty())//表达式为空
        {
            tk.type = TokenType::end;
            num = 0;//表达式下标重置
            return  {tk, ""};//表达式变为空
        }else {
            ch = input.front();//获取第一个字符
            input.erase(input.begin());//移除第一个字符
        }
    }while( ch == ' ');
    if (ch == '-' && num == 0) flag = 1;//如果第一个字符是符号，说明马上处理的是个负数，标志变为1

    std::string inputs = input;//复制当前表达式

    char sh = inputs.front();//获取下一个要处理的字符
    if (flag==0){//如果当前字符不为负数
        switch (ch) {
            case '-':
            case '+':
            case '*':
            case '/':
            case '(':
            case ')':
            case '%':
                    tk.type = TokenType(ch);
                    break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                    tk.type = TokenType::number;
                    input.insert(input.begin(),ch);
                    std::tie(tk.value,input) = parseNumber(input);
                    break;
            default:
                    throw std::runtime_error("invalid input\n");
                    break;

            }
    }else if (flag == 1 ){//如果当前字符为负数
        tk.type = TokenType::number;
        input.insert(input.begin(),ch);
        std::tie(tk.value,input) = XparseNumber(input);
        flag = 0;//标志重置为0
    }

    if ((ch == '*'|| ch == '/' || ch == '(')&&(sh=='-')) flag = 1;//如果出现当前字符是*/(，下一个字符是-，说明下一个要处理的数字为负数，标志变为1

    num++;//表达式下标对应加1
    return {tk, input};
}

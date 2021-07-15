//语法分析模块，完成语法分析，计算结果
//date:2021-03-28

#include "parseexpress.h"
#include <token.h>

//对因子进行处理，切分运算符，数字和括号
static std::tuple<double,std::string> parseFactor(std::string input)
{
    double result;
    Token tk;
    std::tie(tk, input) = tokenize(input);//调用词法分析，返回词法单元以及处理后的表达式
    switch (tk.type) {
    //词法分析返回为数字，结果暂时保存为数字
    case TokenType::number:
            result = tk.value;
        break;
    //词法分析返回为左括号，对括号内的表达式进行语法分析
    case TokenType::lp:
        std::tie(result, input) = parseExpress(input);
        std::tie(tk, input) = tokenize(input);
        //如果只有左括号没有有括号，输出错误信息
        if(tk.type != TokenType::rp) {
            throw  std::runtime_error("need a )\n");
        }
        break;
        //如果出现不符合语法的运算符使用，输出错误信息
    default:
        throw std::runtime_error("BAD SYNATX:");
        break;
    }

    return  {result, input};//返回当前的运算结果，以及处理后的表达式
}

//对词法单元进行处理，进行*，/，%运算
static std::tuple<double,std::string> parseTerm(std::string input)
{
    double result;
    bool loop = true;
    std::tie(result, input) = parseFactor(input);

    while (loop) {
          Token op;
          std::string res;
          double term;
          std::tie(op, res) = tokenize(input);//调用词法分析来解析运算符

          switch (op.type) {
          //乘法运算
          case TokenType::mul:
              std::tie(term, input) =parseFactor(res);//解析数字
              result *= term;
              break;
          //除法运算
          case TokenType::div:
              std::tie(term, input) = parseFactor(res);
              result /= term;
              if(term == 0) {
                  throw std::runtime_error("error:vie");
              }
              break;
           //取余运算
          case TokenType::pr:
              std::tie(term,input) = parseFactor(res);
              result  =(int)result % (int)term;
              break;
          default:
              loop = false;
              break;
          }
    }

    return  {result, input};//返回当前结果，以及处理后的表达式

}


//E -> TR
//R -> +TR | -TR | null
//语法分析，构建语法分析树，从下往上，最后计算+,-得出结果
std::tuple<double,std::string> parseExpress(std::string input)
{
    double result;
    bool loop = true;
    std::tie(result, input) = parseTerm(input);


    while (loop) {
          Token op;
          std::string res;
          double term;
          std::tie(op, res) = tokenize(input);//解析运算符

          switch (op.type) {
          case TokenType::add:
              std::tie(term, input) = parseTerm(res);//解析数字
              result += term;
              break;
          case TokenType::sub:
              std::tie(term,input) = parseTerm(res);
              result -=term;
              break;
         default:
              loop = false;
              break;
          }
    }

    return  {result, input};//运算结束，返回最终结果，表达式此时为空
}

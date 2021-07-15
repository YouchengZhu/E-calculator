//计算机界面设计模块，完成对应按键与对应槽函数的连接，提供光标位置插入，键盘输入输出，输入语法错误处理等功能
//date:2021-03-28

#include "widget.h"
#include "ui_widget.h"
#include "parseexpress.h"
#include "token.h"
#include <iostream>
#include "QSignalMapper"
#include <QtGui>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("E-calculator");
    //将数字按键与数字按键的槽连接
    connect(ui->pushButton_num0,SIGNAL(clicked()),this,SLOT(pushButton_num_clicked()));
    connect(ui->pushButton_num1,SIGNAL(clicked()),this,SLOT(pushButton_num_clicked()));
    connect(ui->pushButton_num2,SIGNAL(clicked()),this,SLOT(pushButton_num_clicked()));
    connect(ui->pushButton_num3,SIGNAL(clicked()),this,SLOT(pushButton_num_clicked()));
    connect(ui->pushButton_num4,SIGNAL(clicked()),this,SLOT(pushButton_num_clicked()));
    connect(ui->pushButton_num5,SIGNAL(clicked()),this,SLOT(pushButton_num_clicked()));
    connect(ui->pushButton_num6,SIGNAL(clicked()),this,SLOT(pushButton_num_clicked()));
    connect(ui->pushButton_num7,SIGNAL(clicked()),this,SLOT(pushButton_num_clicked()));
    connect(ui->pushButton_num8,SIGNAL(clicked()),this,SLOT(pushButton_num_clicked()));
    connect(ui->pushButton_num9,SIGNAL(clicked()),this,SLOT(pushButton_num_clicked()));
    connect(ui->pushButton_ponit,SIGNAL(clicked()),this,SLOT(pushButton_num_clicked()));

    //将运算符键和运算符槽连接
    connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(pushButton_op_clicked()));
    connect(ui->pushButton_sub,SIGNAL(clicked()),this,SLOT(pushButton_op_clicked()));
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(pushButton_op_clicked()));
    connect(ui->pushButton_mul,SIGNAL(clicked()),this,SLOT(pushButton_op_clicked()));
    connect(ui->pushButton_ld,SIGNAL(clicked()),this,SLOT(pushButton_op_clicked()));
    connect(ui->pushButton_rd,SIGNAL(clicked()),this,SLOT(pushButton_op_clicked()));
    connect(ui->pushButton_pr,SIGNAL(clicked()),this,SLOT(pushButton_op_clicked()));

    ui->pushButton_equ->setShortcut(Qt::Key_Return);


}

Widget::~Widget()
{
    delete ui;
}

//AC槽，将输入输出框的内容全部清空
void Widget::on_pushButton_AC_clicked()
{
    ui->lineEdit_input->clear();
    ui->lineEdit_output->clear();
    ui->lineEdit_input->setFocus();//焦点保持在输入框上
}

//数字键对应的槽函数
void Widget::pushButton_num_clicked()
{
    int position = ui->lineEdit_input->cursorPosition();//首先获取光标的位置
    QString text = ui->lineEdit_input->text();//获取输入框当前的文本
    QPushButton *btn = qobject_cast<QPushButton*>(sender());//寻找按下的是哪个按钮

    text.insert(position,btn->text());//在光标位置处插入对应按钮代表的数字
    ui->lineEdit_input->setText(text);//重新设置输入框的文本
    ui->lineEdit_input->setCursorPosition(position+1);//光标位置对应后移
    ui->lineEdit_input->setFocus();//焦点保持在输入框上
}

//运算符键对应的槽函数
void Widget::pushButton_op_clicked()
{
    int position = ui->lineEdit_input->cursorPosition();//获取光标的位置
    QString text = ui->lineEdit_input->text();//获取但前输入框内的文本
    QPushButton *btn = qobject_cast<QPushButton*>(sender());//寻找按下的是哪按钮

    //设置语法限制，除减号，左括号外不允许其他的运算符出现在输入框第一个的位置
    if (position>=1){
        if (btn->text() == "(" ){
                text.insert(position,btn->text());
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position+1);
                ui->lineEdit_input->setFocus();
        } else if(btn->text() == ")"){
            //右括号前一个字符不允许是加减乘除等运算符，如果是这些符号，右括号直接覆盖前一个符号，没有则直接插入右括号
            if((text[position-1]=='+')||(text[position-1]=='-')||
                    (text[position-1]=='*')||(text[position-1]=='/')||(text[position-1]=='%')){
                text.replace(position-1,1,")");//将前一个符号替换成右括号
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position);
                ui->lineEdit_input->setFocus();
            }else{
                text.insert(position,btn->text());
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position+1);
                ui->lineEdit_input->setFocus();
            }
        } else if (btn->text() == "+"){
            //运算符前一个字符不允许是其他的任何运算符，如是，则用加号替换
            if((text[position-1]=='+')||(text[position-1]=='-')||
                    (text[position-1]=='*')||(text[position-1]=='/')||(text[position-1]=='%')){
                text.replace(position-1,1,"+");
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position);
                ui->lineEdit_input->setFocus();
            }else{
                text.insert(position,btn->text());
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position+1);
                ui->lineEdit_input->setFocus();
            }
        } else if(btn->text() == "-"){
            //运算符减前一个字符不允许是加，减，取余运算符，如是则用减号替换
            if ((text[position-1] == '+')||(text[position-1] == '-')||(text[position-1] == '%')){
                    text.replace(position-1,1,"-");
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position);
                ui->lineEdit_input->setFocus();
            } else{
                text.insert(position,btn->text());
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position+1);
                ui->lineEdit_input->setFocus();
            }
        } else if(btn->text() == "*"){
            //运算符乘前一个字符不允许是加减乘除等运算符，如是，则用乘号替换
            if((text[position-1]=='+')||(text[position-1]=='-')||
                    (text[position-1]=='*')||(text[position-1]=='/')||(text[position-1]=='%')){
                text.replace(position-1,1,"*");
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position);
                ui->lineEdit_input->setFocus();
            }else{
                text.insert(position,btn->text());
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position+1);
                ui->lineEdit_input->setFocus();
            }
        } else if(btn->text() == "/"){
            //运算符除前一个字符不允许是加减乘除等运算符，如是，则用除号替换
            if((text[position-1]=='+')||(text[position-1]=='-')||
                    (text[position-1]=='*')||(text[position-1]=='/')||(text[position-1]=='%')){
                text.replace(position-1,1,"/");
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position);
                ui->lineEdit_input->setFocus();
            }else{
                text.insert(position,btn->text());
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position+1);
                ui->lineEdit_input->setFocus();
            }
        } else if(btn->text() == "%"){
            //运算符取余前一个字符不允许是加减乘除等字符，如是，则用取余替换
            if((text[position-1]=='+')||(text[position-1]=='-')||
                    (text[position-1]=='*')||(text[position-1]=='/')||(text[position-1]=='%')){
                text.replace(position-1,1,"%");
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position);
                ui->lineEdit_input->setFocus();
            }else{
                text.insert(position,btn->text());
                ui->lineEdit_input->setText(text);
                ui->lineEdit_input->setCursorPosition(position+1);
                ui->lineEdit_input->setFocus();
            }
        }
    }else if(btn->text() == "-" && position == 0){//如果减号是第一个字符
            text.insert(position,btn->text());
            ui->lineEdit_input->setText(text);
            ui->lineEdit_input->setCursorPosition(position+1);
            ui->lineEdit_input->setFocus();
    }else if (btn->text() == "(" && position == 0){//如果左括号是第一个字符
        text.insert(position,btn->text());
        ui->lineEdit_input->setText(text);
        ui->lineEdit_input->setCursorPosition(position+1);
        ui->lineEdit_input->setFocus();
    } else{//如果不是以上这些情况，输入语法必然为错
            ui->lineEdit_input->setText("Error");
    }
}

//消除键对应的槽
void Widget::on_pushButton_del_clicked()
{
        int position = ui->lineEdit_input->cursorPosition();//获取光标的位置
        QString text = ui->lineEdit_input->text();//读取输入框内的文本
        std::string tmp = text.toStdString();
        if (position >=1 && position <= text.length()){//设置光标的范围
            tmp.erase(tmp.begin()+position-1);//移除光标前的一个字符
            text = QString::fromStdString(tmp);
            ui->lineEdit_input->setText(text);
            ui->lineEdit_input->setCursorPosition(position-1);
            ui->lineEdit_input->setFocus();
        }
}

//等号键对应的槽函数
void Widget::on_pushButton_equ_clicked()
{
      try{
            QString text = ui->lineEdit_input->text();
            std::string tmp = text.toStdString();
            auto[result, res] = parseExpress(tmp);//调用语法分析函数进行计算
            ui->lineEdit_output->setText(QString::number(result));//将计算结果输出到输出框内
      } catch(std::runtime_error e){
                ui->lineEdit_input->setText(e.what());
            }
}

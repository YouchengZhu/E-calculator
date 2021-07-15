//计算器界面设计，对应槽函数与按键处理
//date:2021-03-28

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_AC_clicked();//AC键对应槽，提供清除整个输入输出的功能

    void pushButton_num_clicked();//数字键对应槽，提供在光标位置插入相应数字的功能
    void pushButton_op_clicked();//运算符对应槽，提供在光标处插入对应运算符的功能，同时处理一些运算符非法输入

    void on_pushButton_del_clicked();//消除键对应槽，提供消除前一个字符的功能

    void on_pushButton_equ_clicked();//等号键对应槽，调用运算核心模块，对输入框内的表达式解析，运算结果，在输出框内输出

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

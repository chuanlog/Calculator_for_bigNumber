#include "widget.h"
#include "ui_widget.h"
#include"bigNumber.h"
#include "CalculateFuntions.h"

//QString转std::string
string QString_to_string(QString& s)
{
    QByteArray localBytes = s.toLocal8Bit();
    string localStr = localBytes.data();
    return localStr;
}

QString string_to_QString(string& s)
{

    return QString::fromStdString(s);
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QFont f("仿宋",30);
    ui->InputLineEdit1->setFont(f);
    ui->InputLineEdit2->setFont(f);
    ui->OperatorLineEdit->setFont(f);
    ui->ResultLineEdit->setFont(f);//设置输出输入框的文字格式

}

Widget::~Widget()
{
    delete ui;
}
/*此处定义每个数字按钮以及小数点的输入与显示数字逻辑*/
void Widget::on_pushButton_num0_clicked()
{
    line1=ui->InputLineEdit1->text();
    line2=ui->InputLineEdit2->text();
    if(ui->InputLineEdit1->hasFocus())
    {
        line1+='0';
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2+='0';
        ui->InputLineEdit2->setText(line2);
    }
}
void Widget::on_pushButton_num1_clicked()
{
    line1=ui->InputLineEdit1->text();
    line2=ui->InputLineEdit2->text();
    if(ui->InputLineEdit1->hasFocus())
    {
        line1+='1';
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2+='1';
        ui->InputLineEdit2->setText(line2);
    }
}
void Widget::on_pushButton_num2_clicked()
{
    line1=ui->InputLineEdit1->text();
    line2=ui->InputLineEdit2->text();
    if(ui->InputLineEdit1->hasFocus())
    {
        line1+='2';
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2+='2';
        ui->InputLineEdit2->setText(line2);
    }
}
void Widget::on_pushButton_num3_clicked()
{
    line1=ui->InputLineEdit1->text();
    line2=ui->InputLineEdit2->text();
    if(ui->InputLineEdit1->hasFocus())
    {
        line1+='3';
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2+='3';
        ui->InputLineEdit2->setText(line2);
    }
}
void Widget::on_pushButton_num4_clicked()
{
    line1=ui->InputLineEdit1->text();
    line2=ui->InputLineEdit2->text();
    if(ui->InputLineEdit1->hasFocus())
    {
        line1+='4';
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2+='4';
        ui->InputLineEdit2->setText(line2);
    }
}
void Widget::on_pushButton_num5_clicked()
{
    line1=ui->InputLineEdit1->text();
    line2=ui->InputLineEdit2->text();
    if(ui->InputLineEdit1->hasFocus())
    {
        line1+='5';
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2+='5';
        ui->InputLineEdit2->setText(line2);
    }
}
void Widget::on_pushButton_num6_clicked()
{
    line1=ui->InputLineEdit1->text();
    line2=ui->InputLineEdit2->text();
    if(ui->InputLineEdit1->hasFocus())
    {
        line1+='6';
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2+='6';
        ui->InputLineEdit2->setText(line2);
    }
}
void Widget::on_pushButton_num7_clicked()
{
    line1=ui->InputLineEdit1->text();
    line2=ui->InputLineEdit2->text();
    if(ui->InputLineEdit1->hasFocus())
    {
        line1+='7';
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2+='7';
        ui->InputLineEdit2->setText(line2);
    }
}
void Widget::on_pushButton_num8_clicked()
{
    line1=ui->InputLineEdit1->text();
    line2=ui->InputLineEdit2->text();
    if(ui->InputLineEdit1->hasFocus())
    {
        line1+='8';
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2+='8';
        ui->InputLineEdit2->setText(line2);
    }
}
void Widget::on_pushButton_num9_clicked()
{
    line1=ui->InputLineEdit1->text();
    line2=ui->InputLineEdit2->text();
    if(ui->InputLineEdit1->hasFocus())
    {
        line1+='9';
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2+='9';
        ui->InputLineEdit2->setText(line2);
    }
}
void Widget::on_pushButton_point_clicked()
{
    line1=ui->InputLineEdit1->text();
    line2=ui->InputLineEdit2->text();
    if(ui->InputLineEdit1->hasFocus())
    {
        line1+='.';
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2+='.';
        ui->InputLineEdit2->setText(line2);
    }
}





/*此处定义运算符输入的按钮逻辑*/
void Widget::on_pushButton_add_clicked()
{
    if(ui->OperatorLineEdit->hasFocus())
    {
        op='+';
        ui->OperatorLineEdit->setText(op);
    }
}

void Widget::on_pushButton_sub_clicked()
{
    if(ui->OperatorLineEdit->hasFocus())
    {
        op='-';
        ui->OperatorLineEdit->setText(op);
    }
    else if(ui->InputLineEdit1->hasFocus())
    {
        line1=ui->InputLineEdit1->text();
        line1+='-';
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2=ui->InputLineEdit2->text();
        line2+='-';
        ui->InputLineEdit2->setText(line2);
    }
}

//清空所有LineEdit
void Widget::on_pushButton_Clear_clicked()
{
    line1.clear();
    line2.clear();
    op='+';
    ui->InputLineEdit1->clear();
    ui->InputLineEdit2->clear();
    ui->ResultLineEdit->clear();
    ui->OperatorLineEdit->clear();
}

//退格
void Widget::on_pushButton_back_clicked()
{
    line1=ui->InputLineEdit1->text();
    line2=ui->InputLineEdit2->text();
    if(ui->InputLineEdit1->hasFocus())
    {
        line1.chop(1);
        ui->InputLineEdit1->setText(line1);
    }
    else if(ui->InputLineEdit2->hasFocus())
    {
        line2.chop(1);
        ui->InputLineEdit2->setText(line2);
    }
    else if(ui->OperatorLineEdit->hasFocus())
    {
        ui->OperatorLineEdit->clear();
        op='+';
    }
}


void Widget::on_pushButton_equal_clicked()
{

    if(ui->InputLineEdit1->text().isEmpty()||ui->InputLineEdit2->text().isEmpty())
    {
        ui->ResultLineEdit->setText("请输入待运算数字");
        return;
    }
    if(ui->OperatorLineEdit->text().isEmpty())
    {
        ui->ResultLineEdit->setText("请输入运算符");
        return;
    }

    bigNumber number1;
    bigNumber number2;
    bigNumber result;
    QString qnum1;
    QString qnum2;
    QString qres;
    string num1;
    string num2;
    string res;
    bool OP=false;
    qnum1=ui->InputLineEdit1->text();
    qnum2=ui->InputLineEdit2->text();
    num1=qnum1.toStdString();
    num2=qnum2.toStdString();
    number1.read_in(num1);
    number2.read_in(num2);
    if(ui->OperatorLineEdit->text()=="-")OP=true;
    Calculate(OP,number1,number2,result);
    res=result.show_list_result();
    qres = QString(QString::fromLocal8Bit(res.c_str()));
    ui->ResultLineEdit->setText(qres);
}






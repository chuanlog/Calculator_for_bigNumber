#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_num0_clicked();

    void on_pushButton_num1_clicked();

    void on_pushButton_num2_clicked();

    void on_pushButton_num3_clicked();

    void on_pushButton_num4_clicked();

    void on_pushButton_num5_clicked();

    void on_pushButton_num6_clicked();

    void on_pushButton_num7_clicked();

    void on_pushButton_num8_clicked();

    void on_pushButton_num9_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_sub_clicked();

    void on_pushButton_Clear_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_equal_clicked();

    void on_pushButton_point_clicked();

private:
    Ui::Widget *ui;
    QString line1;//记录InputLineEdit1的字符串
    QString line2;//记录InputLineEdit2的字符串
    QChar op='+';//记录operator的字符默认为‘+’
};
#endif // WIDGET_H

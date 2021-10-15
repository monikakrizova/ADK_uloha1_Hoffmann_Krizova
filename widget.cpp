#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButtonClear_clicked()
{
    ui->Canvas->clear();
}

void Widget::on_pushButton_clicked()
{
    ui->Canvas->changeStatus();
}

void Widget::on_pushButtonAnalyze_clicked()
{

    //Analyze position of the point and vertex
    QPoint q = ui->Canvas->getPoint();
    std::vector<QPoint> pol = ui->Canvas->getPolygon();

    //Get position
    Algorithms a;
    int pos = a.getPositionWinding(q, pol);

    //Print results
    if (pos == 1)
        ui->label->setText("Inside");
    else
        ui->label->setText("Outside");
}

void Widget::on_pushButton_2_clicked()
{

}


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

/*void Widget::on_pushButton_clicked()
{
    ui->Canvas->changeStatus();
}*/

void Widget::on_pushButtonAnalyze_clicked()
{
    Algorithms a;
    std::vector <QPoint> vert;
    int position;

    //Analyze position of the point and vertex
    QPoint q = ui->Canvas->getPoint();
    int polygon_count = ui->Canvas->getPolygonsCount();

    std::vector<QPolygon> pol = ui->Canvas->getPolygon();

    for (int i = 0; i < polygon_count; i++)
    {
        vert.clear();
        QPolygon polygonek = pol[i];
        for (int j = 0; j < polygonek.size(); j++)
        {
            vert.push_back(polygonek[j]);
        }
        position = a.getPositionWinding(q, vert);
        if (position == 1)
            break;
    }

    //Get position

    //Print results
    if (position == 1)
        ui->label->setText("Inside");
    else
        ui->label->setText("Outside");
}

void Widget::on_pushButton_2_clicked()
{

}


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
    std::vector <int> position;
    int result;
    int pol_position;

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
        result = a.getPositionWinding(q, vert);
        position.push_back(result);
        std::cout << result << std::endl;
        if (result == 1)
        {
            pol_position = i;
            std::cout << "polygon id: " << pol_position << std::endl;
            break;}
    }
    //Get position
    //Print results
    if (result == 1)
        ui->label->setText("Inside");
    else
        ui->label->setText("Outside");

    ui->Canvas->fillPolygon(pol_position);
    ui->Canvas->getResult(pol_position);

}

void Widget::on_pushButton_2_clicked()
{

}


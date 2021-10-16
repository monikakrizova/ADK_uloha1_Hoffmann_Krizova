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
    int result;
    int pol_position;
    int res;
    //Analyze position of the point and vertex
    QPoint q = ui->Canvas->getPoint();
    int polygon_count = ui->Canvas->getPolygonsCount();
    std::vector<QPolygon> pol = ui->Canvas->getPolygon();

    for (int i = 0; i < polygon_count; i++)
    {
        vert.clear();
        QPolygon polygon1 = pol[i];
        //Get polygon coordinates from polygons
        for (int j = 0; j < polygon1.size(); j++)
        {
            vert.push_back(polygon1[j]);
        }

        if(ui->comboBox->currentIndex())
            result = a.getPositionRayCrossing(q, vert);
        else
            result = a.getPositionWinding(q, vert);

        std::cout << result << std::endl;           //jen pro me, aby bylo videt, jak to funguje, pak smazeme
        //If the result of the function is 1, point is inside the polygon pol[i]
        if (result == 1)
        {
            res = 1;
            pol_position = i;
            std::cout << "polygon id: " << pol_position << std::endl; //jen pro me, aby bylo videt, jak to funguje, pak smazeme
            //break;
        }
    }
    //Get position
    //Print results
    if (res == 1)
        ui->label->setText("Inside");
    else if (res == 0)
    {
        ui->label->setText("Outside");
        pol_position = -99;
    }
    else if (res == -1)
    {
        ui->label->setText("Point is on the line");
    }

    ui->Canvas->fillPolygon(pol_position);
    ui->Canvas->getResult(pol_position);

}

//Tady pak pridame otevreni dialogoveho okna pro vyber souboru s polygony
void Widget::on_pushButton_2_clicked()
{

}


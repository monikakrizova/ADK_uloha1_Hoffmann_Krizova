#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include <iostream>
#include <QFileDialog>


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
    //Clear canvas
    ui->Canvas->clear();
}


void Widget::on_pushButtonAnalyze_clicked()
{
    Algorithms a;
    std::vector <QPoint> vert;
    int result;
    int pol_position;
    int res;

    //Analyze position of the point and vertex
    QPoint q = ui->Canvas->getPoint();

    std::vector<QPolygon> pol = ui->Canvas->getPolygon();

    for (unsigned int i = 0; i < pol.size(); i++)
    {
        //Clear the vector of vertices
        vert.clear();

        //Save one polygon from the vector to the separate value
        QPolygon polygon1 = pol[i];

        //Get polygon coordinates from polygons
        for (int j = 0; j < polygon1.size(); j++)
        {
            vert.push_back(polygon1[j]);
        }

        //Analyze point position
        if(ui->comboBox->currentIndex())
            result = a.getPositionRayCrossing(q, vert);
        else
            result = a.getPositionWinding(q, vert);

        //If the result of the function is 1, point is inside the polygon pol[i]
        if (result == 1)
        {
            pol_position = i;
            break;
        }
    }
    //Get position
    //Print results
    if (result == 1)
        ui->label->setText("Inside");
    else if (result == 0)
    {
        ui->label->setText("Outside");
        pol_position = -99;
    }
    else if (result == -1)
    {
        ui->label->setText("Point is on the line");
    }

    //Fill polygon including point
    ui->Canvas->fillPolygon(pol_position);

}

void Widget::on_pushButtonLoad_clicked()
{
    //Load polygon from the file
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open Text file"), "", tr("Text Files (*.txt)"));
    QFileInfo fileinfo(file_name);
    ui->Canvas->loadData(file_name);
}


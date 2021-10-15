#include "draw.h"
#include <QtGui>
#include <fstream>
#include <iostream>


Draw::Draw(QWidget *parent) : QWidget(parent)
{
    q.setX(-100);
    q.setY(-100);
    add_vertex = true;
}


void Draw::paintEvent(QPaintEvent *event)
{
    // Create graphic object
    QPainter painter(this);
    painter.begin(this);



    /* //Convert vector to polygon
    for (int i = 0; i < vertices.size(); i++){
        pol.append(vertices[i]);
    }*/

    //Draw point q
    painter.drawEllipse(q.x()-4, q.y()-4, 8, 8);



    QPolygon polygon;
    //std::vector <QPolygon> polygons;
    QPoint vertice;
    double x,y;
    int id;
    std::ifstream file("C:/Users/monik/Documents/SKOLA/Ing_3.semestr/ADK/PointInPolygon/polygon.txt");


    while (file >> id >> x >> y)
    {
        if (id == 1)
        {
            if (polygon.empty() == false)
                polygons.push_back(polygon);
            polygon.clear();
            vertice.setX(x);
            vertice.setY(y);
            polygon.append(vertice);
        }
        else
        {
            vertice.setX(x);
            vertice.setY(y);
            polygon.append(vertice);
        }

    }
    polygons.push_back(polygon);


    for (int i = 0; i < polygons.size(); i++)
    {
        painter.drawPolygon(polygons[i]);
    }

    //Improvements
    //for( QPoint vertex : vertices)
    //    pol.append(vertex);

    painter.end();
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get cursor coordinates
    int x = event->pos().x();
    int y = event->pos().y();

    //Add new vertex
    if (add_vertex)
    {
        //Create new point
        QPoint p(x,y);

        //Add point to vector
        vertices.push_back(p);
    }

    //Modify coordinates of point Q
    else
    {
        q.setX(x);
        q.setY(y);
    }

    //Repaint screen
    repaint();
}

void Draw::clear()
{
    //Clear and repaint
    vertices.clear();
    repaint();
}



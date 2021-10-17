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
    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    //Draw point q
    painter.drawEllipse(q.x()-4, q.y()-4, 8, 8);

    }
    //Save to the vector of QPolygons
    //Draw polygons
    for (unsigned int i = 0; i < polygons.size(); i++)
    {
        painter.drawPolygon(polygons[i]);
    }

//    QPolygon polygon;
//    //std::vector <QPolygon> polygons;
//    QPoint vertice;
//    double x,y;
//    int id;

//    //Load polygons from the txt file
//    std::ifstream file("D:/Github/ADK/ADKI_uloha1/polygon.txt");
//    while (file >> id >> x >> y)
//    {
//        if (id == 1)
//        {
//            if (polygon.empty() == false)
//                polygons.push_back(polygon);
//            polygon.clear();
//            vertice.setX(x);
//            vertice.setY(y);
//            polygon.append(vertice);
//        }
//        else
//        {
//            vertice.setX(x);
//            vertice.setY(y);
//            polygon.append(vertice);
//        }
//    }
//    //Save to the vector of QPolygons
//    polygons.push_back(polygon);

//    //Draw polygons
//    for (unsigned int i = 0; i < polygons.size(); i++)
//    {
//        painter.drawPolygon(polygons[i]);
//    }

    //Draw polygon which contains the point

    //Set the painting style
    QBrush brush;
    brush.setColor(Qt::magenta);
    brush.setStyle(Qt::CrossPattern);
    QPainterPath path;
    QPen fill_pen(Qt::magenta, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(fill_pen);

    //Paint selected polygon (-99 je jen pomucka aby se nezvyraznovalo nic, pokud je bod mimo nebo jeste nikde neni)
    if (highlighted_polygon != -99)
    {
        path.addPolygon(polygons[highlighted_polygon]);
        painter.drawPolygon(polygons[highlighted_polygon]);
        painter.fillPath(path, brush);
    }


    painter.end();
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get cursor coordinates
    int x = event->pos().x();
    int y = event->pos().y();

    //Set point coordinates to the cursor position
    q.setX(x);
    q.setY(y);

    //Repaint screen
    repaint();
}

void Draw::clear()
{
    //Clear and repaint
    polygons.clear();
    repaint();
}

void Draw::fillPolygon(int result1)
{
    this->highlighted_polygon = result1;
    repaint();
}

void Draw::loadData(QString &path)
{

    std::string file_path = path.toStdString();
    std::cout << "file path:" << file_path << std::endl;

    QPolygon polygon;
    //std::vector <QPolygon> polygons;
    QPoint vertice;
    double x,y;
    int id;

    //Load polygons from the txt file
    std::ifstream file(file_path);
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
    //Save to the vector of QPolygons
    polygons.push_back(polygon);
}

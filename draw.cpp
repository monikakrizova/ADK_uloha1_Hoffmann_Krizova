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

    //Draw polygons
    for (unsigned int i = 0; i < polygons.size(); i++)
    {
        painter.drawPolygon(polygons[i]);
    }

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
    q.setX(-100);
    q.setY(-100);
    repaint();
}

void Draw::fillPolygon(int result1)
{
    this->highlighted_polygon = result1;
    repaint();
}

void Draw::loadData(QString &file_name)
{
    QPolygon polygon;
    QPoint vertice;

    QFile inputFile(file_name);
        if (inputFile.open(QIODevice::ReadOnly))
        {
            QTextStream in(&inputFile);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                int id = line.split(" ")[0].toInt();
                int x = line.split(" ")[1].toDouble();
                int y = line.split(" ")[2].toDouble();

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
        inputFile.close();
    }

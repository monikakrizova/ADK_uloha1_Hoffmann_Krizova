#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <QPainterPath>
#include <QBrush>
#include <QPen>

class Draw : public QWidget
{
    Q_OBJECT

private:
    //std::vector<QPoint> vertices;
    std::vector<QPolygon> polygons;
    QPoint q;
    bool add_vertex;
    int highlighted_polygon=-99;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void clear();
    //void changeStatus(){add_vertex = !add_vertex;} //nepotrebujeme
    QPoint getPoint(){return q;}
    std::vector<QPolygon> getPolygon(){return polygons;}
    int getPolygonsCount(){return polygons.size();}
    void fillPolygon(int result);
    void getResult(int result){highlighted_polygon = result;} //nema bejt setResult? gettery musi neco vracet :D a k cemu to vlastne je?

    void loadData(QString &file_name);
signals:

public slots:
};

#endif // DRAW_H

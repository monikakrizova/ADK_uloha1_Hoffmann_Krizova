#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>

class Draw : public QWidget
{
    Q_OBJECT

private:
    std::vector<QPoint> vertices;
    std::vector<QPolygon> polygons;
    QPoint q;
    bool add_vertex;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void clear();
    void changeStatus(){add_vertex = !add_vertex;}
    QPoint getPoint(){return q;}
    std::vector<QPolygon> getPolygon(){return polygons;}
    int getPolygonsCount(){return polygons.size();}

    void loadData();
signals:

public slots:
};

#endif // DRAW_H

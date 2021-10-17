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
    std::vector<QPolygon> polygons;
    QPoint q;
    bool add_vertex;
    int highlighted_polygon=-99;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void clear();
    QPoint getPoint(){return q;}
    std::vector<QPolygon> getPolygon(){return polygons;}
    void fillPolygon(int result);
    void getResult(int result){highlighted_polygon = result;}
    void loadData(QString &file_name);

signals:

public slots:
};

#endif // DRAW_H

#include "algorithms.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

Algorithms::Algorithms()
{

}

int Algorithms::getPointLinePosition(QPoint &a,QPoint &p1,QPoint &p2)
{
    //Analyze point and line position
    double eps = 1.0e-10;

    //Coordinate differences
    double ux=p2.x()-p1.x();
    double uy=p2.y()-p1.y();

    double vx=a.x()-p1.x();
    double vy=a.y()-p1.y();

    //Half plane test(cross product)
    double t = ux*vy-vx*uy;

    //Point in the left halfplane
    if (t > eps)
        return 1;

    //Point in the right halfplane
    if (t < -eps)
        return 0;

    //Point on the line
    return -1;
}

double Algorithms::get2LinesAngle(QPoint &p1, QPoint &p2, QPoint &p3, QPoint &p4)
{
    //Compute angle formed by two lines

    //Coordinate differences
    double ux=p2.x()-p1.x();
    double uy=p2.y()-p1.y();

    double vx=p4.x()-p3.x();
    double vy=p4.y()-p3.y();

    //Dot product
    double dp=ux*vx+uy*vy;

    //Norms
    double nu = sqrt(ux*ux + uy*uy);
    double nv = sqrt(vx*vx + vy*vy);

    //Angle
    return fabs(acos(dp/(nu*nv)));
}


int Algorithms::getPositionWinding(QPoint &q, std::vector<QPoint> &pol)
{
    //Analyze position of point and polygon
    int n = pol.size();
    double omega_sum=0;
    double eps = 1.0e-5;

    //Process all segments of polygon
    for (int i = 0; i<n; i++)
    {
        // Angle between two line segments
        double omega = get2LinesAngle(pol[i], q, pol[(i+1)%n], q);

        // Point and line segment position
        int pos = getPointLinePosition(q, pol[i], pol[(i+1)%n]);

        //Point in the left halfplane
        if (pos==1)
            omega_sum += omega;
        else
            omega_sum -= omega;
    }

    //Point inside polygon
    if (fabs(fabs(omega_sum) - 2*M_PI) < eps)
        return 1;

    //Point outside polygon
    return 0;
}


/*std::string Algorithms::readCSV()
{
    QPolygon polygon;
    std::vector <QPolygon> polygons;
    double x,y;
    int id;
    std::ifstream file("polygon.txt");
    if (file.is_open())
    {
      while(file >> id >> x >> y)
      {
          if (id == 0)
          {
              if (polygon.isEmpty() == FALSE)
              {
                  polygons.push_back(polygon);
              }
              polygon.clear();
              polygon << QPoint(x, y);}
          else
              polygon << QPoint(x,y);
         polygons.push_back(polygon);

      }
      file.close();
    }


    //std::cout<< polygons << std::endl;
};*/










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
    double eps = 1.0e-10; //High number of epsylon to find a solution for point being on a line

    //Process all segments of polygon
    for (int i = 0; i<n; i++)
    {
        //Angle between two line segments
        double omega = get2LinesAngle(pol[i], q, pol[(i+1)%n], q);

        //Point and line segment position
        int pos = getPointLinePosition(q, pol[i], pol[(i+1)%n]);

        if (pos==1) //Point in the left halfplane
            omega_sum += omega;
        else if (pos == 0) //Point in the right halfplane
            omega_sum -= omega;
        else
            return -1;  //Point on a line
    }

    //Point position
    if (fabs(fabs(omega_sum) - 2*M_PI) < eps)    //Point inside polygon
        return 1;
    else
        return 0;   //Point outside polygon
}

int Algorithms::getPositionRayCrossing(QPoint &q, std::vector<QPoint> &pol)
{
    //Get number of vertices in polygon
    int n = pol.size();

    //Inicialize number of intersetions
    int k = 0;

    //First point reduction
    double dx = pol[0].x()-q.x();
    double dy = pol[0].y()-q.y();

    //Process all segments of polygon
    for (int i = 0; i <= n; i++)
    {
        //Point coordinates reductions
        double dxx = pol[i%n].x()-q.x();
        double dyy = pol[i%n].y()-q.y();

        //Find intersection
        if (((dyy > 0) && (dy <= 0)) || ((dy > 0) && (dyy <= 0)))
        {
            //Compute x coordinate of the found intersection
            double xm = (dxx*dy-dx*dyy)/(dyy-dy);
            if (xm > 0) //Right plane
                k++;
        }
        dx = dxx;
        dy = dyy;
    }

    if (k%2 == 0) //Even number
        return 0; //Point lies outside the polygon
    else    //Odd number
        return 1; //Point lies inside the polygon

}











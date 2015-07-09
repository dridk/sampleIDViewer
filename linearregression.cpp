#include "linearregression.h"
#include <QDebug>

LinearRegression::LinearRegression()
{
    mSlope     = 0;
    mIntercept = 0;
    mCoef      = 0;
}
//=====================================================================================
LinearRegression::LinearRegression(const QVector<double> &x, const QVector<double> &y)
{
    set(x,y);
}
//=====================================================================================
void LinearRegression::set(const QVector<double> &x, const QVector<double> &y)
{
    if (x.size() != y.size())
        qWarning()<<"Warning , x and y doesn't have same size";

    double meanX = mean(x);
    double meanY = mean(y);

    double sx = 0, sy = 0, sxy = 0;

    int size  = qMin(x.size(), y.size());

    for (int i=0; i<size; ++i)
    {
        sx  += qPow(x.at(i) - meanX, 2);
        sy  += qPow(y.at(i) - meanY, 2);
        sxy += (x.at(i) - meanX) * (y.at(i) - meanY);
    }

    mSlope     = sxy / sx;
    mIntercept = meanY - mSlope*meanX;
    mCoef      = sxy /qSqrt(sx*sy);


}
//=====================================================================================
double LinearRegression::slope()
{
    return mSlope;
}
//=====================================================================================
double LinearRegression::intercept()
{
    return mIntercept;
}
//=====================================================================================
double LinearRegression::mean(const QVector<double> &v)
{
    if (v.size() == 0 )
        return -1;

    double sum = 0;
    foreach (double i , v)
        sum += i;

    return sum / v.size();


}
//=====================================================================================
double LinearRegression::y(double x)
{
    return slope() * x + intercept();
}

double LinearRegression::x(double y)
{
    return (y - intercept()) / slope();
}

double LinearRegression::coef()
{
    return mCoef;
}

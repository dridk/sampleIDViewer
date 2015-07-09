#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include <QtCore>

class LinearRegression
{
public:
    LinearRegression();
    LinearRegression(const QVector<double>& x, const QVector<double>& y);

    void set(const QVector<double>& x, const QVector<double>& y);
    double slope();
    double intercept();
    double mean(const QVector<double>& v);
    double y(double x);
    double x(double y);
    double coef();


private:
    double mSlope;
    double mIntercept;
    double mCoef;

};

#endif // LINEARREGRESSION_H

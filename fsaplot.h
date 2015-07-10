#ifndef FSAPLOT_H
#define FSAPLOT_H

#include "qcustomplot.h"
#include "abifreader.h"
#include "linearregression.h"
#include "fsaregionitem.h"

#define ID_X 0
#define ID_Y1 1
#define ID_Y2 2
#define ID_Y3 3
#define ID_Y4 4



class FsaPlot : public QCustomPlot
{
    Q_OBJECT
public:
    FsaPlot(QWidget *parent = 0);


    int dyeCount();
    QString dyeName(int id);
    QColor dyeColor(int id);
    QVector<double> dyeData(int id);

    QVariant abifData(const QString& key) const;

    const LinearRegression &regression() const;

    void detectRefPeaks(int xMin, double yMin, double yMax, int dyeId = 3);


    // mathematics function
     QVector<double> diff(const QVector<double>& list);






public slots:
    void detectRefPeaks();
    bool setFileName(const QString& filename);


    void addRegion(const QString& name, int size, int range);
    void removeRegion(int index);
    void clearRegion();


    void setLeft(int x);
    void setBottom(int y);
    void setTop(int y);

    void setLeftLineVisible(bool visible = true);
    void setBottomLineVisible(bool visible = true);
    void setTopLineVisible(bool visible = true);
    void setLinesVisible(bool visible = true);

    void setRegionVisible(bool visible = true);


private:

    AbifReader * mR;
    QCPItemLine * mLeftLine;
    QCPItemLine * mBottomLine;
    QCPItemLine * mTopLine;
    QCPItemRect * mLeftRect;
    QCPItemRect * mTopRect;
    QCPItemRect * mBottomRect;

    QList<QCPItemRect*> mRegionRects;

    LinearRegression mRegression;


    QVector<double> mRefKeys;
    QVector<double> mRefValues;



    QString mCurrentFile;



};

#endif // FSAVIEWER_H

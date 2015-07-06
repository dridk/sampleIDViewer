#ifndef FSAPLOT_H
#define FSAPLOT_H

#include "qcustomplot.h"
#include "abifreader.h"

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


    QList<int> detectPeak(int xMin, int yMin, int yMax);
    QVector<double> diff( QVector<double> list);

public slots:
    void setFileName(const QString& filename);


private:
    QList<int> mRoxRef;

   QList< QVector<double> > mDatas;

QString mCurrentFile;



};

#endif // FSAVIEWER_H

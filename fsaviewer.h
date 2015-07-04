#ifndef FSAVIEWER_H
#define FSAVIEWER_H

#include "qcustomplot.h"
#include "abifreader.h"

#define ID_X 0
#define ID_Y1 1
#define ID_Y2 2
#define ID_Y3 3
#define ID_Y4 4

class FsaViewer : public QCustomPlot
{
    Q_OBJECT
public:
    FsaViewer(QWidget *parent = 0);

public slots:
    void setFileName(const QString& filename);


private:
    QList<int> mRoxRef;

   QList< QVector<double> > mDatas;




};

#endif // FSAVIEWER_H

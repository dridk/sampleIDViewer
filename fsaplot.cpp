#include "fsaplot.h"
#include <QFileDialog>
#include "linearregression.h"
FsaPlot::FsaPlot(QWidget *parent)
    :QCustomPlot(parent)
{

    mR          = NULL;
    mLeftLine   = new QCPItemLine(this);
    mBottomLine = new QCPItemLine(this);
    mTopLine    = new QCPItemLine(this);

    mRefKeys<<35<<50<<75<<100<<139<<150<<160<<200<<250<<300<<340<<350<<400<<450<<490<<500;

}
//====================================================
int FsaPlot::dyeCount()
{
    return abifData("Dye#.1").toInt();
}
//====================================================
QString FsaPlot::dyeName(int id)
{
    return abifData(QString("DyeN.%1").arg(id+1)).toString();
}
//====================================================
QColor FsaPlot::dyeColor(int id)
{
    QList<QColor> cols;
    cols<<Qt::blue<<Qt::green<<Qt::black<<Qt::red;
    return cols.value(id, Qt::lightGray);
}
//====================================================

QVector<double> FsaPlot::dyeData(int id)
{
    QVector<double> y;
    QVariantList raw  = abifData(QString("DATA.%1").arg(id+1)).toList();

    for (int i=0; i<raw.size(); ++i)
        y.append(raw.at(i).toDouble());

    return y;


}
//====================================================
QVariant FsaPlot::abifData(const QString &key) const
{
    if (!mR)
        return QVariant();

    return mR->data(key);
}

const LinearRegression &FsaPlot::regression() const
{
    return mRegression;
}
//====================================================

void FsaPlot::detectRefPeaks()
{

    int xMin    = mLeftLine->start->key();
    double yMin = mBottomLine->start->value();
    double yMax = mTopLine->start->value();

    detectRefPeaks(xMin,yMin,yMax);

}
//====================================================
void FsaPlot::detectRefPeaks(int xMin, double yMin, double yMax, int dyeId)
{
    QVector<double> list = dyeData(dyeId);

    QVector<int> x;
    QVector<double> y;

    // First , filtering data out of the box
    for (int i=0; i< list.size(); ++i)
    {
        if ( (list.at(i) >= yMin) &&  (list.at(i) <= yMax ) && (i >= xMin))
        {
            x.append(i);
            y.append(list.at(i));
        }
    }

    mRefValues.clear();

    // Compute derivate
    QVector<double> delta(diff(y));
    // detect peaks by looking change + to -
    int old = delta.first();
    for (int i=0; i<delta.size(); ++i)
    {
        double value = delta.at(i);
        if ( (old > 0) && (value < 0))
            mRefValues.append(x[i]);
        old = value;
    }



    mRegression.set(mRefValues, mRefKeys);

    qDebug()<<mRegression.slope();
    qDebug()<<mRegression.intercept();


    foreach (int x, mRefValues )
    {
        QCPItemText * pix = new QCPItemText(this);
        pix->setText(QString::number(qFloor(mRegression.y(x))) + QString(" kb"));
        pix->position->setCoords(x,-10);
        addItem(pix);
    }

    replot();
    repaint();


}
//====================================================
bool FsaPlot::setFileName(const QString& filename)
{
    if (!QFile::exists(filename))
        return false;

    if (mR)
        delete mR;

    mCurrentFile = filename;
    mR = new AbifReader(mCurrentFile);


    if (!mR->isAbif())
        return false;


    for (int i=0; i<dyeCount(); ++i)
    {

        QVariantList raw  = abifData(QString("DATA.%1").arg(i+1)).toList();
        QVector<double> x;
        QVector<double> y;

        for (int i=0; i<raw.size(); ++i)
        {
            x.append(i);
            y.append(raw.at(i).toDouble());
        }

        addGraph();
        graph()->setData(x,y);
        graph()->setPen(QPen(dyeColor(i)));

        x.clear();
        y.clear();
    }


    setInteraction(QCP::iRangeZoom,true);
    setInteraction(QCP::iRangeDrag,true);



    QPen pen(Qt::darkGray);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(1);




    mLeftLine->start->setTypeX(QCPItemPosition::ptPlotCoords);
    mLeftLine->start->setTypeY(QCPItemPosition::ptViewportRatio);
    mLeftLine->end->setTypeX(QCPItemPosition::ptPlotCoords);
    mLeftLine->end->setTypeY(QCPItemPosition::ptViewportRatio);

    mBottomLine->start->setTypeX(QCPItemPosition::ptViewportRatio);
    mBottomLine->start->setTypeY(QCPItemPosition::ptPlotCoords);
    mBottomLine->end->setTypeX(QCPItemPosition::ptViewportRatio);
    mBottomLine->end->setTypeY(QCPItemPosition::ptPlotCoords);


    mTopLine->start->setTypeX(QCPItemPosition::ptViewportRatio);
    mTopLine->start->setTypeY(QCPItemPosition::ptPlotCoords);
    mTopLine->end->setTypeX(QCPItemPosition::ptViewportRatio);
    mTopLine->end->setTypeY(QCPItemPosition::ptPlotCoords);


    mLeftLine->start->setCoords(1287,0);
    mLeftLine->end->setCoords(1287,1);


    mBottomLine->start->setCoords(0,256);
    mBottomLine->end->setCoords(1,256);

    mTopLine->start->setCoords(0,1600);
    mTopLine->end->setCoords(1,1600);

    mLeftLine->setPen(pen);
    mBottomLine->setPen(pen);
    mTopLine->setPen(pen);


    replot();
    rescaleAxes();




}

void FsaPlot::addRegion(const QString &name, int size, int range)
{

    qDebug()<<name<<" "<<size<<" "<<range;

    QCPItemRect * rect = new QCPItemRect(this);

    rect->topLeft->setTypeX(QCPItemPosition::ptPlotCoords);
    rect->topLeft->setTypeY(QCPItemPosition::ptViewportRatio);

    rect->bottomRight->setTypeX(QCPItemPosition::ptPlotCoords);
    rect->bottomRight->setTypeY(QCPItemPosition::ptViewportRatio);

    rect->topLeft->setCoords(mRegression.x(size-range), 0);
    rect->bottomRight->setCoords(mRegression.x(size+range), 1);

    QColor col("#CB99C9");
    QBrush brush(col, Qt::BDiagPattern);
    rect->setBrush(brush);
    rect ->setPen(QPen(Qt::lightGray));



    mRegionRects.append(rect);
    addItem(rect);
    replot();

}

void FsaPlot::removeRegion(int index)
{
    QCPItemRect * item = mRegionRects.at(index);
    removeItem(item);

    replot();
}

void FsaPlot::clearRegion()
{

    qDeleteAll(mRegionRects);

}

//void FsaPlot::updateSelectors()
//{

////    foreach (QCPItemRect * r, mSelectorRects)
////        removeItem(r);

////    mSelectorRects.clear();


//    qDeleteAll(mSelectorRects);

//    for (int i=0; i<mSelectorModel->rowCount(); ++i)
//    {

//        FsaSelectorItem * item = mSelectorModel->item(i);
//        if (!item)
//            return;


//        QCPItemRect * rect = new QCPItemRect(this);

//        rect->topLeft->setTypeX(QCPItemPosition::ptPlotCoords);
//        rect->topLeft->setTypeY(QCPItemPosition::ptViewportRatio);

//        rect->bottomRight->setTypeX(QCPItemPosition::ptPlotCoords);
//        rect->bottomRight->setTypeY(QCPItemPosition::ptViewportRatio);


//        rect->topLeft->setCoords(mRegression.x(item->size), 0);
//        rect->bottomRight->setCoords(mRegression.x(item->size)+100, 1);

//        rect->setBrush(QBrush(QColor(255,0,255,50)));

//        if (addItem(rect))
//            mSelectorRects.append(rect);

//    }

//qDebug()<<"selectors updated..";
//replot();
//}


void FsaPlot::setLeft(int x)
{


    qDebug()<<x;
    mLeftLine->start->setCoords(x,0);
    mLeftLine->end->setCoords(x,1);

    replot();

}

void FsaPlot::setBottom(int y)
{

    qDebug()<<y;

    mBottomLine->start->setCoords(0, y);
    mBottomLine->end->setCoords(1, y);

    replot();
}

void FsaPlot::setTop(int y)
{
    qDebug()<<y;

    mTopLine->start->setCoords(0, y);
    mTopLine->end->setCoords(1, y);


    replot();
}

void FsaPlot::setLeftLineVisible(bool visible)
{
    mLeftLine->setVisible(visible);

}

void FsaPlot::setBottomLineVisible(bool visible)
{
    mBottomLine->setVisible(visible);

}

void FsaPlot::setTopLineVisible(bool visible)
{
    mTopLine->setVisible(visible);

}

void FsaPlot::setLinesVisible(bool visible)
{
    mLeftLine->setVisible(visible);
    mBottomLine->setVisible(visible);
    mTopLine->setVisible(visible);

    replot();
}

void FsaPlot::setRegionVisible(bool visible)
{

}

//void FsaPlot::setSelectorModel(FsaSelectorModel *model)
//{
//    mSelectorModel = model;
//    connect(mSelectorModel,SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(updateSelectors()));

//}


//======================================================================

QVector<double> FsaPlot::diff(const QVector<double>& list)
{
    QVector<double> out;
    for (int i=0; i<list.size()-1; ++i)
        out.append(list.at(i+1) - list.at(i));
    return out;
}


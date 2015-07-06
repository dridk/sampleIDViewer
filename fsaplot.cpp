#include "fsaplot.h"
#include <QFileDialog>

FsaPlot::FsaPlot(QWidget *parent)
    :QCustomPlot(parent)
{


    mRoxRef<<35<<50<<75<<100<<139<<150<<160<<200<<250<<300<<340<<350<<400<<450<<490<<500;



    //    detectPeak(1400, 100, 100000);


}

int FsaPlot::dyeCount()
{
    AbifReader r = AbifReader(mCurrentFile);
    return r.data("Dye#.1").toInt();
}

QString FsaPlot::dyeName(int id)
{
    AbifReader r = AbifReader(mCurrentFile);
    return r.data(QString("DyeN.%1").arg(id+1)).toString();
}


QList<int> FsaPlot::detectPeak(int xMin,int yMin, int yMax)
{





    QVector<double> list = mDatas[ID_Y4];

    QVector<int> x;
    QVector<double> y;



    for (int i=0; i< list.size(); ++i)
    {
        if ( (list.at(i) >= yMin) &&  (list.at(i) <= yMax ) && (i >= xMin))
        {
            x.append(i);
            y.append(list.at(i));

        }



    }


    QVector<double> delta(diff(y));

    int old = delta.first();
    QList<int> dot ;
    for (int i=0; i<delta.size(); ++i)
    {
        double value = delta.at(i);

        if ( (old > 0) && (value < 0))
        {
            qDebug()<<"match" <<old<<value;
            dot.append(x[i]);
        }

        old = value;

    }


    qDebug()<<dot;

    QCPItemLine * line = new QCPItemLine(this);

    line->start->setCoords(0, yMin);
    line->end->setCoords(list.size(), yMin);
    line->setSelectable(true);

    addItem(line);




    foreach (int x, dot )
    {
        QCPItemPixmap * pix = new QCPItemPixmap(this);

        QPixmap p(":/loc.png");
        p = p.scaled(16,16);


        pix->setPixmap(p);


        pix->topLeft->setCoords(x-8, 2500);

        addItem(pix);

    }





    return QList<int> ();



}

QVector<double> FsaPlot::diff( QVector<double> list)
{

    QVector<double> out;

    for (int i=0; i<list.size()-1; ++i)
    {

        out.append(list.at(i+1) - list.at(i));

    }

    return out;


}

void FsaPlot::setFileName(const QString& filename)
{
    if (filename.isEmpty())
        return ;


    mCurrentFile = filename;


    AbifReader r = AbifReader(mCurrentFile);


    QVariantList y1  = r.data("DATA.1").toList();
    QVariantList y2  = r.data("DATA.2").toList();
    QVariantList y3  = r.data("DATA.3").toList();
    QVariantList y4  = r.data("DATA.4").toList();

    int size = y1.size();

    mDatas.append(QVector<double> (size));
    mDatas.append(QVector<double> (size));
    mDatas.append(QVector<double> (size));
    mDatas.append(QVector<double> (size));
    mDatas.append(QVector<double> (size));



    for (int i=0; i<size; ++i)
    {


        mDatas[ID_X][i] = i;
        mDatas[ID_Y1][i]= y1.at(i).toDouble();
        mDatas[ID_Y2][i]= y2.at(i).toDouble();
        mDatas[ID_Y3][i]= y3.at(i).toDouble();
        mDatas[ID_Y4][i]= y4.at(i).toDouble();


    }



    addGraph();
    graph(0)->setData( mDatas[ID_X],  mDatas[ID_Y1]);
    graph(0)->setPen(QPen(Qt::green));

    addGraph();
    graph(1)->setData(mDatas[ID_X], mDatas[ID_Y2]);
    graph(1)->setPen(QPen(Qt::blue));

    addGraph();
    graph(2)->setData(mDatas[ID_X], mDatas[ID_Y3]);
    graph(2)->setPen(QPen(Qt::black));

    addGraph();
    graph(3)->setData(mDatas[ID_X], mDatas[ID_Y4]);
    graph(3)->setPen(QPen(Qt::red));






    //load data



    //    QVector<double> y(ref.size());




    //    QFile file("testsacha.txt");

    //    QTextStream stream(&file);

    //    if (!file.open(QIODevice::WriteOnly))
    //        return;


    //        for (int i=0; i<ref.size(); ++i)
    //        {
    //            x[i] = i;
    //            y[i] = ref.at(i).toDouble();

    //            stream<<y[i]<<"\n";
    //        }


    //file.close();


    //            addGraph();
    //            graph(0)->setData(x, y);
    //            graph(0)->setPen(QPen(Qt::red));




    //qSort(y.begin(), y.end(), qGreater<double>());

    //  QVariantList listB = r.data("DATA.4").toList();


    //    QVector<double> a(listA.size());
    //    QVector<double> b(listA.size());


    //    for (int i=0; i<listA.size(); ++i)
    //    {
    //        x[i] = i;
    //        a[i] = listA.at(i).toDouble();
    //        b[i] = listB.at(i).toDouble();
    //    }


    //    addGraph();
    //    graph(0)->setData(x, a);
    //    graph(0)->setPen(QPen(Qt::blue));


    //    addGraph();
    //    graph(1)->setData(x, b);
    //    graph(1)->setPen(QPen(Qt::green));



    ////    // give the axes some labels:
    ////    xAxis->setLabel("x");
    ////    yAxis->setLabel("y");

    setInteraction(QCP::iRangeZoom,true);
    setInteraction(QCP::iRangeDrag,true);
    replot();
    rescaleAxes();





}

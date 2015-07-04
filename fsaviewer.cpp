#include "fsaviewer.h"
#include <QFileDialog>

FsaViewer::FsaViewer(QWidget *parent)
    :QCustomPlot(parent)
{



    setFileName("C:/sacha/M.fsa");

    mRoxRef<<35<<50<<75<<100<<139<<150<<160<<200<<250<<300<<340<<350<<400<<450<<490<<500;






}


void FsaViewer::setFileName(const QString& filename)
{
    if (filename.isEmpty())
        return ;

    AbifReader r = AbifReader(filename);





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

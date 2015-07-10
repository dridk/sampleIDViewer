#ifndef FSAPANELWIDGET_H
#define FSAPANELWIDGET_H
#include <QTabWidget>
#include <QtWidgets>
#include "abstractfsapanelwidget.h"
#include "fsaplot.h"
#include "fsaregionpanelwidget.h"


class FsaPanelWidget : public QTabWidget
{
    Q_OBJECT
public:
    FsaPanelWidget(QWidget * parent = 0);

    int add(AbstractFsaPanelWidget * widget);
     void setPlot(FsaPlot * plot);

protected slots :
     void changeActiveWidgets(int index);

private:


    QList<AbstractFsaPanelWidget *> mWidgets;
    FsaPlot * mPlot;
};

#endif // FSAPANELWIDGET_H

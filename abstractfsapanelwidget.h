#ifndef ABSTRACTFSAPANELWIDGET_H
#define ABSTRACTFSAPANELWIDGET_H

#include <QWidget>
#include "fsaplot.h"
class AbstractFsaPanelWidget : public QWidget
{
    Q_OBJECT
public:
    AbstractFsaPanelWidget(QWidget * parent = 0);
    void setPlot(FsaPlot * plot);
    FsaPlot *plot();

    virtual void init();
public slots:
    virtual void beforeReplot();
    virtual void afterReplot();
    virtual void setActive(bool enabled);




private:
    FsaPlot * mPlot;



};

#endif // ABSTRACTFSAPANELWIDGET_H

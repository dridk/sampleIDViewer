#include "abstractfsapanelwidget.h"

AbstractFsaPanelWidget::AbstractFsaPanelWidget(QWidget * parent)
    :QWidget(parent)
{

}

void AbstractFsaPanelWidget::setPlot(FsaPlot *plot)
{
    mPlot = plot;
    connect(mPlot,SIGNAL(beforeReplot()), this,SLOT(beforeReplot()));
    connect(mPlot,SIGNAL(afterReplot()),this,SLOT(afterReplot()));
    init();
}

FsaPlot *AbstractFsaPanelWidget::plot()
{
    return mPlot;
}

void AbstractFsaPanelWidget::init()
{

}

void AbstractFsaPanelWidget::beforeReplot()
{

}

void AbstractFsaPanelWidget::afterReplot()
{

}

void AbstractFsaPanelWidget::setActive(bool enabled)
{
    Q_UNUSED(enabled);
}


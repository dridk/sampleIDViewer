#include "fsapanelwidget.h"
#include "fsapeakpanelwidget.h"
#include "fsaregionpanelwidget.h"
FsaPanelWidget::FsaPanelWidget(QWidget * parent)
    :QTabWidget(parent)
{

    add(new FsaPeakPanelWidget());
    add(new FsaRegionPanelWidget());

    connect(this,SIGNAL(currentChanged(int)),this,SLOT(changeActiveWidgets(int)));

}

int FsaPanelWidget::add(AbstractFsaPanelWidget *widget)
{
    mWidgets.append(widget);
    return addTab(widget,widget->windowTitle());
}

void FsaPanelWidget::setPlot(FsaPlot *plot)
{
    mPlot = plot;

    foreach (AbstractFsaPanelWidget * w, mWidgets)
        w->setPlot(plot);


}

void FsaPanelWidget::changeActiveWidgets(int index)
{

    foreach (AbstractFsaPanelWidget * w, mWidgets)
    {
        if ( widget(index)  == w )
            w->setActive(true);
        else
            w->setActive(false);
    }

}

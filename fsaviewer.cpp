#include "fsaviewer.h"
#include <QSplitter>
FsaViewer::FsaViewer(QWidget *parent) : QWidget(parent)
{
   mPlot = new FsaPlot;
   mBar = new QToolBar;
   mPanel = new FsaPanelWidget;

   mDyeButton = new QToolButton;
   mDyeButton->setText("Dye");
   mDyeButton->setPopupMode(QToolButton::InstantPopup);

   mDyeButton->setMenu(new QMenu());
    QAction * startAction = mBar->addAction("Peak Detection");
    startAction->setCheckable(true);


   mBar->addWidget(mDyeButton);

   // set Pannel
   mPanel->setPlot(mPlot);

   QSplitter * splitter = new QSplitter(Qt::Horizontal);

   QVBoxLayout * layout = new QVBoxLayout;



   splitter->addWidget(mPlot);
   splitter->addWidget(mPanel);
   layout->addWidget(mBar);
   layout->addWidget(splitter);

   layout->setContentsMargins(0,0,0,0);
   layout->setSpacing(0);

   setLayout(layout);

   splitter->setStretchFactor(0, 10);
   splitter->setStretchFactor(1, 1);

   connect(startAction,SIGNAL(triggered(bool)),mPanel,SLOT(setVisible(bool)));


   setFileName("C:/sacha/M.fsa");


   resize(800,400);

}

void FsaViewer::setFileName(const QString &filename)
{


    mPlot->setFileName(filename);


    for (int i=0; i<mPlot->dyeCount(); ++i)
    {

        QPixmap pix(16,16);
        pix.fill(mPlot->dyeColor(i));

        QAction * action = mDyeButton->menu()->addAction((mPlot->dyeName(i)));
        action->setCheckable(true);
        action->setChecked(true);
        action->setObjectName(QString::number(i));
        action->setIcon(QIcon(pix));

        connect(action,SIGNAL(triggered(bool)),this,SLOT(setGraphVisible(bool)));


    }


mPanel->update();



}

void FsaViewer::setGraphVisible(bool visible)
{

    QAction * action = qobject_cast<QAction*>(sender());
    int index = action->objectName().toInt();

    mPlot->graph(index)->setVisible(visible);
    mPlot->replot();




}


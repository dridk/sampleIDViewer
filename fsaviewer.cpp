#include "fsaviewer.h"
#include <QSplitter>
FsaViewer::FsaViewer(QWidget *parent) : QWidget(parent)
{
    mPlot      = new FsaPlot;
    mBar       = new QToolBar;
    mPanel     = new FsaPanelWidget;
    mDyeButton = new QToolButton;

    mDyeButton->setText("Dye");
    mDyeButton->setIcon(QIcon(":/chart_curve.png"));
    mDyeButton->setPopupMode(QToolButton::InstantPopup);
    mDyeButton->setMenu(new QMenu());

    mBar->addWidget(mDyeButton);
    mBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mPanel->setPlot(mPlot);


    QAction * startAction = mBar->addAction(QIcon(":/control_panel.png"),"Peak Detection");
    startAction->setCheckable(true);

    // set Pannel
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
    loadDyeActions();




    mPanel->update();



}

void FsaViewer::setGraphVisible(bool visible)
{

    QAction * action = qobject_cast<QAction*>(sender());
    int index = action->objectName().toInt();

    mPlot->graph(index)->setVisible(visible);
    mPlot->replot();
}

void FsaViewer::loadDyeActions()
{
    mDyeButton->menu()->clear();
    for (int i=0; i<mPlot->dyeCount(); ++i)
    {
        QPixmap pix(16,16);
        pix.fill(mPlot->dyeColor(i));
        QAction * action = mDyeButton->menu()->addAction((mPlot->dyeName(i)));
        action->setCheckable(true);
        action->setChecked(true);
        action->setObjectName(QString::number(i));

        QIcon icon;

        icon.addPixmap(pix,QIcon::Normal,QIcon::On);


        pix.fill(mPlot->dyeColor(i).darker());
        icon.addPixmap(pix,QIcon::Normal, QIcon::Off);


        action->setIcon(icon);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(setGraphVisible(bool)));
    }
}


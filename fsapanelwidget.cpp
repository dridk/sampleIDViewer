#include "fsapanelwidget.h"

FsaPanelWidget::FsaPanelWidget(QWidget * parent)
    :QTabWidget(parent)
{
    mRefCombo = new QComboBox;
    mSizeMarkCombo = new QComboBox;
    mXMinBox  = new QSlider(Qt::Horizontal);
    mYMinBox = new QSlider(Qt::Horizontal);




    mYMaxBox = new QSlider(Qt::Horizontal);


    refStartButton = new QPushButton("Detect");
    peakStartButton = new QPushButton("Detect");

    mSelectorWidget = new FsaSelectorWidget;


    QFormLayout * refLayout  = new QFormLayout;
    QFormLayout * peakLayout = new QFormLayout;

    refLayout->addRow("marker Dye", mRefCombo);
    refLayout->addRow("marker type", mSizeMarkCombo);

    refLayout->addRow("X min", mXMinBox);
    refLayout->addRow("Y min", mYMinBox);
    refLayout->addRow("Y max", mYMaxBox);


    refLayout->addWidget(refStartButton);


    QWidget * refWidget = new QWidget;
    refWidget->setLayout(refLayout);

    addTab( refWidget,"size marker");
    addTab(mSelectorWidget, "Select area");


}

void FsaPanelWidget::setPlot(FsaPlot *plot)
{
    mPlot = plot;

    mPlot->setSelectorModel(mSelectorWidget->model());


    mXMinBox->setRange(0, 2000);


    connect(mXMinBox, SIGNAL(valueChanged(int)),mPlot,SLOT(setLeft(int)));
    connect(mYMinBox, SIGNAL(valueChanged(int)),mPlot,SLOT(setBottom(int)));
    connect(mYMaxBox, SIGNAL(valueChanged(int)),mPlot,SLOT(setTop(int)));



    connect(mPlot,SIGNAL(beforeReplot()),this,SLOT(axisUpdated()));
    connect(refStartButton,SIGNAL(clicked(bool)),mPlot,SLOT(detectRefPeaks()));





}

void FsaPanelWidget::update()
{

    for (int i=0; i<mPlot->dyeCount(); ++i)
    {

        QPixmap pix(16,16);
        pix.fill(mPlot->dyeColor(i));
        mRefCombo->addItem(QIcon(pix),mPlot->dyeName(i));



    }

}



void FsaPanelWidget::axisUpdated()
{

mXMinBox->setRange(mPlot->xAxis->range().lower, mPlot->xAxis->range().upper);
mYMinBox->setRange(mPlot->yAxis->range().lower, mPlot->yAxis->range().upper);
mYMaxBox->setRange(mPlot->yAxis->range().lower, mPlot->yAxis->range().upper);

}


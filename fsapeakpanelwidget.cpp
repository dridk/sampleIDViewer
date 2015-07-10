#include "fsapeakpanelwidget.h"

FsaPeakPanelWidget::FsaPeakPanelWidget(QWidget *parent) :
    AbstractFsaPanelWidget(parent)
{

    mRefCombo      = new QComboBox;
    mSizeMarkCombo = new QComboBox;
    mXMinBox       = new QSlider(Qt::Horizontal);
    mYMinBox       = new QSlider(Qt::Horizontal);
    mYMaxBox       = new QSlider(Qt::Horizontal);
    mStartButton    = new QPushButton("Detect");


    QFormLayout * fLayout = new QFormLayout;
    QVBoxLayout * vLayout = new QVBoxLayout;

    fLayout->addRow("marker Dye", mRefCombo);
    fLayout->addRow("marker type", mSizeMarkCombo);

    fLayout->addRow("X min", mXMinBox);
    fLayout->addRow("Y min", mYMinBox);
    fLayout->addRow("Y max", mYMaxBox);


    vLayout->addLayout(fLayout);
    vLayout->addStretch();
    vLayout->addWidget(mStartButton);


    setLayout(vLayout);


    setWindowTitle("Peak detection");

}

void FsaPeakPanelWidget::init()
{

    connect(mXMinBox, SIGNAL(valueChanged(int)),plot(),SLOT(setLeft(int)));
    connect(mYMinBox, SIGNAL(valueChanged(int)),plot(),SLOT(setBottom(int)));
    connect(mYMaxBox, SIGNAL(valueChanged(int)),plot(),SLOT(setTop(int)));

    connect(mStartButton,SIGNAL(clicked(bool)),plot(), SLOT(detectRefPeaks()));


}

void FsaPeakPanelWidget::beforeReplot()
{


    mXMinBox->setRange(plot()->xAxis->range().lower, plot()->xAxis->range().upper);
    mYMinBox->setRange(plot()->yAxis->range().lower, plot()->yAxis->range().upper);
    mYMaxBox->setRange(plot()->yAxis->range().lower, plot()->yAxis->range().upper);



}

void FsaPeakPanelWidget::setActive(bool enabled)
{

    qDebug()<<"actibe "<<enabled;

   plot()->setLinesVisible(enabled);

}


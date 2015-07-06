#include "fsapanelwidget.h"

FsaPanelWidget::FsaPanelWidget(QWidget * parent)
    :QTabWidget(parent)
{
    mRefCombo = new QComboBox;
    mSizeMarkCombo = new QComboBox;
    mXMinBox  = new QSpinBox();
    mYMinBox = new QSpinBox();
    mYMaxBox = new QSpinBox();


    refStartButton = new QPushButton("Detect");
    peakStartButton = new QPushButton("Detect");



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


}


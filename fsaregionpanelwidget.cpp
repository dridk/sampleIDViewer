#include "fsaregionpanelwidget.h"

FsaRegionPanelWidget::FsaRegionPanelWidget(QWidget *parent) :
    AbstractFsaPanelWidget(parent)
{

    mView = new QTableView ;
    mModel = new FsaRegionModel;
    mView->setModel(mModel);

    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->setAlternatingRowColors(true);
    mView->verticalHeader()->setDefaultSectionSize(20);
    mView->horizontalHeader()->setDefaultSectionSize(50);
    mView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);


    mView->verticalHeader()->hide();



    mAddButton = new QPushButton("Add");
    mRemButton = new QPushButton("Rem");


    QVBoxLayout * vLayout = new QVBoxLayout;

    QHBoxLayout * hLayout = new QHBoxLayout;

    hLayout->addWidget(mAddButton);
    hLayout->addWidget(mRemButton);

    vLayout->addWidget(mView);
    vLayout->addLayout(hLayout);

    setLayout(vLayout);


    connect(mAddButton,SIGNAL(clicked(bool)),mModel,SLOT(add()));
    connect(mRemButton, SIGNAL(clicked(bool)),this,SLOT(removeClicked()));
    connect(mModel,SIGNAL(changed()),this,SLOT(createRegions()));

    setWindowTitle("Set region");

}

FsaRegionModel *FsaRegionPanelWidget::model()
{
    return mModel;
}

QTableView *FsaRegionPanelWidget::view()
{
    return mView;
}

void FsaRegionPanelWidget::createRegions()
{

    plot()->clearRegion();

    for (int i=0; i<mModel->rowCount(); ++i)
    {

        QString name  = mModel->item(i)->name;
        int size      = mModel->item(i)->size;
        int range     = mModel->item(i)->range;

        plot()->addRegion(name, size, range);


    }



}

void FsaRegionPanelWidget::removeClicked()
{

    if (mView->currentIndex().isValid())
    {
        int index = mView->currentIndex().row();
        plot()->removeRegion(index);
        mModel->rem(index);


    }
}


#include "sampleidlistwidget.h"
#include <QDebug>
SampleIDListWidget::SampleIDListWidget(QWidget *parent)
    : QWidget(parent)
{

    mServerCombo = new QComboBox;
    mView        = new QListView;
    mFilterEdit  = new QLineEdit;
    mModel       = new SampleIDListModel;
    mProxyModel  = new QSortFilterProxyModel;


    mProxyModel->setSourceModel(mModel);
    mView->setModel(mProxyModel);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);

    mainLayout->addWidget(mServerCombo);
    mainLayout->addWidget(mView);
    mainLayout->addWidget(mFilterEdit);

    setLayout(mainLayout);

    mView->setIconSize(QSize(121,11));


    QAction * refreshAction = new QAction("refresh",this);

    addAction(refreshAction);



    connect(mView,SIGNAL(clicked(QModelIndex)),this,SLOT(clicked(QModelIndex)));
    connect(mModel,SIGNAL(stateChanged(QString)),this,SIGNAL(stateChanged(QString)));
    connect(refreshAction,SIGNAL(triggered(bool)),mModel,SLOT(loadAll()));
    connect(mFilterEdit, SIGNAL(returnPressed()), this,SLOT(filterChanged()));
}

bool SampleIDListWidget::isLoading()
{
    return mModel->isLoading();
}

void SampleIDListWidget::clicked(const QModelIndex &index)
{

    QModelIndex sourceIndex = mProxyModel->mapToSource(index);

    emit sampleIDClicked(mModel->sampleID(sourceIndex));

}

void SampleIDListWidget::filterChanged()
{

    mProxyModel->setFilterRegExp(mFilterEdit->text());

}


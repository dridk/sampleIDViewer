#include "fsaselectorwidget.h"

FsaSelectorWidget::FsaSelectorWidget(QWidget *parent) : QWidget(parent)
{

    mView = new QTableView ;
    mModel = new FsaSelectorModel;

    mView->setModel(mModel);

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

}

FsaSelectorModel *FsaSelectorWidget::model()
{
    return mModel;
}

QTableView *FsaSelectorWidget::view()
{
    return mView;
}


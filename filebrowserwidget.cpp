#include "filebrowserwidget.h"

FileBrowserWidget::FileBrowserWidget(QWidget * parent)
    :QListView(parent)
{
  mModel = new QFileSystemModel(this);
    mModel->setRootPath(QDir::currentPath());


    setRootIndex(mModel->index(QDir::currentPath()));
  setModel(mModel);



  connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(setRootIndex(QModelIndex)));

}


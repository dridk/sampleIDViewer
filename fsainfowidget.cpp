#include "fsainfowidget.h"
#include <QVBoxLayout>
FsaInfoWidget::FsaInfoWidget(QWidget *parent) : QWidget(parent)
{

    mView = new QTreeWidget;
    mView->setColumnCount(2);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget(mView);
    vLayout->setContentsMargins(0,0,0,0);

    setLayout(vLayout);



}

void FsaInfoWidget::setFileName(const QString &filename)
{

    if (filename.isEmpty())
        return;

    AbifReader r = AbifReader(filename);

    mView->addTopLevelItem(createItem("name", r.data("CTID.1")));
    mView->addTopLevelItem(createItem("author", r.data("User.1")));

    mView->addTopLevelItem(createItem("Dye 1", r.data("DyeN.1")));
    mView->addTopLevelItem(createItem("Dye 2", r.data("DyeN.2")));
    mView->addTopLevelItem(createItem("Dye 3", r.data("DyeN.3")));
    mView->addTopLevelItem(createItem("Dye 4", r.data("DyeN.4")));

    mView->addTopLevelItem(createItem("Type", r.data("MODF.1")));











}

QTreeWidgetItem * FsaInfoWidget::createItem(const QString &label, const QVariant &value)
{
    QTreeWidgetItem * item  = new QTreeWidgetItem;

    item->setText(0,label);
    item->setText(1, value.toString());

    return item;



}


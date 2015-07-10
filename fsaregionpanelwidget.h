#ifndef FSASELECTORWIDGET_H
#define FSASELECTORWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "fsaregionmodel.h"
#include "abstractfsapanelwidget.h"

class FsaRegionPanelWidget : public AbstractFsaPanelWidget
{
    Q_OBJECT
public:
    explicit FsaRegionPanelWidget(QWidget *parent = 0);

    FsaRegionModel * model();
    QTableView *view() ;

protected slots:
    void createRegions();
    void removeClicked();


private:
    FsaRegionModel * mModel;
    QTableView * mView;

    QPushButton * mAddButton;
    QPushButton * mRemButton;
};

#endif // FSASELECTORWIDGET_H

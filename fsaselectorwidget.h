#ifndef FSASELECTORWIDGET_H
#define FSASELECTORWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "fsaselectormodel.h"
class FsaSelectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FsaSelectorWidget(QWidget *parent = 0);

    FsaSelectorModel * model();
    QTableView *view() ;


private:
    FsaSelectorModel * mModel;
    QTableView * mView;

    QPushButton * mAddButton;
    QPushButton * mRemButton;
};

#endif // FSASELECTORWIDGET_H

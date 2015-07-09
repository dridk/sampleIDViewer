#ifndef PROTONLISTWIDGET_H
#define PROTONLISTWIDGET_H

#include <QtWidgets>
#include <QSortFilterProxyModel>
#include "sampleidlistmodel.h"

class SampleIDListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SampleIDListWidget(QWidget *parent = 0);
    bool isLoading();


signals:
    void sampleIDClicked(SampleID sampleId);
    void stateChanged(QString state);

protected slots:
    void clicked(const QModelIndex& index);
    void filterChanged();
private:
    QComboBox * mServerCombo;
    QListView * mView;
    QLineEdit * mFilterEdit;
    SampleIDListModel * mModel;
    QSortFilterProxyModel * mProxyModel;
};

#endif // PROTONLISTWIDGET_H

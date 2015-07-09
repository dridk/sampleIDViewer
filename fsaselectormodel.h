#ifndef FSASELECTORMODEL_H
#define FSASELECTORMODEL_H
#include <QAbstractTableModel>
#include "fsaselectoritem.h"

class FsaSelectorModel;
class FsaSelectorModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    FsaSelectorModel(QObject * parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    FsaSelectorItem *item(int row);
     Qt::ItemFlags flags(const QModelIndex &index) const;

public slots:
    void add(const QString& name, int size, int r);
    void add();
    void rem(int index);



private:
    QList<FsaSelectorItem*> mItems;



};

#endif // FSASELECTORMODEL_H

#ifndef FSASELECTORMODEL_H
#define FSASELECTORMODEL_H
#include <QAbstractTableModel>
#include "fsaregionitem.h"

class FsaRegionModel;
class FsaRegionModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    FsaRegionModel(QObject * parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    FsaRegionItem *item(int row);
     Qt::ItemFlags flags(const QModelIndex &index) const;

public slots:
    void add(const QString& name, int size, int r);
    void add();
    void rem(int index);

signals:
    void changed();



private:
    QList<FsaRegionItem*> mItems;



};

#endif // FSASELECTORMODEL_H

#include "fsaselectormodel.h"

FsaSelectorModel::FsaSelectorModel(QObject * parent)
    :QAbstractTableModel(parent)
{

}



int FsaSelectorModel::rowCount(const QModelIndex &parent) const
{
    return mItems.count();
}

int FsaSelectorModel::columnCount(const QModelIndex &parent) const
{

    return 3;
}

QVariant FsaSelectorModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();



    if ( (role == Qt::DisplayRole) || (role == Qt::EditRole ))
    {
        if (index.column() == 0)
            return mItems.at(index.row())->name;


        if (index.column() == 1)
            return mItems.at(index.row())->size;


        if (index.column() == 2)
            return mItems.at(index.row())->range;
    }


    return QVariant();
}

bool FsaSelectorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{


    if (!index.isValid())
        return false;

    if ( role == Qt::EditRole)
    {

        if (index.column() == 0)
            mItems[index.row()]->name = value.toString();

        if (index.column() == 1)
            mItems[index.row()]->size = value.toInt();


        if (index.column() == 2)
            mItems[index.row()]->range = value.toInt();



        return true;
    }



    return false;


}

FsaSelectorItem *FsaSelectorModel::item(int row )
{

    if ( ( row >=0) && (row < mItems.size() ))
        return mItems.at(row);

    return NULL;

}

Qt::ItemFlags FsaSelectorModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled;
}

void FsaSelectorModel::add(const QString &name, int size, int r)
{

    beginInsertRows(QModelIndex(),0,0);
    mItems.prepend(new FsaSelectorItem(name, size,r));
    endInsertRows();

}

void FsaSelectorModel::add()
{

    add("name",200, 10);
}

void FsaSelectorModel::rem(int index)
{

}

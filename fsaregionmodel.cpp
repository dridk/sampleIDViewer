#include "fsaregionmodel.h"

FsaRegionModel::FsaRegionModel(QObject * parent)
    :QAbstractTableModel(parent)
{

}



int FsaRegionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mItems.count();
}

int FsaRegionModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 3;
}

QVariant FsaRegionModel::data(const QModelIndex &index, int role) const
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

bool FsaRegionModel::setData(const QModelIndex &index, const QVariant &value, int role)
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


        emit changed();

        return true;
    }



    return false;


}

QVariant FsaRegionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal)
  {

      if (role == Qt::DisplayRole)
      {
          if (section == 0)
              return "Name";

          if ( section == 1)
              return  "Size";

          if (section == 2)
              return "Range";
      }

  }

  return QVariant();

}

FsaRegionItem *FsaRegionModel::item(int row )
{

    if ( ( row >=0) && (row < mItems.size() ))
        return mItems.at(row);

    return NULL;

}

Qt::ItemFlags FsaRegionModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)

    return Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled;
}

void FsaRegionModel::add(const QString &name, int size, int r)
{

    beginInsertRows(QModelIndex(),0,0);
    mItems.prepend(new FsaRegionItem(name, size,r));
    endInsertRows();

    emit changed();

}

void FsaRegionModel::add()
{
    add("name",200, 10);

}

void FsaRegionModel::rem(int index)
{
    beginResetModel();
    mItems.removeAt(index);
    endResetModel();

    emit changed();

}

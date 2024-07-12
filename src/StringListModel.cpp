
#include "StringListModel.h"

QVariant StringListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return {};
    if (index.row() > stringList.size())
        return {};
    if (role == Qt::DisplayRole)
        return stringList.at(index.row());
    else
        return {};
}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return {};

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

Qt::ItemFlags StringListModel::flags(const QModelIndex &index) const {

    return QAbstractListModel::flags(index);
}

int StringListModel::rowCount(const QModelIndex &parent) const {
    return stringList.count();
}



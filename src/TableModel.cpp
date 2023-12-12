#include "TableModel.h"
#include <QDebug>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

QStringList TableModel::getHorHeader() const
{
    return _horHeaderList;
}

void TableModel::setHorHeader(const QStringList &header)
{
    _horHeaderList=header;
    emit horHeaderChanged();
}

void TableModel::classBegin()
{
    qDebug()<<"TableModel::classBegin()";
}

void TableModel::componentComplete()
{
    qDebug()<<"TableModel::componentComplete()";
    _completed=true;
    if(!_initData.isEmpty()){
        loadData(_initData);
    }
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    qDebug()<<"roleNames()";
    //value表示取值，edit表示编辑
    return QHash<int,QByteArray>{
        { Qt::DisplayRole,"value" },
        { Qt::EditRole,"edit" }
    };
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //返回表头数据，无效的返回None
    if(role==Qt::DisplayRole){
        if(orientation==Qt::Horizontal){
            return _horHeaderList.value(section,QString::number(section));
        }else if(orientation==Qt::Vertical){
            return QString::number(section);
        }
    }
    return QVariant();
}

bool TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        if(orientation==Qt::Horizontal&&role==Qt::EditRole){
            _horHeaderList[section]=value.toString();
            emit headerDataChanged(orientation, section, section);
            return true;
        }
    }
    return false;
}


int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return _modelData.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return _horHeaderList.count();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return _modelData.at(index.row()).at(index.column());
    default:
        break;
    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (value.isValid()&&index.isValid()&&(data(index, role) != value)) {
        if(Qt::EditRole==role){
            _modelData[index.row()][index.column()]=value;
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }
    }
    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

void TableModel::loadData(const QVector<QVector<QVariant>> &data)
{
    beginResetModel();
    _modelData.clear();
    for(int i=0;i<data.count();i++){
        QVector<QVariant> newRow;
        for(int j = 0; j < data[0].count(); j++){
            newRow.append(data[i][j]);
        }
        _modelData.append(newRow);
    }
    qDebug()<<_modelData;
    endResetModel();
}

QVector<QVector<QVariant> > TableModel::initData() const
{
    return _initData;
}

void TableModel::setInitData(const QVector<QVector<QVariant> > &newInitData)
{
    if (_initData == newInitData)
        return;
    _initData = newInitData;
    emit initDataChanged();
}


bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid() || row < 0 || count == 0 ||
        row + count > _modelData.size())
        return false;
    beginRemoveRows(parent, row, row + count - 1);
    while (count-- > 0 && row < _modelData.size())
        _modelData.removeAt(row);
    endRemoveRows();
    return true;
}

//bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
//{//需要一个QJsonArray类型的数据insertData,此处先用initData代替，并且函数只能插入一行
//    if (parent.isValid() || row < 0 || count == 0 || count > 1){
//        qDebug()<<"Error! count > 1!";
//        return false;
//    }
//    beginInsertRows(parent, row, row + count - 1);
//    //获取表头的值
//    QList<QString> initialValue;
//    QVariant value = property("horHeader");
//    if (value.isValid()) {
//        initialValue = value.value<QList<QString>>();
//    }else{
//        qDebug()<<"Can't get horHeader!";
//        return false;
//    }
//    // 将值附加到 newRow
//    QJsonArray::iterator iter = _initData.begin();
//    const QJsonObject itemRow=(*iter).toObject();
//    QVector<QVariant> newRow;
//    foreach (const QString &item, initialValue) {
//        if (itemRow.contains(item)) { // 检查是否包含键
//            QVariant cellValue = itemRow.value(item); // 获取列名称对应的值, cellValue是QJsonValue类型的
//            newRow.append(cellValue); // 将值附加到 newRow
//        } else {
//            newRow.append(QVariant()); // 如果键不存在，附加一个无效的 QVariant
//        }
//    }

//    _modelData.insert(row, newRow);
//    endInsertRows();
//    return true;
//}


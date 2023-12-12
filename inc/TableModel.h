#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QQmlParserStatus>
#include <QHash>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

class TableModel : public QAbstractTableModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QStringList horHeader READ getHorHeader WRITE setHorHeader NOTIFY horHeaderChanged)

public:
    explicit TableModel(QObject *parent = nullptr);
    QStringList getHorHeader() const;
    void setHorHeader(const QStringList &header);

    // QQmlParserStatus：构造前
    void classBegin() override;
    // QQmlParserStatus：构造后
    void componentComplete() override;
    // 自定义role
    QHash<int,QByteArray> roleNames() const override;

    // 表头
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // 数据，这三个必须实现
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // 编辑
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    //bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE void loadData(const QVector<QVector<QVariant>> &data);

    QVector<QVector<QVariant> > initData() const;
    void setInitData(const QVector<QVector<QVariant> > &newInitData);

signals:
    void horHeaderChanged();
    void initDataChanged();

private:
    // 组件是否初始化完成
    bool _completed=false;
    // 初始数据
    QVector<QVector<QVariant>> _initData;
    // 数据展示
    QVector<QVector<QVariant>> _modelData;
    // 横项表头
    QList<QString> _horHeaderList;
    Q_PROPERTY(QVector<QVector<QVariant> > initData READ initData WRITE setInitData NOTIFY initDataChanged FINAL)
};

#endif // TABLEMODEL_H

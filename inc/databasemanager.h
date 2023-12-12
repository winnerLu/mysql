#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    bool connectDatabase();
    Q_INVOKABLE bool disconnectDatabase();
    Q_INVOKABLE void queryTable();
    Q_INVOKABLE void add();

public slots:
    void connectToDatabase(const QString &hostName, int port, const QString &dbName,
                           const QString &userName, const QString &password);
    void insertToDatabase(int studentID, const QString &studentName, const QString &classID);
    void insertToTableDot(int id, int datetime, double longitude, double latitude,
                          double length, double angle, int trajectory_id);
    void insertToTableTrajectory(int id, QString target);
    void deleteToDatabase(int studentID);
    void deleteToTableDot(int id);
    void deleteToTableTrajectory(int id);
    void modifyToDatabase(int studentID, const QString &studentName, const QString &classID);
    void modifyToTableDot(int id, int datetime, double longitude, double latitude,
                          double length, double angle, int trajectory_id);
    void modifyToTableTrajectory(int id, QString target);
    void queryByStudentIDToDatabase(int studentID);

signals:
    void connectionResult(bool success, const QString &errorMessage);
    void initTableWidgetData(QVector<QVector<QVariant>> m_modelData);

private:
    QSqlDatabase m_database;
    QVector<QVector<QVariant>> m_modelData;
    QVector<QVector<QVariant>> m_jsonArrayData;
    QList<QString> m_horHeader;

};

#endif // DATABASEMANAGER_H

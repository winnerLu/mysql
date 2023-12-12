#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject{parent}
{

}

bool DatabaseManager::connectDatabase()
{
    m_database = QSqlDatabase::addDatabase("QMYSQL");
    m_database.setHostName("localhost");
    m_database.setPort(3306);
    m_database.setDatabaseName("database_test"); // 数据库名
    m_database.setUserName("root");   // 数据库登录用户名
    m_database.setPassword("123456");   // 数据库登录密码
    if(m_database.open()){	//尝试打开数据库
        return true;
    }
    return m_database.open();
}

void DatabaseManager::connectToDatabase(const QString &hostName, int port, const QString &dbName,
                                        const QString &userName, const QString &password)
{
    m_database = QSqlDatabase::addDatabase("QMYSQL");
    m_database.setHostName(hostName);
    m_database.setPort(port);
    m_database.setDatabaseName(dbName);
    m_database.setUserName(userName);
    m_database.setPassword(password);

    if (m_database.open()) {
        emit connectionResult(true, "Connected to database successfully");
        qDebug()<<"Connected!!!";
    } else {
        emit connectionResult(false, m_database.lastError().text());
    }
}

void DatabaseManager::insertToDatabase(int studentID, const QString &studentName, const QString &classID)
{
    if(m_database.isOpen()){
        qDebug() << "m_database.isOpen()";
        QSqlQuery query;
        query.prepare("INSERT INTO students (student_id, student_name, class_id) "
                      "VALUES (:student_id, :student_name, :class_id)");
        query.bindValue(":student_id", studentID);
        query.bindValue(":student_name", studentName);
        query.bindValue(":class_id", classID);
        if (query.exec()) {
            qDebug() << "Row inserted successfully";
        } else {
            qDebug() << "Error inserting row:" << query.lastError().text();
        }
    }else{
        qDebug() << "Error opening database:" << m_database.lastError().text();
    }
}

void DatabaseManager::insertToTableDot(int id, int datetime, double longitude, double latitude, double length, double angle, int trajectory_id)
{
    if(m_database.isOpen()){
        qDebug() << "m_database.isOpen()";
        QSqlQuery query;
        query.prepare("INSERT INTO dot (id, datetime, longitude, latitude, length, angle, trajectory_id) "
                      "VALUES (:id, :datetime, :longitude, :latitude, :length, :angle, :trajectory_id)");
        query.bindValue(":id", id);
        query.bindValue(":datetime", datetime);
        query.bindValue(":longitude", longitude);
        query.bindValue(":latitude", latitude);
        query.bindValue(":length", length);
        query.bindValue(":angle", angle);
        query.bindValue(":trajectory_id", trajectory_id);
        if (query.exec()) {
            qDebug() << "Row inserted successfully";
        } else {
            qDebug() << "Error inserting row:" << query.lastError().text();
        }
    }else{
        qDebug() << "Error opening database:" << m_database.lastError().text();
    }
}

void DatabaseManager::insertToTableTrajectory(int id, QString target)
{
    if(m_database.isOpen()){
        qDebug() << "m_database.isOpen()";
        QSqlQuery query;
        query.prepare("INSERT INTO trajectory (id, target) "
                      "VALUES (:id, :target)");
        query.bindValue(":id", id);
        query.bindValue(":target", target);
        if (query.exec()) {
            qDebug() << "Row inserted successfully";
        } else {
            qDebug() << "Error inserting row:" << query.lastError().text();
        }
    }else{
        qDebug() << "Error opening database:" << m_database.lastError().text();
    }
}

void DatabaseManager::deleteToDatabase(int studentID)
{
    if(m_database.isOpen()){
        QSqlQuery query;
        QString sql = QString("DELETE FROM students WHERE student_id = %1").arg(studentID);
        if (query.exec(sql)) {
            qDebug() << "Row deleted successfully";
        } else {
            qDebug() << "Error deleting row:" << query.lastError().text();
        }
    }else{
        qDebug() << "Error opening database:" << m_database.lastError().text();
    }
}

void DatabaseManager::deleteToTableDot(int id)
{
    if(m_database.isOpen()){
        QSqlQuery query;
        QString sql = QString("DELETE FROM dot WHERE id = %1").arg(id);
        if (query.exec(sql)) {
            qDebug() << "Row deleted successfully";
        } else {
            qDebug() << "Error deleting row:" << query.lastError().text();
        }
    }else{
        qDebug() << "Error opening database:" << m_database.lastError().text();
    }
}

void DatabaseManager::deleteToTableTrajectory(int id)
{
    if(m_database.isOpen()){
        QSqlQuery query;
        QString sql = QString("DELETE FROM trajectory WHERE id = %1").arg(id);
        if (query.exec(sql)) {
            qDebug() << "Row deleted successfully";
        } else {
            qDebug() << "Error deleting row:" << query.lastError().text();
        }
    }else{
        qDebug() << "Error opening database:" << m_database.lastError().text();
    }
}

void DatabaseManager::modifyToDatabase(int studentID, const QString &studentName, const QString &classID)
{
    if (m_database.open()) {
        QSqlQuery query;

        QString sql = "UPDATE students SET student_name = :studentName, "
                      "class_id = :classID WHERE student_id = :studentID";

        // 绑定参数，防止SQL注入
        query.prepare(sql);
        query.bindValue(":studentID", studentID);
        query.bindValue(":studentName", studentName);
        query.bindValue(":classID", classID);

        // 执行SQL语句
        if (query.exec()) {
            qDebug() << "Row modified successfully";
        } else {
            qDebug() << "Error modifying row:" << query.lastError().text();
        }
    }else{
        qDebug() << "Error opening database:" << m_database.lastError().text();
    }
}

void DatabaseManager::modifyToTableDot(int id, int datetime, double longitude, double latitude, double length,
                                       double angle, int trajectory_id)
{
    if(m_database.isOpen()){
        qDebug() << "m_database.isOpen()";
        QSqlQuery query;
        query.prepare("UPDATE dot SET datetime = :datetime, longitude = :longitude, latitude = :latitude, "
                      "length = :length, angle = :angle, trajectory_id = :trajectory_id WHERE id = :id ");
        query.bindValue(":id", id);
        query.bindValue(":datetime", datetime);
        query.bindValue(":longitude", longitude);
        query.bindValue(":latitude", latitude);
        query.bindValue(":length", length);
        query.bindValue(":angle", angle);
        query.bindValue(":trajectory_id", trajectory_id);
        if (query.exec()) {
            qDebug() << "Row modified successfully";
        } else {
            qDebug() << "Error modifying row:" << query.lastError().text();
        }
    }else{
        qDebug() << "Error opening database:" << m_database.lastError().text();
    }
}

void DatabaseManager::modifyToTableTrajectory(int id, QString target)
{
    if (m_database.open()) {
        QSqlQuery query;

        QString sql = "UPDATE trajectory SET target = :target WHERE id = :id";

        // 绑定参数，防止SQL注入
        query.prepare(sql);
        query.bindValue(":id", id);
        query.bindValue(":target", target);

        // 执行SQL语句
        if (query.exec()) {
            qDebug() << "Row modified successfully";
        } else {
            qDebug() << "Error modifying row:" << query.lastError().text();
        }
    }else{
        qDebug() << "Error opening database:" << m_database.lastError().text();
    }
}

void DatabaseManager::queryByStudentIDToDatabase(int studentID)
{
    if(m_database.isOpen()){

    }else{
        qDebug() << "Error opening database:" << m_database.lastError().text();
    }
}

void DatabaseManager::queryTable()
{
    qDebug()<<"DatabaseManager::queryTable()";
    if(m_database.isOpen()){
        qDebug() << "m_database.isOpen()";
        m_modelData.clear();
        QSqlQuery query("SELECT * FROM students");
        while (query.next()) {//query.next()将指针移动到结果集的下一行
            QVector<QVariant> rowData;
            qDebug() << "query.record().count() = " << query.record().count();
            for (int i = 0; i < query.record().count(); ++i) {
                qDebug() << "Column name:" << query.record().fieldName(i);//获取表头
                rowData += query.value(i).toString();//+=相当于append?
            }
            m_modelData.append(rowData);
        }
        emit initTableWidgetData(m_modelData);
    }else{
        qDebug() << "Error opening database:" << m_database.lastError().text();
    }

}

void DatabaseManager::add()
{

}


bool DatabaseManager::disconnectDatabase()
{
    m_database.close();	//关闭数据库
    return false;
}



#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "DatabaseManager.h"
#include "TableModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // 注册 DatabaseManager 类到 QML 上下文中
    DatabaseManager databaseManager;
    engine.rootContext()->setContextProperty("databaseManager", &databaseManager);
    qmlRegisterType<TableModel>("TableModel",1,0,"TableModel");
    const QUrl url(u"qrc:/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

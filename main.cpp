#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client.h"
#include "server.h"

using namespace std;

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  Client client;
  client.setupQML(engine);
  client.networkClient->connectToServer();
  Server server;
  server.startServer();

  const QUrl url(QStringLiteral("qrc:qml/MainPage/MainPage.qml"));
  engine.load(url);

  return app.exec();
}

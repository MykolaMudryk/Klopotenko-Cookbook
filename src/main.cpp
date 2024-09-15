#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

using namespace std;

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  const QUrl url(QStringLiteral("qrc:qml/MainPage/MainPage.qml"));
  engine.load(url);

  return app.exec();
}

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>

#include "QtQml/qqmlapplicationengine.h"
#include "json_parser.h"
#include "network_client.h"
#include "qml_handler.h"

class Client : public QObject {
  Q_OBJECT

 public:
  explicit Client(QObject *parent = nullptr);

  void setupQML(QQmlApplicationEngine &engine);

 private:
  NetworkClient *networkClient;
  QmlHandler *qmlHandler;
  CategoryModel *categoryModel;
  JsonParser *jsonParser;
};

#endif  // CLIENT_H

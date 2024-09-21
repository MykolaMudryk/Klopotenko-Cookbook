#include "client.h"

#include <QQmlContext>

Client::Client(QObject *parent)
    : QObject(parent),
      networkClient(new NetworkClient(this)),
      qmlHandler(new QmlHandler(networkClient, this)),
      categoryModel(new CategoryModel(this)),
      jsonParser(new JsonParser(this)) {
  connect(networkClient, &NetworkClient::requestFinished, jsonParser,
          &JsonParser::extractCategoryName);
  connect(jsonParser, &JsonParser::categoryNameExtracted, qmlHandler,
          &QmlHandler::handleCategoryName);
}

void Client::setupQML(QQmlApplicationEngine &engine) {
  engine.rootContext()->setContextProperty("qmlHandler", qmlHandler);
  engine.rootContext()->setContextProperty("categoryModel", categoryModel);
}

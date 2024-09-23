#include "client.h"

#include <QQmlContext>

Client::Client(QObject *parent)
    : QObject(parent),
      networkClient(new NetworkClient(this)),
      qmlHandler(new QmlHandler(networkClient, this)),
      categoryModel(new RecipeModel(this)),
      jsonParser(new JsonParser(this)) {
  connect(networkClient, &NetworkClient::requestFinished, jsonParser,
          &JsonParser::extractCategory);
  connect(jsonParser, &JsonParser::categoryExtracted, qmlHandler,
          &QmlHandler::handleCategory);
}

void Client::setupQML(QQmlApplicationEngine &engine) {
  engine.rootContext()->setContextProperty("qmlHandler", qmlHandler);
  engine.rootContext()->setContextProperty("categoryModel", categoryModel);
}

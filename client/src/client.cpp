#include "client.h"

#include <QQmlContext>

Client::Client(QObject *parent)
    : QObject(parent),
      networkClient(new NetworkClient(this)),
      qmlHandler(new QmlHandler(networkClient, this)),
      jsonParser(new JsonParser(this)),
      categoryModel(new RecipeModel(this)),
      nationalityModel(new RecipeModel(this)) {
  connect(networkClient, &NetworkClient::requestFinished, jsonParser,
          &JsonParser::extractValues);
  connect(jsonParser, &JsonParser::categoryExtracted, qmlHandler,
          &QmlHandler::handleCategory);
}

void Client::setupQML(QQmlApplicationEngine &engine) {
  engine.rootContext()->setContextProperty("qmlHandler", qmlHandler);
  engine.rootContext()->setContextProperty("categoryModel", categoryModel);
  engine.rootContext()->setContextProperty("nationalityModel",
                                           nationalityModel);
}

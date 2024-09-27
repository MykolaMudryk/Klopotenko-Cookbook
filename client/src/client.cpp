#include "client.h"

#include <QQmlContext>

Client::Client(QObject *parent)
    : QObject(parent),
      networkClient(new NetworkClient(this)),
      qmlHandler(new QmlHandler(networkClient, this)),
      jsonParser(new JsonParser(this)) {
  connect(networkClient, &NetworkClient::requestFinished, jsonParser,
          &JsonParser::extractValues);

  connect(jsonParser, &JsonParser::categoryExtracted, qmlHandler,
          &QmlHandler::handleCategory);

  connect(jsonParser, &JsonParser::nationalityExtracted, qmlHandler,
          &QmlHandler::handleNationality);

  connect(jsonParser, &JsonParser::dishNameExtracted, qmlHandler,
          &QmlHandler::handleDishName);
}

void Client::setupQML(QQmlApplicationEngine &engine) {
  engine.rootContext()->setContextProperty("qmlHandler", qmlHandler);
}

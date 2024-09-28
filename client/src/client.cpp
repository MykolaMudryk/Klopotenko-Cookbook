#include "client.h"

#include <QQmlContext>

Client::Client(QObject *parent)
    : QObject(parent),
      networkClient(new NetworkClient(this)),
      jsonParser(new JsonParser(this)),
      categoryModel(new CategoryModel(networkClient, this)),
      nationalityModel(new NationalityModel(networkClient, this)),
      dishNameModel(new DishNameModel(networkClient, this)) {
  connect(networkClient, &NetworkClient::requestFinished, jsonParser,
          &JsonParser::extractValues);

  connect(jsonParser, &JsonParser::categoryExtracted, categoryModel,
          &CategoryModel::setCategory);

  connect(jsonParser, &JsonParser::nationalityExtracted, nationalityModel,
          &NationalityModel::setNationality);

  connect(jsonParser, &JsonParser::dishNameExtracted, dishNameModel,
          &DishNameModel::setDishName);
}

void Client::setupQML(QQmlApplicationEngine &engine) {
  engine.rootContext()->setContextProperty("categoryModel", categoryModel);
  engine.rootContext()->setContextProperty("nationalityModel",
                                           nationalityModel);
  engine.rootContext()->setContextProperty("dishNameModel", dishNameModel);
}

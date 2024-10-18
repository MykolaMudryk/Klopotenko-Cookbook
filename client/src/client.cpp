#include "client.h"

#include <QQmlContext>

Client::Client(QObject *parent)
    : QObject(parent),
      networkClient(new NetworkClient(this)),
      jsonParser(new JsonParser(this)),

      menuCategoryModel(new MenuCategoryModel(networkClient, this)),
      menuNationalityModel(new MenuNationModel(networkClient, this)),
      menuDishModel(new MenuDishModel(networkClient, this)),

      filterCategoryModel(new FilterCategoryModel(networkClient, this)),
      filterNationModel(new FilterNationModel(networkClient, this)),
      filterDishModel(new FilterDishModel(networkClient, this)),

      breadCrumb(new BreadCrumb(this)) {
  connect(networkClient, &NetworkClient::requestFinished, jsonParser,
          &JsonParser::extractValues);

  connect(jsonParser, &JsonParser::categoryNameIconExtracted, menuCategoryModel,
          &MenuCategoryModel::setCategoryNameIcon);

  connect(jsonParser, &JsonParser::nationalityExtracted, menuNationalityModel,
          &MenuNationModel::setNationality);

  connect(jsonParser, &JsonParser::dishNameExtracted, menuDishModel,
          &MenuDishModel::setDishName);
}

void Client::setupQML(QQmlApplicationEngine &engine) {
  engine.rootContext()->setContextProperty("menuCategoryModel",
                                           menuCategoryModel);
  engine.rootContext()->setContextProperty("menuNationalityModel",
                                           menuNationalityModel);
  engine.rootContext()->setContextProperty("menuDishModel", menuDishModel);

  engine.rootContext()->setContextProperty("filterCategoryModel",
                                           filterCategoryModel);
  engine.rootContext()->setContextProperty("nationModel", filterNationModel);
  engine.rootContext()->setContextProperty("dishModel", filterDishModel);

  engine.rootContext()->setContextProperty("breadCrumb", breadCrumb);
}

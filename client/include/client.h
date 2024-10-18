#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>

#include "QtQml/qqmlapplicationengine.h"
#include "client_json_parser.h"
#include "network_client.h"
#include "qmlHandling/breadcrumb_line.h"
#include "qmlHandling/dropdown_recipe_list.h"
#include "qmlHandling/filter_panel.h"

class Client : public QObject {
  Q_OBJECT

 public:
  explicit Client(QObject *parent = nullptr);

  void setupQML(QQmlApplicationEngine &engine);

  NetworkClient *networkClient;

 private:
  JsonParser *jsonParser;
  MenuCategoryModel *menuCategoryModel;
  MenuNationModel *menuNationalityModel;
  MenuDishModel *menuDishModel;

  FilterCategoryModel *filterCategoryModel;
  FilterNationModel *filterNationModel;
  FilterDishModel *filterDishModel;

  BreadCrumb *breadCrumb;
};

#endif  // CLIENT_H

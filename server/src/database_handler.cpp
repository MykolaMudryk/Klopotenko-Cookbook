#include "database_handler.h"

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent), db(QSqlDatabase::addDatabase("QMYSQL")) {}

bool DatabaseHandler::connectToDatabase() {
  db.setHostName("localhost");
  db.setDatabaseName("cookbook");
  db.setUserName("root");
  db.setPassword("12345678");

  if (!db.open()) {
    qDebug() << "Не вдалося підключитися до бази даних: " << db.lastError();
    return false;
  }

  qDebug() << "Підключено до бази даних!";
  return true;
}

QJsonDocument DatabaseHandler::getCategories() {
  QSqlQuery query(db);
  QJsonArray categoriesArray;

  query.prepare("SELECT category_name, icon_name FROM categories");

  if (query.exec()) {
    while (query.next()) {
      QJsonObject categoryObject;
      categoryObject["category_name"] = query.value(0).toString();
      categoryObject["icon_name"] = query.value(1).toString();

      categoriesArray.append(categoryObject);
    }
  } else {
    qDebug() << "Не вдалося виконати SQL-запит: " << query.lastError();
  }

  QJsonDocument doc(categoriesArray);
  return doc;
}

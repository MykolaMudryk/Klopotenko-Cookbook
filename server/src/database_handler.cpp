#include "database_handler.h"

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent), db(QSqlDatabase::addDatabase("QMYSQL")) {}

bool DatabaseHandler::connectToDatabase() {
  db.setHostName("localhost");
  db.setPort(3306);
  db.setDatabaseName("cookbook");
  db.setUserName("root");
  db.setPassword("12345678");

  if (!db.open()) {
    qDebug() << "Не вдалося підключитися до бази даних: "
             << db.lastError().text();
    ;
    return false;
  }

  qDebug() << "Підключено до бази даних!";

  return true;
}

QJsonArray DatabaseHandler::getCategories() {
  QSqlQuery query(db);
  QJsonArray categoriesArray;

  query.prepare("SELECT category_name, iconName FROM categories");

  if (query.exec()) {
    while (query.next()) {
      QJsonObject categoryObject;

      QString categoryName = query.value(0).toString();
      QString iconName = query.value(1).toString();

      categoryObject["category_name"] = categoryName;

      categoryObject["iconName"] = iconName;

      qDebug() << "Data after query on server" << categoryName << iconName;

      categoriesArray.append(categoryObject);
    }
  } else {
    qDebug() << "Failed to retrieve categories from database: "
             << query.lastError().text();
  }

  return categoriesArray;
}

QJsonArray DatabaseHandler::getNationality(const QString &categoryName) {
  QSqlQuery query(db);
  QJsonArray nationalitiesArray;

  query.prepare(R"(
        SELECT DISTINCT n.name
        FROM nationalities n
        JOIN recipes r ON n.id = r.nationality_id
        JOIN categories c ON r.category_id = c.id
        WHERE c.category_name = :category_name
    )");
  query.bindValue(":category_name", categoryName);

  if (query.exec()) {
    while (query.next()) {
      QString nationality = query.value(0).toString();
      nationalitiesArray.append(nationality);
    }
  } else {
    qDebug() << "Failed to retrieve nationalitites for hovered category from "
                "database: "
             << query.lastError().text();
  }

  return nationalitiesArray;
}

QJsonArray DatabaseHandler::setCategories(const QString &categoryName) {
  QSqlQuery query(db);

  query.prepare(
      "INSERT INTO categories (category_name) VALUES (:category_name)");

  query.bindValue(":category_name", categoryName);

  if (!query.exec()) {
    qDebug() << "Error adding category to database:"
             << query.lastError().text();
  }

  return getCategories();
}

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

QJsonDocument DatabaseHandler::getCategories() {
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
    qDebug() << query.lastError();
    QJsonObject errorObject;

    errorObject["Error"] = "Failed to retrieve categories from database";
    QJsonArray errorArray;
    errorArray.append(errorObject);

    return QJsonDocument(errorArray);
  }

  QJsonDocument doc(categoriesArray);
  return doc;
}

QJsonDocument DatabaseHandler::getNationality(const QString &categoryName) {
  QSqlQuery query;
  query.prepare(R"(
        SELECT DISTINCT n.name
        FROM nationalities n
        JOIN recipes r ON n.id = r.nationality_id
        JOIN categories c ON r.category_id = c.id
        WHERE c.name = :category_name
    )");
  query.bindValue(":category_name", categoryName);

  if (query.exec()) {
    QStringList nationalities;
    while (query.next()) {
      nationalities.append(query.value(0).toString());
    }

  } else {
    qDebug() << "SQL Error:" << query.lastError();
  }
}

QJsonDocument DatabaseHandler::setCategories(const QString &categoryName,
                                             const QString &iconName) {
  QSqlQuery query(db);
  QJsonArray categoriesArray;

  query.prepare(
      "INSERT INTO categories (category_name, iconName) VALUES "
      "(:category_name, :iconName)");
  query.bindValue(":category_name", categoryName);
  query.bindValue(":iconName", iconName);

  if (query.exec()) {
    qDebug() << "New category added successfully.";

  } else {
    qDebug() << "Error adding category:" << query.lastError().text();
  }
  QJsonDocument doc(categoriesArray);
  return doc;
}

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

      categoriesArray.append(categoryObject);
    }
    return categoriesArray;

  } else {
    qDebug() << "Failed to retrieve categories from database: "
             << query.lastError().text();

    return QJsonArray();
  }
}

QJsonArray DatabaseHandler::getNationality(const QString &categoryName) {
  QSqlQuery query(db);
  QJsonArray nationalitiesArray;

  int rowCount = 0;

  query.prepare(R"(
        SELECT DISTINCT n.nationality_name
        FROM nationalities n
        JOIN recipes r ON n.recipe_id = r.nationality_id
        JOIN categories c ON r.category_id = c.recipe_id
        WHERE c.category_name = :category_name
    )");
  query.bindValue(":category_name", categoryName);

  // qDebug() << "category name before sql query:" << categoryName;

  if (query.exec()) {
    while (query.next()) {
      rowCount++;

      QJsonObject nationalityObject;

      QString nationality = query.value(0).toString();

      nationalityObject["nationality_name"] = nationality;

      // qDebug() << "Data after query on server" << nationality;

      nationalitiesArray.append(nationalityObject);
    }
    return nationalitiesArray;

  } else if (rowCount == 0) {
    qDebug() << "No recipes found for this category.";
    return QJsonArray();

  } else {
    qDebug() << "Failed to retrieve nationalitites for hovered category from "
                "database: "
             << query.lastError().text();

    return QJsonArray();
  }
}

QJsonArray DatabaseHandler::getDishName(const QString &category,
                                        const QString &nationality) {
  QSqlQuery query(db);
  QJsonArray dishesArray;

  query.prepare(R"(
    SELECT DISTINCT d.name
    FROM dishes d
    JOIN recipes r ON d.recipe_id = r.dish_id
    JOIN nationalities n ON r.nationality_id = n.recipe_id
    JOIN categories c ON r.category_id = c.recipe_id
    WHERE n.nationality_name = :nationality_name
    AND c.category_name = :category_name
)");

  query.bindValue(":category_name", category);
  query.bindValue(":nationality_name", nationality);

  qDebug() << "Data before SQL query:" << category << nationality;

  if (query.exec()) {
    while (query.next()) {
      QJsonObject dishObject;

      QString dishName = query.value(0).toString();

      dishObject["dish_name"] = dishName;

      qDebug() << "Data after query on server" << dishName;

      dishesArray.append(dishObject);
    }
    return dishesArray;
  } else {
    qDebug()
        << "Failed to retrieve dishes for hovered nationality from database:"
        << query.lastError().text();
    return QJsonArray();
  }
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

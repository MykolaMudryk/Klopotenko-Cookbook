#include "server_json_parser.h"

ParseClientData::ParseClientData(QObject *parent)
    : QObject(parent), database(this) {
  if (!database.connectToDatabase()) {
    qDebug() << "{\"error\": \"Database connection failed\"}";
  }
}

QByteArray ParseClientData::extractCategory(const QString &getCategory) {
  if (getCategory == "GET_CATEGORIES") {
    QJsonArray categoriesArray = database.getCategories();

    if (!categoriesArray.isEmpty()) {
      QJsonDocument doc(categoriesArray);
      QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

      return jsonResponse;
    }
  }

  return QByteArray();
}

QByteArray ParseClientData::extractHoveredCategory(
    const QString &hoveredCategory) {
  if (hoveredCategory.startsWith("GET_NATIONALITY")) {
    QString categoryName = hoveredCategory.mid(16).trimmed();

    QJsonArray nationalitiesArray = database.getNationality(categoryName);

    QJsonDocument doc(nationalitiesArray);
    QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

    return jsonResponse;
  }

  return QByteArray();
}

QByteArray ParseClientData::extractDishName(const QString &nationality) {
  if (nationality.startsWith("GET_DISHNAME")) {
    QJsonArray dishNameArray = database.getDishName(nationality);

    QJsonDocument doc(dishNameArray);
    QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

    return jsonResponse;
  }

  return QByteArray();
}

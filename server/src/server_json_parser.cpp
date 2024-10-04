#include "server_json_parser.h"

ParseClientData::ParseClientData(QObject *parent)
    : QObject(parent), dropdownRecipes(this) {}

QByteArray ParseClientData::extractCategory(const QString &getCategory) {
  if (getCategory == "GET_CATEGORIES") {
    QJsonArray categoriesArray = dropdownRecipes.getCategories();

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

    QJsonArray nationalitiesArray =
        dropdownRecipes.getNationality(categoryName);

    QJsonDocument doc(nationalitiesArray);
    QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

    return jsonResponse;
  }

  return QByteArray();
}

QByteArray ParseClientData::extractDishName(const QString &hoveredData) {
  QString categoryKey = "HOVERED_CATEGORY:";
  QString nationalityKey = "HOVERED_NATIONALITY:";

  if (hoveredData.startsWith(categoryKey) &&
      hoveredData.contains(nationalityKey)) {
    int categoryStart = categoryKey.length();
    int nationalityStart = hoveredData.indexOf(nationalityKey);

    QString categoryName =
        hoveredData.mid(categoryStart, nationalityStart - categoryStart)
            .trimmed();
    QString nationality =
        hoveredData.mid(nationalityStart + nationalityKey.length()).trimmed();

    qDebug() << "Category:" << categoryName;
    qDebug() << "Nationality:" << nationality;

    QJsonArray dishNameArray =
        dropdownRecipes.getDishName(categoryName, nationality);

    QJsonDocument doc(dishNameArray);
    QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

    return jsonResponse;
  }

  return QByteArray();
}

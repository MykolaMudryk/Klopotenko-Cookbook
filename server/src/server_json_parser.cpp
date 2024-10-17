#include "server_json_parser.h"

ParseClientData::ParseClientData(QObject *parent)
    : QObject(parent), queryDropdownData(this), queryFilterData(this) {}

QByteArray ParseClientData::extractCategory() {
  QJsonArray categoriesArray = queryDropdownData.getCategories();

  QJsonDocument doc(categoriesArray);
  QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

  return jsonResponse;
}

QByteArray ParseClientData::extractHoveredCategory(
    const QString &hoveredCategory) {
  QString categoryName = hoveredCategory.mid(16).trimmed();

  QJsonArray nationalitiesArray =
      queryDropdownData.getNationality(categoryName);

  QJsonDocument doc(nationalitiesArray);
  QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

  return jsonResponse;
}

QByteArray ParseClientData::extractDishName(const QString &hoveredData) {
  QString categoryKey = "HOVERED_CATEGORY";
  QString nationalityKey = "HOVERED_NATIONALITY";

  int categoryStart = categoryKey.length();
  int nationalityStart = hoveredData.indexOf(nationalityKey);

  QString categoryName =
      hoveredData.mid(categoryStart, nationalityStart - categoryStart)
          .trimmed();
  QString nationality =
      hoveredData.mid(nationalityStart + nationalityKey.length()).trimmed();

  QJsonArray dishNameArray =
      queryDropdownData.getDishName(categoryName, nationality);

  QJsonDocument doc(dishNameArray);
  QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

  return jsonResponse;
}

QByteArray ParseClientData::allCategoryResponse() {
  QJsonArray allCategoriesArray = queryFilterData.getAllCategories();

  QJsonDocument doc(allCategoriesArray);
  QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

  return jsonResponse;
}

QByteArray ParseClientData::allNationResponse() {
  QJsonArray allNationArray = queryFilterData.getAllNation();

  QJsonDocument doc(allNationArray);
  QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

  return jsonResponse;
}

QByteArray ParseClientData::allDishResponse() {
  QJsonArray allDishArray = queryFilterData.getAllDish();

  QJsonDocument doc(allDishArray);
  QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

  return jsonResponse;
}

#include "server_json_parser.h"

ParseClientData::ParseClientData(QObject *parent)
    : QObject(parent), dropdownRecipes(this) {}

QByteArray ParseClientData::extractCategory(const QString &getCategory) {
  QJsonArray categoriesArray = dropdownRecipes.getCategories();

  QJsonDocument doc(categoriesArray);
  QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

  return jsonResponse;
}

QByteArray ParseClientData::extractHoveredCategory(
    const QString &hoveredCategory) {
  QString categoryName = hoveredCategory.mid(16).trimmed();

  QJsonArray nationalitiesArray = dropdownRecipes.getNationality(categoryName);

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
      dropdownRecipes.getDishName(categoryName, nationality);

  QJsonDocument doc(dishNameArray);
  QByteArray jsonResponse = doc.toJson(QJsonDocument::Compact);

  return jsonResponse;
}

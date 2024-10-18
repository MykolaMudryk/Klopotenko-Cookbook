#include "client_json_parser.h"

JsonParser::JsonParser(QObject *parent) : QObject(parent) {}

void JsonParser::registerHandlers() {
  signalMap.insert("category_name", [this](const QJsonObject &jsonObject) {
    QString categoryName = jsonObject.value("category_name").toString();
    QString iconName = jsonObject.value("iconName").toString();
    emit categoryNameIconExtracted(categoryName, iconName);
  });

  signalMap.insert("nationality_name", [this](const QJsonObject &jsonObject) {
    QString nationality = jsonObject.value("nationality_name").toString();
    emit nationalityExtracted(nationality);
  });

  signalMap.insert("dish_name", [this](const QJsonObject &jsonObject) {
    QString dishName = jsonObject.value("dish_name").toString();
    emit dishNameExtracted(dishName);
  });

  signalMap.insert("all_categories", [this](const QJsonObject &jsonObject) {
    QString allCategories = jsonObject.value("all_categories").toString();
    emit allCategoryExtracted(allCategories);
  });

  signalMap.insert("all_nation", [this](const QJsonObject &jsonObject) {
    QString allNation = jsonObject.value("all_nation").toString();
    emit allNationExtracted(allNation);
  });

  signalMap.insert("all_dishes", [this](const QJsonObject &jsonObject) {
    QString allDishes = jsonObject.value("all_dishes").toString();
    emit allDishesExtracted(allDishes);
  });
}

void JsonParser::extractValues(const QByteArray &jsonData) {
  QJsonDocument doc = QJsonDocument::fromJson(jsonData);

  if (!doc.isArray()) {
    qWarning() << "Received JSON is not an array.";
    return;
  }
    QJsonArray jsonArray = doc.array();

    if (signalMap.isEmpty()) {
      registerHandlers();
    }

    for (const QJsonValue &value : jsonArray) {
      QJsonObject jsonObject = value.toObject();

      for (auto it = signalMap.begin(); it != signalMap.end(); ++it) {
        if (jsonObject.contains(it.key())) {
          it.value()(jsonObject);
        }
      }
    }
}

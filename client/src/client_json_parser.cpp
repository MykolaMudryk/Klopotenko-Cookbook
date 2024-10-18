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

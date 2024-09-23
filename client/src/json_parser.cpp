#include "json_parser.h"

JsonParser::JsonParser(QObject *parent) : QObject(parent) {}

void JsonParser::extractCategory(const QByteArray &jsonData) {
  QJsonDocument doc = QJsonDocument::fromJson(jsonData);

  if (doc.isArray()) {
    QJsonArray jsonArray = doc.array();

    for (const QJsonValue &value : jsonArray) {
      QJsonObject jsonObject = value.toObject();

      QString categoryName = jsonObject.value("category_name").toString();
      QString iconName = jsonObject.value("iconName").toString();

      qDebug() << "Parsed category: " << categoryName << iconName;

      emit categoryExtracted(categoryName, iconName);
    }
  } else {
    qWarning() << "Received data isn't an array";
  }
}

void JsonParser::extractNationality(const QByteArray &jsonData) {
  QJsonDocument doc = QJsonDocument::fromJson(jsonData);

  if (doc.isArray()) {
    QJsonArray jsonArray = doc.array();

    for (const QJsonValue &value : jsonArray) {
      QJsonObject jsonObject = value.toObject();

      QString nationality = jsonObject.value("nationality_name").toString();

      qDebug() << "Parsed nationality: " << nationality;

      emit nationalityExtracted(nationality);
    }
  } else {
    qWarning() << "Received data isn't an array";
  }
}

void JsonParser::extractDishName(const QByteArray &jsonData) {
  QJsonDocument doc = QJsonDocument::fromJson(jsonData);

  if (doc.isArray()) {
    QJsonArray jsonArray = doc.array();

    for (const QJsonValue &value : jsonArray) {
      QJsonObject jsonObject = value.toObject();

      QString dishName = jsonObject.value("name").toString();

      qDebug() << "Parsed dishName: " << dishName;

      emit dishNameExtracted(dishName);
    }
  } else {
    qWarning() << "Received data isn't an array";
  }
}

#include "json_parser.h"

JsonParser::JsonParser(QObject *parent) : QObject(parent) {}

void JsonParser::extractCategoryName(const QByteArray &jsonData) {
  QJsonDocument doc = QJsonDocument::fromJson(jsonData);

  if (doc.isArray()) {
    QJsonArray jsonArray = doc.array();

    for (const QJsonValue &value : jsonArray) {
      QJsonObject jsonObject = value.toObject();

      QString categoryName = jsonObject.value("category_name").toString();
      QString iconName = jsonObject.value("iconName").toString();

      qDebug() << "Parsed data: " << categoryName << iconName;

      emit categoryNameExtracted(categoryName, iconName);
    }
  } else {
    qWarning() << "Received data isn't an array";
  }
}

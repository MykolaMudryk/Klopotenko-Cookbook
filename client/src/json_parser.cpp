#include "json_parser.h"

JsonParser::JsonParser(QObject *parent) : QObject(parent) {}

void JsonParser::extractCategoryName(const QByteArray &jsonData) {
  QJsonDocument doc = QJsonDocument::fromJson(jsonData);

  if (doc.isArray()) {
    QJsonArray jsonArray = doc.array();

    for (const QJsonValue &value : jsonArray) {
      if (value.isObject()) {
        QJsonObject jsonObject = value.toObject();

        QString categoryName = jsonObject.value("category_name").toString();
        QString iconName = jsonObject.value("iconName").toString();

        qDebug() << "Parsed data: " << categoryName << iconName;

        emit categoryNameExtracted(categoryName, iconName);

      } else {
        qWarning() << "Array element is not a valid JSON object.";
      }
    }
  } else {
    qWarning() << "Received data is not a valid JSON array.";
  }
}

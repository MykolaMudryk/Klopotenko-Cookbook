#include "client_json_parser.h"

JsonParser::JsonParser(QObject *parent) : QObject(parent) {}

void JsonParser::extractValues(const QByteArray &jsonData) {
  QJsonDocument doc = QJsonDocument::fromJson(jsonData);

  if (!doc.isArray()) {
    qWarning() << "Received JSON is not an array.";
    return;
  }
    QJsonArray jsonArray = doc.array();

    for (const QJsonValue &value : jsonArray) {
      QJsonObject jsonObject = value.toObject();

      if (jsonObject.contains("category_name") &&
          jsonObject.contains("iconName")) {
        QString categoryName = jsonObject.value("category_name").toString();
        QString iconName = jsonObject.value("iconName").toString();

        // qDebug() << "Parsed category on client: " << categoryName <<
        // iconName;

        emit categoryExtracted(categoryName, iconName);
      }

      if (jsonObject.contains("nationality_name")) {
        QString nationality = jsonObject.value("nationality_name").toString();

        qDebug() << "Parsed nationality on client: " << nationality;

        emit nationalityExtracted(nationality);
      }

      if (jsonObject.contains("name")) {
        QString dishName = jsonObject.value("name").toString();

        qDebug() << "Parsed dishName on client: " << dishName;

        emit dishNameExtracted(dishName);
      }
    }
}

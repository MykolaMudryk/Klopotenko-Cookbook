#include "json_parser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

JsonParser::JsonParser(QObject *parent) : QObject(parent) {}

void JsonParser::extractCategoryName(const QByteArray &jsonData) {
  QJsonDocument doc = QJsonDocument::fromJson(jsonData);

  if (!doc.isObject()) {
    qWarning() << "Received data is not a valid JSON object.";

    return;
  }

  QJsonObject jsonObject = doc.object();

  QString categoryName = jsonObject.value("category_name").toString();
  QString iconName = jsonObject.value("iconName").toString();
  emit categoryNameExtracted(categoryName, iconName);
}

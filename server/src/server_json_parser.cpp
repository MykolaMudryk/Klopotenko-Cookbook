#include "server_json_parser.h"

ParseClientData::ParseClientData(QObject *parent) : QObject(parent) {}

void ParseClientData::extractHoveredCategory(const QString &category) {
  if (category.startsWith("GET_NATIONALITY ")) {
    QString categoryName = category.mid(16);

    emit hoveredCategoryExtracted(categoryName);
  } else {
    QJsonObject errorObject;
    errorObject["error"] = "Unknown request";

    QJsonDocument errorDoc(errorObject);

    QByteArray errorByteArray = errorDoc.toJson(QJsonDocument::Compact);
    emit hoveredCategoryError(errorByteArray);
  }
}

#include "server_json_parser.h"

ServerJsonParser::ServerJsonParser(QObject *parent) : QObject(parent) {}

void ServerJsonParser::extractCategory(const QString &category) {
  if (category.startsWith("GET_NATIONALITY ")) {
    QString categoryName = category.mid(16);

    emit hoveredCategoryExtracted(categoryName);
  } else {
    QJsonObject errorObject;
    errorObject["error"] = "Unknown request";

    // Convert the JSON object to a QJsonDocument
    QJsonDocument errorDoc(errorObject);

    QByteArray errorByteArray = errorDoc.toJson(QJsonDocument::Compact);
    emit hoveredCategoryError(errorByteArray);
  }
}
// сигнал hoveredCategoryError має відправляти сигнал в getNationalities в класі
// Server ВИКОНАНО

// сигнал hoveredCategoryExtracted має відправлятиcь в форматі QJsonDocument
// getNationality в класі DatabaseHandler для створення sql запиту

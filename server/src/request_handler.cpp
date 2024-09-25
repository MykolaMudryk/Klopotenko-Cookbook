#include "request_handler.h"

RequestHandler::RequestHandler(QObject *parent)
    : QObject(parent), dbHandler(this) {}

QString RequestHandler::getCategories() {
  if (!dbHandler.connectToDatabase()) {
    return QString("{\"error\": \"Database connection failed\"}");
  }

  QJsonDocument categoriesData = dbHandler.getCategories();
  return categoriesData.toJson(QJsonDocument::Compact);
}

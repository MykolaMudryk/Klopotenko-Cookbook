#ifndef SERVER_JSON_PARSER_H
#define SERVER_JSON_PARSER_H

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QString>

#include "database_handler.h"

class ParseClientData : public QObject {
  Q_OBJECT
 private:
  DatabaseHandler database;
  QString hoveredCategoryName;

 public:
  explicit ParseClientData(QObject *parent = nullptr);

 public slots:
  QByteArray extractCategory(const QString &getCategory);
  QByteArray extractHoveredCategory(const QString &jsonResponse);
};

#endif  // JSON_PARSER_H

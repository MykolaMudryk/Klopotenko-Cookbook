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
  QueryDropdownData queryDropdownData;
  QueryFilterData queryFilterData;

 public:
  explicit ParseClientData(QObject *parent = nullptr);

 public slots:
  QByteArray extractCategory();
  QByteArray extractHoveredCategory(const QString &hoveredCategory);
  QByteArray extractDishName(const QString &hoveredData);

  QByteArray allCategoryResponse();
  QByteArray allNationResponse();
  QByteArray allDishResponse();
};

#endif  // JSON_PARSER_H

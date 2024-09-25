#ifndef SERVER_JSON_PARSER_H
#define SERVER_JSON_PARSER_H

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QString>

class ServerJsonParser : public QObject {
  Q_OBJECT
 private:
  QString hoveredCategoryName;

 public:
  explicit ServerJsonParser(QObject *parent = nullptr);

 public slots:
  void extractCategory(const QString &category);
 signals:
  void hoveredCategoryExtracted(const QString &categoryName);
  void hoveredCategoryError(const QByteArray &errorDoc);
};

#endif  // JSON_PARSER_H

// сигнал hoveredCategoryError має відправляти сигнал в getNationalities в класі
// Server

// сигнал hoveredCategoryExtracted має відправляти в getNationality в
// класі DatabaseHandler для створення sql запиту

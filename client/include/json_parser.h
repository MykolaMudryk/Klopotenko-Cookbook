#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QString>

class JsonParser : public QObject {
  Q_OBJECT
 private:
  QString categoryName;

 public:
  explicit JsonParser(QObject *parent = nullptr);

 public slots:
  void extractCategory(const QByteArray &jsonData);
  void extractNationality(const QByteArray &jsonData);
  void extractDishName(const QByteArray &jsonData);
 signals:
  void categoryExtracted(const QString &categoryName, const QString &iconName);
  void nationalityExtracted(const QString &nationality);
  void dishNameExtracted(const QString &nationality);
};

#endif  // JSON_PARSER_H

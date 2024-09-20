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
  void extractCategoryName(const QByteArray &jsonData);
 signals:
  void categoryNameExtracted(const QString &categoryName,
                             const QString &iconName);
};

#endif  // JSON_PARSER_H

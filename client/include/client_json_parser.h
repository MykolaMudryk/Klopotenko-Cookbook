#ifndef CLIENT_JSON_PARSER_H
#define CLIENT_JSON_PARSER_H

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
  QString iconName;
  QString nationality;
  QString dishName;

 public:
  explicit JsonParser(QObject *parent = nullptr);

 public slots:
  void extractValues(const QByteArray &jsonData);
 signals:
  void categoryNameIconExtracted(const QString &categoryName,
                                 const QString &iconName);
  void categoryNameExtracted(const QString &categoryName);

  void nationalityExtracted(const QString &nationality);
  void dishNameExtracted(const QString &nationality);
};

#endif  // CLIENT_JSON_PARSER_H

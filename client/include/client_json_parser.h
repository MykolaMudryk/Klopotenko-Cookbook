#ifndef CLIENT_JSON_PARSER_H
#define CLIENT_JSON_PARSER_H

#include <QByteArray>
#include <QHash>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

class JsonParser : public QObject {
  Q_OBJECT
 private:
  QString categoryName;
  QString iconName;
  QString nationality;
  QString dishName;

  QHash<QString, std::function<void(const QJsonObject &jsonObject)>> signalMap;

 public:
  explicit JsonParser(QObject *parent = nullptr);

  void registerHandlers();

 public slots:
  void extractValues(const QByteArray &jsonData);
 signals:
  void categoryNameIconExtracted(const QString &categoryName,
                                 const QString &iconName);
  void nationalityExtracted(const QString &nationality);
  void dishNameExtracted(const QString &nationality);

  void allCategoryExtracted(const QString &categoryName);
  void allNationExtracted(const QString &categoryName);
  void allDishesExtracted(const QString &categoryName);
};

#endif  // CLIENT_JSON_PARSER_H

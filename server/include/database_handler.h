#ifndef DATABASE_HANDLER
#define DATABASE_HANDLER

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class DatabaseHandler : public QObject {
  Q_OBJECT
 private:
  QSqlDatabase db;

 public:
  explicit DatabaseHandler(QObject *parent = nullptr);

  bool connectToDatabase();

  QJsonArray getCategories();

  QJsonArray getNationality(const QString &categoryName);

  QJsonArray getDishName(const QString &nationality, const QString &category);
};

#endif  // DATABASE_HANDLER

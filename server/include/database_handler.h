#ifndef DATABASE_HANDLER
#define DATABASE_HANDLER

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class DatabaseConnection : public QObject {
  Q_OBJECT
 private:
  QSqlDatabase db;

  static DatabaseConnection *instance;

  DatabaseConnection(const DatabaseConnection &) = delete;
  DatabaseConnection &operator=(const DatabaseConnection &) = delete;

  explicit DatabaseConnection(QObject *parent = nullptr);

 public:
  bool connectToDatabase();

  static DatabaseConnection *getInstance(QObject *parent = nullptr);

  QSqlDatabase getConnection() const;
};

class QueryDropdownData : public QObject {
  Q_OBJECT
 private:
  QSqlDatabase db;

 public:
  explicit QueryDropdownData(QObject *parent = nullptr);

  QJsonArray getCategories();

  QJsonArray getNationality(const QString &categoryName);

  QJsonArray getDishName(const QString &nationality, const QString &category);
};

class QueryFilterData : public QObject {
  Q_OBJECT
 private:
  QSqlDatabase db;

 public:
  explicit QueryFilterData(QObject *parent = nullptr);

  QJsonArray getAllCategories();

  QJsonArray getAllNation();

  QJsonArray getAllDish();
};

#endif  // DATABASE_HANDLER

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

  explicit DatabaseConnection(QObject *parent = nullptr);

 public:
  bool connectToDatabase();

  static DatabaseConnection *getInstance(QObject *parent = nullptr);

  QSqlDatabase getConnection() const;
};

class DropdownRecipes : public QObject {
  Q_OBJECT
 private:
  QSqlDatabase db;

 public:
  explicit DropdownRecipes(QObject *parent = nullptr);

  QJsonArray getCategories();

  QJsonArray getNationality(const QString &categoryName);

  QJsonArray getDishName(const QString &nationality, const QString &category);
};

#endif  // DATABASE_HANDLER

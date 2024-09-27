#ifndef RECIPE_MODEL_H
#define RECIPE_MODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QObject>
#include <QVariantMap>

#include "network_client.h"

class RecipeModel : public QAbstractListModel {
  Q_OBJECT

 private:
  QList<QVariantMap> m_recipes;

 public:
  explicit RecipeModel(QObject *parent = nullptr);

  enum RecipeRoles {
    CategoryNameRole = Qt::UserRole + 1,
    IconNameRole,
    NationalityRole,
    DishNameRole
  };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QHash<int, QByteArray> roleNames() const override;

  void clearNationalities();

  QStringList getNationality() const;

  void setNationality(const QString &nationality);

  void setCategories(const QString &categoryName, const QString &iconName);

  QStringList getCategories() const;

  void clearDishNames();

  void setDishName(const QString &dishName);

  QStringList getDishNames() const;
};

class QmlHandler : public QObject {
  Q_OBJECT
  Q_PROPERTY(
      RecipeModel *categoryModel READ categoryModel NOTIFY categoryChanged)
  Q_PROPERTY(RecipeModel *nationalityModel READ nationalityModel NOTIFY
                 nationalityChanged)
  Q_PROPERTY(
      RecipeModel *dishNameModel READ dishNameModel NOTIFY dishNameChanged)

 private:
  NetworkClient *networkClient;
  RecipeModel *m_categoryModel;
  RecipeModel *m_nationalityModel;
  RecipeModel *m_dishNameModel;

 public:
  explicit QmlHandler(NetworkClient *client = nullptr,
                      QObject *parent = nullptr);

  RecipeModel *categoryModel() const;
  RecipeModel *nationalityModel() const;
  RecipeModel *dishNameModel() const;

  int getNationalityRowCount();

 public slots:
  void fetchCategories();
  void fetchNationality(const QString &categoryName);
  void fetchDishName();

  void handleCategory(const QString &categoryName, const QString &iconName);
  void handleNationality(const QString &nationality);
  void handleDishName(const QString &dishName);

 signals:
  void categoryChanged();
  void nationalityChanged();
  void dishNameChanged();
};

#endif  // QMLHANDLER_H

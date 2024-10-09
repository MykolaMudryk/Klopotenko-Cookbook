#ifndef DROPDOWN_RECIPE_LIST_H
#define DROPDOWN_RECIPE_LIST_H

#include <QAbstractListModel>
#include <QList>
#include <QObject>

#include "network_client.h"

class MenuCategoryModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(MenuCategoryModel *menuCategoryModel READ menuCategoryModel NOTIFY
                 categoryNameIconChanged)

 private:
  struct Category {
    QString name;
    QString icon;
  };

  QList<Category> m_categories;
  NetworkClient *networkClient;

 public:
  explicit MenuCategoryModel(NetworkClient *client = nullptr,
                             QObject *parent = nullptr);

  enum CategoryRoles { CategoryNameRole = Qt::UserRole + 1, IconNameRole };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QHash<int, QByteArray> roleNames() const override;

  void setCategoryNameIcon(const QString &categoryName,
                           const QString &iconName);

  void setCategoryName(const QString &categoryName);

  MenuCategoryModel *menuCategoryModel() const;

 public slots:
  void fetchCategories();

 signals:
  void categoryNameIconChanged();
  void categoryForFilter();
};

class MenuNationModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(MenuNationModel *menuNationalityModel READ menuNationalityModel
                 NOTIFY nationalityChanged)

 private:
  QList<QString> m_nationalities;
  NetworkClient *networkClient;

 public:
  explicit MenuNationModel(NetworkClient *client = nullptr,
                           QObject *parent = nullptr);

  enum NationalityRoles { NationalityRole = Qt::UserRole + 1 };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE void clearNationalities();

  void setNationality(const QString &nationality);

  MenuNationModel *menuNationalityModel() const;

 public slots:
  void fetchNationality(const QString &categoryName);

 signals:
  void nationalityChanged();
};

class MenuDishModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(
      MenuDishModel *menuDishModel READ menuDishModel NOTIFY dishNameChanged)

 private:
  QList<QString> m_dishNames;
  NetworkClient *networkClient;

 public:
  explicit MenuDishModel(NetworkClient *client = nullptr,
                         QObject *parent = nullptr);

  enum DishNameRoles { DishNameRole = Qt::UserRole + 1 };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE void clearDishNames();

  void setDishName(const QString &dishName);

  MenuDishModel *menuDishModel() const;

 public slots:
  void fetchDishName(const QString &categoryName, const QString &nationality);

 signals:
  void dishNameChanged();
};

#endif  // DROPDOWN_RECIPE_LIST_H

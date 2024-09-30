#ifndef QMLHANDLER_H
#define QMLHANDLER_H

#include <QAbstractListModel>
#include <QList>
#include <QObject>

#include "network_client.h"

class CategoryModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(
      CategoryModel *categoryModel READ categoryModel NOTIFY categoryChanged)

 private:
  struct Category {
    QString name;
    QString icon;
  };

  QList<Category> m_categories;
  NetworkClient *networkClient;

 public:
  explicit CategoryModel(NetworkClient *client = nullptr,
                         QObject *parent = nullptr);

  enum CategoryRoles { CategoryNameRole = Qt::UserRole + 1, IconNameRole };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QHash<int, QByteArray> roleNames() const override;

  void setCategory(const QString &categoryName, const QString &iconName);

  CategoryModel *categoryModel() const;

 public slots:
  void fetchCategories();

 signals:
  void categoryChanged();
};

class NationalityModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(NationalityModel *nationalityModel READ nationalityModel NOTIFY
                 nationalityChanged)

 private:
  QList<QString> m_nationalities;
  NetworkClient *networkClient;

 public:
  explicit NationalityModel(NetworkClient *client = nullptr,
                            QObject *parent = nullptr);

  enum NationalityRoles { NationalityRole = Qt::UserRole + 1 };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE void clearNationalities();

  void setNationality(const QString &nationality);

  NationalityModel *nationalityModel() const;

 public slots:
  void fetchNationality(const QString &categoryName);

 signals:
  void nationalityChanged();
};

class DishNameModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(
      DishNameModel *dishNameModel READ dishNameModel NOTIFY dishNameChanged)

 private:
  QList<QString> m_dishNames;
  NetworkClient *networkClient;

 public:
  explicit DishNameModel(NetworkClient *client = nullptr,
                         QObject *parent = nullptr);

  enum DishNameRoles { DishNameRole = Qt::UserRole + 1 };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE void clearDishNames();

  void setDishName(const QString &dishName);

  DishNameModel *dishNameModel() const;

 public slots:
  void fetchDishName(const QString &categoryName, const QString &nationality);

 signals:
  void dishNameChanged();
};

#endif  // QMLHANDLER_H

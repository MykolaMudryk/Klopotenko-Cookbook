#ifndef QMLHANDLER_H
#define QMLHANDLER_H

#include <QAbstractListModel>
#include <QList>
#include <QObject>

#include "network_client.h"

class CategoryModel : public QAbstractListModel {
  Q_OBJECT

 public:
  struct CategoryItem {
    QString categoryName;
    QString iconName;
  };

  QList<CategoryItem> m_categories;

  enum CategoryRoles { NameRole = Qt::UserRole + 1, IconRole };

  explicit CategoryModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QHash<int, QByteArray> roleNames() const override;

  void setCategories(const QList<CategoryItem> &categories);
  QList<CategoryItem> getCategories() const;
};

class QmlHandler : public QObject {
  Q_OBJECT
  Q_PROPERTY(CategoryModel *categoryModel READ categoryModel NOTIFY
                 categoryModelChanged)

 private:
  NetworkClient *networkClient;
  CategoryModel *m_categoryModel;

 public:
  explicit QmlHandler(NetworkClient *client, QObject *parent = nullptr);

  CategoryModel *categoryModel() const;

 public slots:
  void fetchCategories();
  void handleCategoryName(const QString &categoryName, const QString &iconName);

 signals:
  void categoryModelChanged();
};

#endif  // QMLHANDLER_H

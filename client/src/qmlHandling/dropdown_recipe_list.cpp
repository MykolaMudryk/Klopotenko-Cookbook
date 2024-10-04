#include <QObject>

#include "qmlHandling/dropdown_recipe_list.h"

CategoryModel::CategoryModel(NetworkClient *client, QObject *parent)
    : QAbstractListModel(parent), networkClient(client) {}

int CategoryModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_categories.count();
}

QVariant CategoryModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_categories.count()) {
    return QVariant();
  }

  const Category &category = m_categories.at(index.row());

  if (role == CategoryNameRole) {
    return category.name;
  } else if (role == IconNameRole) {
    return category.icon;
  }

  return QVariant();
}

QHash<int, QByteArray> CategoryModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[CategoryNameRole] = "categoryName";
  roles[IconNameRole] = "iconName";
  return roles;
}

void CategoryModel::setCategory(const QString &categoryName,
                                const QString &iconName) {
  for (const Category &existingCategory : m_categories) {
    if (existingCategory.name == categoryName &&
        existingCategory.icon == iconName) {
      return;
    }
  }

  beginInsertRows(QModelIndex(), m_categories.count(), m_categories.count());
  m_categories.append({categoryName, iconName});
  endInsertRows();
  emit categoryChanged();
}

CategoryModel *CategoryModel::categoryModel() const {
  return const_cast<CategoryModel *>(this);
}

void CategoryModel::fetchCategories() {
  networkClient->sendMessage("GET_CATEGORIES");
}

NationalityModel::NationalityModel(NetworkClient *client, QObject *parent)
    : QAbstractListModel(parent), networkClient(client) {}

int NationalityModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_nationalities.count();
}

QVariant NationalityModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_nationalities.count()) {
    return QVariant();
  }

  if (role == NationalityRole) {
    return m_nationalities.at(index.row());
  }

  return QVariant();
}

QHash<int, QByteArray> NationalityModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NationalityRole] = "nationality";
  return roles;
}

void NationalityModel::clearNationalities() {
  beginResetModel();
  m_nationalities.clear();
  endResetModel();
}

void NationalityModel::setNationality(const QString &nationality) {
  for (const QString &existingNationality : m_nationalities) {
    if (existingNationality == nationality) {
      return;
    }
  }

  beginInsertRows(QModelIndex(), m_nationalities.count(),
                  m_nationalities.count());
  m_nationalities.append(nationality);
  endInsertRows();

  emit nationalityChanged();
}

NationalityModel *NationalityModel::nationalityModel() const {
  return const_cast<NationalityModel *>(this);
}

void NationalityModel::fetchNationality(const QString &categoryName) {
  QString message = QString("GET_NATIONALITY %1").arg(categoryName);
  networkClient->sendMessage(message);
}

DishNameModel::DishNameModel(NetworkClient *client, QObject *parent)
    : QAbstractListModel(parent), networkClient(client) {}

void DishNameModel::fetchDishName(const QString &categoryName,
                                  const QString &nationality) {
  QString message = QString("HOVERED_CATEGORY:%1 HOVERED_NATIONALITY:%2")
                        .arg(categoryName, nationality);

  qDebug() << "Data before request:" << message;
  networkClient->sendMessage(message);
}

int DishNameModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_dishNames.count();
}

QVariant DishNameModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_dishNames.count()) {
    return QVariant();
  }

  if (role == DishNameRole) {
    return m_dishNames.at(index.row());
  }

  return QVariant();
}

QHash<int, QByteArray> DishNameModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[DishNameRole] = "dishName";
  return roles;
}

void DishNameModel::clearDishNames() {
  beginResetModel();
  m_dishNames.clear();
  endResetModel();
}

void DishNameModel::setDishName(const QString &dishName) {
  for (const QString &existingDishName : m_dishNames) {
    if (existingDishName == dishName) {
      return;
    }
  }

  beginInsertRows(QModelIndex(), m_dishNames.count(), m_dishNames.count());
  m_dishNames.append(dishName);
  endInsertRows();
  emit dishNameChanged();
}

DishNameModel *DishNameModel::dishNameModel() const {
  return const_cast<DishNameModel *>(this);
}

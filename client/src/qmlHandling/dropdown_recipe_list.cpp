#include "qmlHandling/dropdown_recipe_list.h"

MenuCategoryModel::MenuCategoryModel(NetworkClient *client, QObject *parent)
    : QAbstractListModel(parent), networkClient(client) {}

int MenuCategoryModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_categories.count();
}

QVariant MenuCategoryModel::data(const QModelIndex &index, int role) const {
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

QHash<int, QByteArray> MenuCategoryModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[CategoryNameRole] = "categoryName";
  roles[IconNameRole] = "iconName";
  return roles;
}

void MenuCategoryModel::setCategoryNameIcon(const QString &categoryName,
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
  emit categoryNameIconChanged();
}

MenuCategoryModel *MenuCategoryModel::menuCategoryModel() const {
  return const_cast<MenuCategoryModel *>(this);
}

void MenuCategoryModel::fetchCategories() {
  networkClient->sendMessage("GET_CATEGORIES");
}

MenuNationModel::MenuNationModel(NetworkClient *client, QObject *parent)
    : QAbstractListModel(parent), networkClient(client) {}

int MenuNationModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_nationalities.count();
}

QVariant MenuNationModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_nationalities.count()) {
    return QVariant();
  }

  if (role == NationalityRole) {
    return m_nationalities.at(index.row());
  }

  return QVariant();
}

QHash<int, QByteArray> MenuNationModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NationalityRole] = "nationality";
  return roles;
}

void MenuNationModel::clearNationalities() {
  beginResetModel();
  m_nationalities.clear();
  endResetModel();
}

void MenuNationModel::setNationality(const QString &nationality) {
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

MenuNationModel *MenuNationModel::menuNationalityModel() const {
  return const_cast<MenuNationModel *>(this);
}

void MenuNationModel::fetchNationality(const QString &categoryName) {
  QString message = QString("GET_NATIONALITY %1").arg(categoryName);
  networkClient->sendMessage(message);
}

MenuDishModel::MenuDishModel(NetworkClient *client, QObject *parent)
    : QAbstractListModel(parent), networkClient(client) {}

void MenuDishModel::fetchDishName(const QString &categoryName,
                                  const QString &nationality) {
  QString message = QString("HOVERED_CATEGORY %1 HOVERED_NATIONALITY %2")
                        .arg(categoryName, nationality);

  // qDebug() << "Data before request:" << message;
  networkClient->sendMessage(message);
}

int MenuDishModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_dishNames.count();
}

QVariant MenuDishModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_dishNames.count()) {
    return QVariant();
  }

  if (role == DishNameRole) {
    return m_dishNames.at(index.row());
  }

  return QVariant();
}

QHash<int, QByteArray> MenuDishModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[DishNameRole] = "dishName";
  return roles;
}

void MenuDishModel::clearDishNames() {
  beginResetModel();
  m_dishNames.clear();
  endResetModel();
}

void MenuDishModel::setDishName(const QString &dishName) {
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

MenuDishModel *MenuDishModel::menuDishModel() const {
  return const_cast<MenuDishModel *>(this);
}

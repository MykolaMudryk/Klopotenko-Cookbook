#include "qml_handler.h"

#include <QObject>

RecipeModel::RecipeModel(QObject *parent) : QAbstractListModel(parent) {}

int RecipeModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_recipes.count();
}

QVariant RecipeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_recipes.count()) {
    return QVariant();
  }

  const QVariantMap &item = m_recipes.at(index.row());

  switch (role) {
    case CategoryNameRole:
      return item.value("categoryName");
    case IconNameRole:
      return item.value("iconName");
    case NationalityRole:
      return item.value("nationality");
    case DishNameRole:
      return item.value("dishName");
    default:
      return QVariant();
  }
}

QHash<int, QByteArray> RecipeModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[CategoryNameRole] = "categoryName";
  roles[IconNameRole] = "iconName";
  roles[NationalityRole] = "nationality";
  roles[DishNameRole] = "dishName";
  return roles;
}

void RecipeModel::clearNationalities() {
  beginResetModel();
  for (QVariantMap &item : m_recipes) {
    item.remove("nationality");
  }
  endResetModel();
}

void RecipeModel::clearDishNames() {
  beginResetModel();
  for (QVariantMap &item : m_recipes) {
    item.remove("dishName");
  }
  endResetModel();
}

void RecipeModel::setCategories(const QString &categoryName,
                                const QString &iconName) {
  bool exists = false;
  for (const auto &category : m_recipes) {
    if (category.value("categoryName").toString() == categoryName &&
        category.value("iconName").toString() == iconName) {
      exists = true;
      break;
    }
  }

  if (!exists) {
    beginInsertRows(QModelIndex(), m_recipes.count(), m_recipes.count());

    QVariantMap newCategory;
    newCategory["categoryName"] = categoryName;
    newCategory["iconName"] = iconName;

    m_recipes.append(newCategory);

    endInsertRows();
  }
}

void RecipeModel::setNationality(const QString &nationality) {
  bool exists = false;
  for (const auto &cuisine : m_recipes) {
    if (cuisine.value("nationality").toString() == nationality) {
      exists = true;
      break;
    }
  }

  if (!exists) {
    beginInsertRows(QModelIndex(), m_recipes.count(), m_recipes.count());

    QVariantMap newNationality;
    newNationality["nationality"] = nationality;

    m_recipes.append(newNationality);

    endInsertRows();
  }
}

void RecipeModel::setDishName(const QString &dishName) {
  bool exists = false;
  for (const auto &dish : m_recipes) {
    if (dish.value("dishName").toString() == dishName) {
      exists = true;
      break;
    }
  }

  if (!exists) {
    beginInsertRows(QModelIndex(), m_recipes.count(), m_recipes.count());

    QVariantMap dishName;
    dishName["dishName"] = dishName;

    m_recipes.append(dishName);

    endInsertRows();
  }
}

QStringList RecipeModel::getCategories() const {
  QStringList categories;
  for (const auto &recipe : m_recipes) {
    categories.append(recipe.value("categoryName").toString());
    categories.append(recipe.value("iconName").toString());
  }
  return categories;
}

QStringList RecipeModel::getNationality() const {
  QStringList nationalities;
  for (const auto &recipe : m_recipes) {
    nationalities.append(recipe.value("nationality").toString());
  }
  return nationalities;
}

QStringList RecipeModel::getDishNames() const {
  QStringList dishNames;
  for (const auto &recipe : m_recipes) {
    dishNames.append(recipe.value("dishName").toString());
  }
  return dishNames;
}

QmlHandler::QmlHandler(NetworkClient *client, QObject *parent)
    : QObject(parent),
      networkClient(client),
      m_categoryModel(new RecipeModel(this)),
      m_nationalityModel(new RecipeModel(this)),
      m_dishNameModel(new RecipeModel(this)) {}

void QmlHandler::fetchCategories() {
  networkClient->sendMessage("GET_CATEGORIES");
}

void QmlHandler::fetchNationality(const QString &categoryName) {
  if (!m_nationalityModel->getNationality().isEmpty()) {
    m_nationalityModel->clearNationalities();
  }
  QString message = QString("GET_NATIONALITY %1").arg(categoryName);
  networkClient->sendMessage(message);
}

void QmlHandler::fetchDishName() {
  if (!m_nationalityModel->getNationality().isEmpty()) {
    m_nationalityModel->clearDishNames();
  }
  networkClient->sendMessage("GET_DISHNAME");
}

RecipeModel *QmlHandler::categoryModel() const { return m_categoryModel; }

RecipeModel *QmlHandler::nationalityModel() const { return m_nationalityModel; }

RecipeModel *QmlHandler::dishNameModel() const { return m_dishNameModel; }

void QmlHandler::handleCategory(const QString &categoryName,
                                const QString &iconName) {
  m_categoryModel->setCategories(categoryName, iconName);

  emit categoryChanged();
}

void QmlHandler::handleNationality(const QString &nationality) {

  m_nationalityModel->setNationality(nationality);

  emit nationalityChanged();
}

void QmlHandler::handleDishName(const QString &dishName) {
  qDebug() << "handleDishName triggered";

  m_dishNameModel->setDishName(dishName);

  emit dishNameChanged();
}

#include "qml_handler.h"

#include <QObject>

CategoryModel::CategoryModel(QObject *parent) : QAbstractListModel(parent) {}

int CategoryModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_categories.count();
}

QVariant CategoryModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_categories.count()) {
    return QVariant();
  }

  const CategoryItem &item = m_categories.at(index.row());

  if (role == NameRole) {
    return item.categoryName;
  } else if (role == IconRole) {
    return item.iconName;
  }

  return QVariant();
}

QHash<int, QByteArray> CategoryModel::roleNames() const {
  QHash<int, QByteArray> roles;

  roles[NameRole] = "categoryName";
  roles[IconRole] = "iconName";
  return roles;
}

void CategoryModel::setCategories(const QList<CategoryItem> &categories) {
  beginResetModel();
  m_categories = categories;
  endResetModel();
}

QList<CategoryModel::CategoryItem> CategoryModel::getCategories() const {
  return m_categories;
}

QmlHandler::QmlHandler(NetworkClient *client, QObject *parent)
    : QObject(parent),
      networkClient(client),
      m_categoryModel(new CategoryModel(this)) {}

void QmlHandler::fetchCategories() {
  networkClient->sendRequest("http://localhost:8080/categories");
}

CategoryModel *QmlHandler::categoryModel() const { return m_categoryModel; }

void QmlHandler::handleCategoryName(const QString &categoryName,
                                    const QString &iconName) {
  qDebug() << "handleCategoryName triggered";

  QList<CategoryModel::CategoryItem> categories =
      m_categoryModel->getCategories();

  categories.append({categoryName, iconName});
  m_categoryModel->setCategories(categories);
  emit categoryModelChanged();
}

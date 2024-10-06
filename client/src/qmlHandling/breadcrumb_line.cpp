#include "qmlHandling/breadcrumb_line.h"

BreadCrumb::BreadCrumb(QObject *parent) : QObject(parent) {}

QString BreadCrumb::breadCrumbRow() { return m_breadCrumbRow; }

void BreadCrumb::updateBreadCrumb(const QString &category,
                                  const QString &nationality,
                                  const QString &dishName) {
  if (!category.isEmpty() && nationality.isEmpty() && dishName.isEmpty()) {
    m_breadCrumbRow = category;
  } else if (!category.isEmpty() && !nationality.isEmpty() &&
             dishName.isEmpty()) {
    m_breadCrumbRow = category + " / " + nationality;
  } else if (!category.isEmpty() && !nationality.isEmpty() &&
             !dishName.isEmpty()) {
    m_breadCrumbRow = category + " / " + nationality + " / " + dishName;
  }
  emit breadCrumbRowChanged();
}

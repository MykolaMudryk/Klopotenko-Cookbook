#ifndef BREADCRUMB_LINE_H
#define BREADCRUMB_LINE_H

#include <QObject>
#include <QString>

class BreadCrumb : public QObject {
  Q_OBJECT
  Q_PROPERTY(
      QString breadCrumbRow READ breadCrumbRow NOTIFY breadCrumbRowChanged)

 public:
  explicit BreadCrumb(QObject *parent = nullptr);

  QString breadCrumbRow();

  Q_INVOKABLE void updateBreadCrumb(const QString &category,
                                    const QString &nationality = "",
                                    const QString &dishName = "");

 signals:
  void breadCrumbRowChanged();

 private:
  QString m_breadCrumbRow;
};

#endif  // BREADCRUMB_LINE_H

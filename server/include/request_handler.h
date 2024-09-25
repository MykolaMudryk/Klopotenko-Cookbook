#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <QObject>

#include "database_handler.h"

class RequestHandler : public QObject {
  Q_OBJECT
 private:
  DatabaseHandler dbHandler;

 public:
  explicit RequestHandler(QObject* parent = nullptr);

  QString getCategories();
};

#endif  // REQUEST_HANDLER_H

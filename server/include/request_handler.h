#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "database_handler.h"

class RequestHandler : public QObject {
  Q_OBJECT
 private:
  DatabaseHandler dbHandler;

 public:
  explicit RequestHandler(QObject* parent = nullptr);

  QString handleGetRequest();
};

#endif  // REQUEST_HANDLER_H

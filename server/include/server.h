#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "request_handler.h"

class Server : public QObject {
  Q_OBJECT
 private:
  RequestHandler requestHandler;
  QTcpServer* tcpServer;

  int port;

 public:
  explicit Server(QObject* parent = nullptr);

  void startServer();
 public slots:
  void incomingConnection();
};

#endif  // SERVER_H

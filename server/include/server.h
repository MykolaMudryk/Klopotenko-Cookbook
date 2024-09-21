#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>

#include "request_handler.h"

class Server : public QObject {
  Q_OBJECT
 private:
  RequestHandler requestHandler;
  QWebSocketServer* webSocketServer;
  QList<QWebSocket*> clients;

  int port;

 public:
  explicit Server(QObject* parent = nullptr);

  void startServer();
 public slots:
  void onIncomingConnection();
  void handleGetRequest(const QString& getMessage);
  void onSocketDisconnected();
};

#endif  // SERVER_H

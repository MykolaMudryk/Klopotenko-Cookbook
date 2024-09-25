#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QWebSocket>
#include <QWebSocketServer>

#include "request_handler.h"
#include "server_json_parser.h"

class Server : public QObject {
  Q_OBJECT
 private:
  RequestHandler requestHandler;
  ServerJsonParser* jsonParser;

  QWebSocketServer* webSocketServer;
  QList<QWebSocket*> clients;

  int port;

 public:
  explicit Server(QObject* parent = nullptr);

  void startServer();
 public slots:
  void onIncomingConnection();
  void onSocketDisconnected();
  void getCategories(const QString& getMessage);
  void getNationalities(const QByteArray& hoveredCategoryError);
};

#endif  // SERVER_H

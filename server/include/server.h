#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QWebSocket>
#include <QWebSocketServer>

#include "server_json_parser.h"

class SendDataToClient : public QObject {
  Q_OBJECT
 private:
  ServerJsonParser* jsonParser;

  QWebSocketServer* webSocketServer;
  QList<QWebSocket*> clients;

  int port;

 public:
  explicit SendDataToClient(QObject* parent = nullptr);

  void startServer();
 public slots:
  void onIncomingConnection();
  void onSocketDisconnected();
  void getCategories(const QString& getMessage);
  void getNationalities(const QByteArray& hoveredCategoryError);
};

#endif  // SERVER_H

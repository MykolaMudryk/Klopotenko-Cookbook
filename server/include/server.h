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
  ParseClientData jsonParser;

  QWebSocketServer* webSocketServer;
  QList<QWebSocket*> clients;

  int port;

 public:
  explicit SendDataToClient(QObject* parent = nullptr);

  void startServer();
 public slots:
  void onIncomingConnection();
  void onSocketDisconnected();

  void onSendCategory(const QString& categoryDatabase);
  void onSendNationality(const QString& categoryClient);
  void onSendDishName(const QString& hoveredData);
};

#endif  // SERVER_H

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
  ParseClientData* jsonParser;

  QWebSocketServer* webSocketServer;
  QList<QWebSocket*> clients;

  int port;

 public:
  explicit SendDataToClient(QObject* parent = nullptr);

  void startServer();
 public slots:
  void onIncomingConnection();

  void onSocketDisconnected();
  void onSendCategory(const QByteArray& category);
  void onSendNationality(const QByteArray& nationality);
};

class SendErrorToclient : public QObject {
  Q_OBJECT
 private:
  QWebSocketServer* webSocketServer;
  QList<QWebSocket*> clients;

  ParseClientData* jsonParser;

  int port;

 public:
  explicit SendErrorToclient(QObject* parent = nullptr);

 public slots:
  void onConnectClientRequestError();
  void sendCategoryError(const QByteArray& category);
  void sendHoveredCategoryError(const QByteArray& hoveredCategoryError);
};

#endif  // SERVER_H

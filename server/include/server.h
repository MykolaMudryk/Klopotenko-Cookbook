#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QWebSocket>
#include <QWebSocketServer>

#include "server_json_parser.h"

class SendForDropdown : public QObject {
  Q_OBJECT
 private:
  QWebSocketServer* webSocketServer;
  ParseClientData jsonParser;

  QMap<QString, QWebSocket*> clientSockets;

 public:
  explicit SendForDropdown(QObject* parent = nullptr);

 public slots:

  void onSendCategory(QWebSocket* clientSocket, const QString& clientId,
                      const QString& categoryDatabase);
  void onSendNationality(QWebSocket* clientSocket, const QString& clientId,
                         const QString& categoryClient);
  void onSendDishName(QWebSocket* clientSocket, const QString& clientId,
                      const QString& hoveredData);
};

class ServerConnection : public QObject {
  Q_OBJECT
 private:
  QWebSocketServer* webSocketServer;

  QMap<QString, QWebSocket*> clients;

  SendForDropdown* sendForDropdown;

  QHash<QString, std::function<void(const QString& clientId, const QString&)>>
      requestHandlers;

  int port;

 public:
  explicit ServerConnection(QObject* parent = nullptr);

  void startServer();

  void registerRequestHandlers();

 public slots:
  void onIncomingConnection();
  void onSocketDisconnected();

  void onRequestReceived(const QString& request);
 signals:
  void sendCategory(QWebSocket* clientSocket, const QString& clientId,
                    const QString data);
  void sendNationality(QWebSocket* clientSocket, const QString& clientId,
                       const QString data);
  void sendDishName(QWebSocket* clientSocket, const QString& clientId,
                    const QString data);
};

#endif  // SERVER_H

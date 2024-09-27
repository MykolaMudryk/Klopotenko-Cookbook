#include "server.h"
SendDataToClient::SendDataToClient(QObject *parent)
    : QObject(parent),
      webSocketServer(new QWebSocketServer(QStringLiteral("WebSocket Server"),
                                           QWebSocketServer::NonSecureMode,
                                           this)),
      jsonParser(this) {}

void SendDataToClient::startServer() {
  port = 8080;

  if (!webSocketServer->listen(QHostAddress::LocalHost, port)) {
    qDebug() << "Failed to start the server: "
             << webSocketServer->errorString();
  } else {
    qDebug() << "WebSocket server started on port: " << port;
    connect(webSocketServer, &QWebSocketServer::newConnection, this,
            &SendDataToClient::onIncomingConnection);
  }
}

void SendDataToClient::onIncomingConnection() {
  while (webSocketServer->hasPendingConnections()) {
    QWebSocket *clientSocket = webSocketServer->nextPendingConnection();

    connect(clientSocket, &QWebSocket::disconnected, this,
            &SendDataToClient::onSocketDisconnected);

    connect(clientSocket, &QWebSocket::textMessageReceived, this,
            &SendDataToClient::onSendCategory);

    connect(clientSocket, &QWebSocket::textMessageReceived, this,
            &SendDataToClient::onSendNationality);
  }
}

void SendDataToClient::onSocketDisconnected() {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());
  if (clientSocket) {
    clients.removeAll(clientSocket);
    clientSocket->deleteLater();
  }
}

void SendDataToClient::onSendCategory(const QString &categoryDatabase) {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());

  if (!clientSocket) {
    qWarning() << "Client socket is null, cannot send message.";
    return;
  }

  QByteArray parsedCategory = jsonParser.extractCategory(categoryDatabase);

  // qDebug() << "Sending JSON category:" << QString::fromUtf8(parsedCategory);

  clientSocket->sendTextMessage(QString::fromUtf8(parsedCategory));
}

void SendDataToClient::onSendNationality(const QString &categoryClient) {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());

  if (!clientSocket) {
    qWarning() << "Client socket is null, cannot send message.";
    return;
  }

  QByteArray parsedHoveredCategory =
      jsonParser.extractHoveredCategory(categoryClient);

  qDebug() << "Sending JSON hovered category:"
           << QString::fromUtf8(parsedHoveredCategory);

  clientSocket->sendTextMessage(QString::fromUtf8(parsedHoveredCategory));
}

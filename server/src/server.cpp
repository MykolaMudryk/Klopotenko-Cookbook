#include "server.h"
SendDataToClient::SendDataToClient(QObject *parent)
    : QObject(parent),
      webSocketServer(new QWebSocketServer(QStringLiteral("WebSocket Server"),
                                           QWebSocketServer::NonSecureMode,
                                           this)),
      jsonParser(new ParseClientData(this)) {}

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

    connect(clientSocket, &QWebSocket::textMessageReceived, this,
            &SendDataToClient::onSendCategory);
    connect(clientSocket, &QWebSocket::textMessageReceived, jsonParser,
            &ParseClientData::extractHoveredCategory);
  }
}

void SendDataToClient::onSocketDisconnected() {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());
  if (clientSocket) {
    clients.removeAll(clientSocket);
    clientSocket->deleteLater();
  }
}

void SendDataToClient::onSendCategory(const QByteArray &category) {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());
  if (getMessage == "GET_CATEGORIES") {
    QString response = requestHandler.getCategories();
    QByteArray jsonResponse = response.toUtf8();

    clientSocket->sendTextMessage(QString::fromUtf8(jsonResponse));
  } else {
    clientSocket->sendTextMessage("Unknown request");
  }
}

void SendDataToClient::onSendNationality(const QByteArray &nationality) {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());

  QString response = databaseHandler.getNationality();

  QByteArray jsonResponse = response.toUtf8();

  clientSocket->sendTextMessage(QString::fromUtf8(jsonResponse));
}

SendErrorToclient::SendErrorToclient(QObject *parent)
    : QObject(parent),
      webSocketServer(new QWebSocketServer(QStringLiteral("WebSocket Server"),
                                           QWebSocketServer::NonSecureMode,
                                           this)),
      jsonParser(new ParseClientData(this)) {}

void SendErrorToclient::onConnectClientRequestError() {
  connect(jsonParser, &ParseClientData::hoveredCategoryError, this,
          &SendErrorToclient::sendHoveredCategoryError);
}

void SendErrorToclient::sendCategoryError(const QByteArray &category) {}

void SendErrorToclient::sendHoveredCategoryError(
    const QByteArray &hoveredCategoryError) {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());

  clientSocket->sendTextMessage(QString::fromUtf8(hoveredCategoryError));
}

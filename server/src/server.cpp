#include "server.h"

Server::Server(QObject *parent)
    : QObject(parent),
      requestHandler(this),
      webSocketServer(new QWebSocketServer(QStringLiteral("WebSocket Server"),
                                           QWebSocketServer::NonSecureMode,
                                           this)) {}

void Server::startServer() {
  port = 8080;

  if (!webSocketServer->listen(QHostAddress::LocalHost, port)) {
    qDebug() << "Failed to start the server: "
             << webSocketServer->errorString();
  } else {
    qDebug() << "WebSocket server started on port: " << port;
    connect(webSocketServer, &QWebSocketServer::newConnection, this,
            &Server::onIncomingConnection);
  }
}

void Server::onIncomingConnection() {
  while (webSocketServer->hasPendingConnections()) {
    QWebSocket *clientSocket = webSocketServer->nextPendingConnection();

    connect(clientSocket, &QWebSocket::textMessageReceived, this,
            &Server::handleGetRequest);
  }
}

void Server::handleGetRequest(const QString &getMessage) {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());
  if (getMessage == "GET_CATEGORIES") {
    QString response = requestHandler.handleGetRequest();
    QByteArray jsonResponse = response.toUtf8();

    qDebug() << "Received getMessage on server:" << getMessage;

    clientSocket->sendTextMessage(QString::fromUtf8(jsonResponse));
  } else {
    clientSocket->sendTextMessage("Unknown request");
  }
}

void Server::onSocketDisconnected() {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());
  if (clientSocket) {
    clients.removeAll(clientSocket);
    clientSocket->deleteLater();
  }
}

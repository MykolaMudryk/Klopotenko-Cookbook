#include "server.h"
Server::Server(QObject *parent)
    : QObject(parent),
      requestHandler(this),
      webSocketServer(new QWebSocketServer(QStringLiteral("WebSocket Server"),
                                           QWebSocketServer::NonSecureMode,
                                           this)),
      jsonParser(new ServerJsonParser(this)) {}

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
            &Server::getCategories);
    connect(clientSocket, &QWebSocket::textMessageReceived, jsonParser,
            &ServerJsonParser::extractCategory);
    connect(jsonParser, &ServerJsonParser::hoveredCategoryError, this,
            &Server::getNationalities);
  }
}

void Server::getCategories(const QString &getMessage) {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());
  if (getMessage == "GET_CATEGORIES") {
    QString response = requestHandler.getCategories();
    QByteArray jsonResponse = response.toUtf8();

    qDebug() << "Received getCategories on server:" << getMessage;

    clientSocket->sendTextMessage(QString::fromUtf8(jsonResponse));
  } else {
    clientSocket->sendTextMessage("Unknown request");
  }
}

void Server::getNationalities(const QByteArray &hoveredCategoryError) {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());

  if (!hoveredCategoryError.isEmpty()) {
    clientSocket->sendTextMessage(QString::fromUtf8(hoveredCategoryError));
    return;
  }

  QString response = requestHandler.getNationality();

  QByteArray jsonResponse = response.toUtf8();

  clientSocket->sendTextMessage(QString::fromUtf8(jsonResponse));
}

void Server::onSocketDisconnected() {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());
  if (clientSocket) {
    clients.removeAll(clientSocket);
    clientSocket->deleteLater();
  }
}

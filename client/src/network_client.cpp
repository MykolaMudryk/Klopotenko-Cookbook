#include "network_client.h"

NetworkClient::NetworkClient(QObject *parent)
    : QObject(parent),
      websocket(
          new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, this)) {
  connect(websocket, &QWebSocket::connected, this, &NetworkClient::onConnected);
  connect(websocket, &QWebSocket::textMessageReceived, this,
          &NetworkClient::onTextMessageReceived);
  connect(websocket, &QWebSocket::errorOccurred, this, &NetworkClient::onError);
}

void NetworkClient::connectToServer() {
  websocket->open(QUrl("ws://localhost:8080/"));
  qDebug() << "Client opened connection";
}

void NetworkClient::onConnected() { qDebug() << "Connected to the server"; }

void NetworkClient::sendMessage(const QString &message) {
  if (websocket->isValid()) {
    websocket->sendTextMessage(message);
  } else {
    emit errorOccurred("Websocket isn't open");
  }
}

void NetworkClient::onTextMessageReceived(const QString &message) {
  QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());

  qDebug() << "Received message on client:" << message;

  if (jsonDoc.isNull()) {
    qWarning() << "Received JSON is null.";
    return;
  } else if (!jsonDoc.isObject() && !jsonDoc.isArray()) {
    qWarning() << "Received JSON is not an object nor array";

  } else {
    if (jsonDoc.isArray() && jsonDoc.array().isEmpty()) {
      qWarning() << "Received empty array.";
    } else {
      qDebug() << "Received data is correct";
      emit requestFinished(message.toUtf8());
    }
  }
}

void NetworkClient::onError(QAbstractSocket::SocketError error) {
  qWarning() << websocket->errorString();
  qWarning() << "WebSocket error:" << error << websocket->errorString();
}

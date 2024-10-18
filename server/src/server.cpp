#include "server.h"
ServerConnection::ServerConnection(QObject *parent)
    : QObject(parent),
      webSocketServer(new QWebSocketServer(QStringLiteral("WebSocket Server"),
                                           QWebSocketServer::NonSecureMode,
                                           this)) {
  sendForDropdown = new SendForDropdown(this);
  sendForFilter = new SendForFilter(this);
  registerRequestHandlers();
  onIncomingConnection();
}

void ServerConnection::startServer() {
  port = 8080;

  if (!webSocketServer->listen(QHostAddress::LocalHost, port)) {
    qDebug() << "Failed to start the server: "
             << webSocketServer->errorString();
  } else {
    qDebug() << "WebSocket server started on port: " << port;
    connect(webSocketServer, &QWebSocketServer::newConnection, this,
            &ServerConnection::onIncomingConnection);
  }
}

void ServerConnection::onIncomingConnection() {
  while (webSocketServer->hasPendingConnections()) {
    QWebSocket *clientSocket = webSocketServer->nextPendingConnection();

    QString clientIp = clientSocket->peerAddress().toString();
    quint16 clientPort = clientSocket->peerPort();

    QString clientId = QString("%1:%2").arg(clientIp).arg(clientPort);

    clients[clientId] = clientSocket;

    qDebug() << "New client socket saved with clientId:" << clientId
             << "socket address:" << clients[clientId];

    connect(clientSocket, &QWebSocket::textMessageReceived, this,
            &ServerConnection::onRequestReceived);

    connect(clientSocket, &QWebSocket::disconnected, this,
            &ServerConnection::onSocketDisconnected);
  }
}

void ServerConnection::registerRequestHandlers() {
  connect(this, &ServerConnection::sendCategory, sendForDropdown,
          &SendForDropdown::onSendCategory);
  connect(this, &ServerConnection::sendNationality, sendForDropdown,
          &SendForDropdown::onSendNationality);
  connect(this, &ServerConnection::sendDishName, sendForDropdown,
          &SendForDropdown::onSendDishName);

  connect(this, &ServerConnection::sendAllCategory, sendForFilter,
          &SendForFilter::onSendAllCategory);
  connect(this, &ServerConnection::sendAllNationality, sendForFilter,
          &SendForFilter::onSendAllNationality);
  connect(this, &ServerConnection::sendAllDishName, sendForFilter,
          &SendForFilter::onSendAllDishName);

  requestHandlers["GET_CATEGORIES"] = [this](const QString &clientId,
                                             const QString &request) {
    QWebSocket *clientSocket = clients[clientId];
    emit sendCategory(clientSocket, clientId);
  };

  requestHandlers["GET_NATIONALITY"] = [this](const QString &clientId,
                                              const QString &request) {
    QWebSocket *clientSocket = clients[clientId];
    emit sendNationality(clientSocket, clientId, request);
  };

  requestHandlers["HOVERED_CATEGORY"] = [this](const QString &clientId,
                                               const QString &request) {
    QWebSocket *clientSocket = clients[clientId];
    emit sendDishName(clientSocket, clientId, request);
  };

  requestHandlers["GET_FILTER_CATEGORIES"] = [this](const QString &clientId,
                                                    const QString &request) {
    QWebSocket *clientSocket = clients[clientId];
    emit sendAllCategory(clientSocket, clientId);
  };

  requestHandlers["GET_FILTER_NATIONALITY"] = [this](const QString &clientId,
                                                     const QString &request) {
    QWebSocket *clientSocket = clients[clientId];
    emit sendAllNationality(clientSocket, clientId);
  };

  requestHandlers["GET_FILTER_DISHNAME"] = [this](const QString &clientId,
                                                  const QString &request) {
    QWebSocket *clientSocket = clients[clientId];
    emit sendAllDishName(clientSocket, clientId);
  };
}

void ServerConnection::onRequestReceived(const QString &request) {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());

  if (clientSocket) {
    QString clientId;
    for (auto it = clients.begin(); it != clients.end(); ++it) {
      if (it.value() == clientSocket) {
        clientId = it.key();

        break;
      }
    }

    QString qHashKey = request.section(' ', 0, 0);

    if (requestHandlers.contains(qHashKey)) {
      requestHandlers[qHashKey](
          clientId, request);  // call signal handler registerRequestHandlers()
    } else {
      qWarning() << "Request handler not found or clientId is empty."
                 << "request:" << request << "clientId:" << clientId;
    }
  }
}

void ServerConnection::onSocketDisconnected() {
  QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());

  if (clientSocket) {
    QString clientId;
    for (auto it = clients.begin(); it != clients.end(); ++it) {
      if (it.value() == clientSocket) {
        clientId = it.key();
        break;
      }
    }

    if (!clientId.isEmpty()) {
      clients.remove(clientId);
      clientSocket->deleteLater();
      qDebug() << "Client disconnected with ID:" << clientId;
    }
  }
}

SendForDropdown::SendForDropdown(QObject *parent) : QObject(parent) {}

void SendForDropdown::onSendCategory(QWebSocket *clientSocket,
                                     const QString &clientId) {
  if (!clientSocket) {
    qWarning() << "Client socket is null, cannot send message.";
    return;
  }

  QByteArray parsedCategory = jsonParser.extractCategory();

  clientSocket->sendTextMessage(QString::fromUtf8(parsedCategory));
}

void SendForDropdown::onSendNationality(QWebSocket *clientSocket,
                                        const QString &clientId,
                                        const QString &categoryClient) {
  if (!clientSocket) {
    qWarning() << "Client socket is null, cannot send message.";
    return;
  }

  QByteArray parsedHoveredCategory =
      jsonParser.extractHoveredCategory(categoryClient);

  clientSocket->sendTextMessage(QString::fromUtf8(parsedHoveredCategory));
}

void SendForDropdown::onSendDishName(QWebSocket *clientSocket,
                                     const QString &clientId,
                                     const QString &hoveredData) {
  if (!clientSocket) {
    qWarning() << "Client socket is null, cannot send message.";
    return;
  }

  QByteArray parsedDishName = jsonParser.extractDishName(hoveredData);

  clientSocket->sendTextMessage(QString::fromUtf8(parsedDishName));
}

SendForFilter::SendForFilter(QObject *parent) {}

void SendForFilter::onSendAllCategory(QWebSocket *clientSocket,
                                      const QString &clientId) {
  if (!clientSocket) {
    qWarning() << "Client socket is null, cannot send message.";
    return;
  }

  QByteArray parsedAllcategories = jsonParser.allCategoryResponse();

  clientSocket->sendTextMessage(QString::fromUtf8(parsedAllcategories));
}

void SendForFilter::onSendAllNationality(QWebSocket *clientSocket,
                                         const QString &clientId) {
  if (!clientSocket) {
    qWarning() << "Client socket is null, cannot send message.";
    return;
  }

  QByteArray parsedAllNations = jsonParser.allNationResponse();

  clientSocket->sendTextMessage(QString::fromUtf8(parsedAllNations));
}

void SendForFilter::onSendAllDishName(QWebSocket *clientSocket,
                                      const QString &clientId) {
  if (!clientSocket) {
    qWarning() << "Client socket is null, cannot send message.";
    return;
  }

  QByteArray parsedAllDishes = jsonParser.allDishResponse();

  clientSocket->sendTextMessage(QString::fromUtf8(parsedAllDishes));
}

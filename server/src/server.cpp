#include "server.h"

Server::Server(QObject *parent)
    : QObject(parent), requestHandler(this), tcpServer(new QTcpServer(this)) {
  connect(tcpServer, &QTcpServer::newConnection, this,
          &Server::incomingConnection);
}

void Server::startServer() {
  port = 8080;

  if (!tcpServer->listen(QHostAddress::LocalHost, port)) {
    qDebug() << "Failed to start the server: " << tcpServer->errorString();
  } else {
    qDebug() << "Server started on port: " << port;
  }
}

void Server::incomingConnection() {
  while (tcpServer->hasPendingConnections()) {
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();

    connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {
      QByteArray request = clientSocket->readAll();

      QList<QByteArray> requestLines = request.split('\n');
      if (requestLines.isEmpty()) {
        clientSocket->disconnectFromHost();
        clientSocket->deleteLater();
        return;
      }

      QList<QByteArray> requestLine = requestLines[0].split(' ');
      if (requestLine.size() != 3) {
        clientSocket->disconnectFromHost();
        clientSocket->deleteLater();
        return;
      }

      QByteArray method = requestLine[0];
      QByteArray path = requestLine[1];

      if (method == "GET" && path == "/categories") {
        QString response = requestHandler.handleGetRequest();
        QByteArray httpResponse;

        qDebug() << "Method:" << method << "Path:" << path;

        httpResponse.append("HTTP/1.1 200 OK\r\n");
        httpResponse.append("Content-Type: application/json\r\n");
        httpResponse.append("Access-Control-Allow-Origin: *\r\n");
        httpResponse.append(
            "Content-Length: " + QByteArray::number(response.toUtf8().size()) +
            "\r\n");
        httpResponse.append("\r\n");
        httpResponse.append(response.toUtf8());

        clientSocket->write(httpResponse);
        clientSocket->flush();

      } else {
        QByteArray httpResponse = "HTTP/1.1 404 Not Found\r\n\r\n";
        clientSocket->write(httpResponse);
        clientSocket->flush();
      }

      clientSocket->disconnectFromHost();
      clientSocket->deleteLater();
    });
  }
}

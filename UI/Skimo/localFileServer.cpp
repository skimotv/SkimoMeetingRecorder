#include "Skimo/localFileServer.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

//! [constructor]
FileServer::FileServer(quint16 port, bool debug, QObject *parent)
	: QObject(parent),
	  m_pWebSocketServer(
		  new QWebSocketServer(QStringLiteral("Echo Server"),
				       QWebSocketServer::NonSecureMode, this)),
	  m_debug(debug)
{
	if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
		if (m_debug)
			qDebug() << "FileServer listening on port" << port;
		connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
			this, &FileServer::onNewConnection);
		connect(m_pWebSocketServer, &QWebSocketServer::closed, this,
			&FileServer::closed);
	}
}
//! [constructor]

FileServer::~FileServer()
{
	m_pWebSocketServer->close();
	qDeleteAll(m_clients.begin(), m_clients.end());
}

//! [onNewConnection]
void FileServer::onNewConnection()
{
	QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

	connect(pSocket, &QWebSocket::textMessageReceived, this,
		&FileServer::processTextMessage);
	connect(pSocket, &QWebSocket::binaryMessageReceived, this,
		&FileServer::processBinaryMessage);
	connect(pSocket, &QWebSocket::disconnected, this,
		&FileServer::socketDisconnected);

	m_clients << pSocket;
}
//! [onNewConnection]

//! [processTextMessage]
void FileServer::processTextMessage(QString message)
{
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (m_debug)
		qDebug() << "Message received:" << message;
	if (pClient) {
		pClient->sendTextMessage(message);
	}
}
//! [processTextMessage]

//! [processBinaryMessage]
void FileServer::processBinaryMessage(QByteArray message)
{
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (m_debug)
		qDebug() << "Binary Message received:" << message;
	if (pClient) {
		pClient->sendBinaryMessage(message);
	}
}
//! [processBinaryMessage]

//! [socketDisconnected]
void FileServer::socketDisconnected()
{
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (m_debug)
		qDebug() << "socketDisconnected:" << pClient;
	if (pClient) {
		m_clients.removeAll(pClient);
		pClient->deleteLater();
	}
}

void FileServer::setOpenDirectory(QString newDir) {
	openDirectory = newDir;
}

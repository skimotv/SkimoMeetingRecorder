#include "Skimo/localFileServer.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


QT_USE_NAMESPACE

//! [constructor]
FileServer::FileServer(quint16 port, bool debug, QObject *parent)
	: QObject(parent),
	  m_pWebSocketServer(
		  new QWebSocketServer(QStringLiteral("Web Server"),
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
		&FileServer::processMessage);
	connect(pSocket, &QWebSocket::binaryMessageReceived, this,
		&FileServer::processMessage);
	connect(pSocket, &QWebSocket::disconnected, this,
		&FileServer::socketDisconnected);

	m_clients << pSocket;
}
//! [onNewConnection]

//! [processTextMessage]
void FileServer::processMessage(QString message)
{
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (m_debug)
		qDebug() << "Message received:" << message;
	int j, file_fd, buflen;
	long i, ret, len, fd;
	char * fstr;
	static char buffer[8096+1];

	struct
	{
		char *ext;
		char *filetype;
	} extensions [] = {
		{"gif", "image/gif" },
		{"jpg", "image/jpg" },
		{"jpeg","image/jpeg"},
		{"png", "image/png" },
		{"ico", "image/ico" },
		{"zip", "image/zip" },
		{"gz",  "image/gz"  },
		{"tar", "image/tar" },
		{"htm", "text/html" },
		{"html","text/html" },
		{"css","text/css" },
		{"js","text/js" },
		{"txt","text/txt" },
		{"sub","text/sub" },
		{"mp4","video/mp4" },
		{0,0} };

	chdir("/Users/vasusrinivasan/Movies");	
	QString qstr = message.left(8096);
	strcpy(buffer, qstr.toStdString().c_str());
	int length = strlen(buffer);

	if(length > 0 && length < 8096)
		buffer[length]=0;
	else
		buffer[0]=0;

	for(i = 0; i < ret; i++)
		if(buffer[i] == '\r' || buffer[i] == '\n')
			buffer[i]='*';

	for(i = 4; i < 8096; i++)
	{
		if(buffer[i] == ' ')
		{
			buffer[i] = 0;
			break;
		}
	}

	buflen=strlen(buffer);
	fstr = (char *)0;
	for(i = 0; extensions[i].ext != 0; i++)
	{
		len = strlen(extensions[i].ext);
		if( !strncmp(&buffer[buflen-len], extensions[i].ext, len))
		{
			fstr =extensions[i].filetype;
			break;
		}
	}
	file_fd = open(&buffer[5],O_RDONLY);

	len = (long)lseek(file_fd, (off_t)0, SEEK_END);
	lseek(file_fd, (off_t)0, SEEK_SET);
	sprintf(buffer,"HTTP/1.1 200 OK\nServer: fileserver1.0\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n",len, fstr);
	write(fd,buffer,strlen(buffer));

	while (	(ret = read(file_fd, buffer, 8096)) > 0 )
	{
		write(fd,buffer,ret);
	}

	QString retQString = QString::fromStdString(buffer);

	if (pClient)
		pClient->sendTextMessage(retQString);
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

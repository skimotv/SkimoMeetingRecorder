#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class FileServer : public QObject {
	Q_OBJECT
public:
	explicit FileServer(quint16 port, bool debug = false,
			    QObject *parent = nullptr);
	void setOpenDirectory(QString dir);
	~FileServer();

Q_SIGNALS:
	void closed();

private Q_SLOTS:
	void onNewConnection();
	void processTextMessage(QString message);
	void processBinaryMessage(QByteArray message);
	void socketDisconnected();

private:
	QString openDirectory;

	QWebSocketServer *m_pWebSocketServer;
	QList<QWebSocket *> m_clients;
	bool m_debug;
};

#endif //ECHOSERVER_H

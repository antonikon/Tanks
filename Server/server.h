#pragma once

#include <QObject>
#include <QtNetwork>
#include <QtCore>

#include "../Proto/p.pb.h"
#include "player.h"
#include "world.h"

class Server : public QObject
{
	Q_OBJECT
public:
	explicit Server(QObject *parent = 0);
signals:
	
public slots:

private slots:
	void dataReceived();
	void playerConnectionLost();
	void sendData();
private:
	QUdpSocket *_socket = new QUdpSocket(this);
	QVector <Player*> _playerList;
	World *_world = new World;

};

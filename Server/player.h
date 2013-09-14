#pragma once

#include <QObject>
#include <QtNetwork>
#include <QtCore>
#include <QTimer>

#include "../Proto/p.pb.h"
#include "tank.h"

class Player : public QObject
{
	Q_OBJECT
public:
	Player(const QHostAddress &address = QHostAddress(), quint16 port = 0, const QString &name = "", Tank *tank = 0, QObject *parent = 0);
	QHostAddress getAddress() const {
		return _address;
	}
	quint16 getPort() const {
		return _port;
	}
	QString getName() const {
		return _name;
	}
	void update(const MClient &packet);
	void timerEvent(QTimerEvent *);
	Tank *tank() {
		return _tank;
	}

public:
	bool operator ==(const Player *player);
signals:
	void connectionLost();
public slots:
	
private:
	QHostAddress _address ;
	quint16 _port;
	QString _name;
	size_t _lastPacketTime = 0;
	Tank *_tank;

};

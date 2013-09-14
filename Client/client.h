#pragma once

#include <QObject>
#include <QtNetwork>
#include <QtCore>

#include "tank.h"
#include "../Proto/p.pb.h"
#include "buffer.h"
#include "wall.h"
#include "bullet.h"

class Client : public QObject
{
	Q_OBJECT
public:
	Client(QObject *parent = 0);
	~Client();
	void paintAll(QPainter *painter);
signals:
	void readyPaint();
private slots:
	void dataReceived();
	void createPacket(QVector <bool> keys, bool keyFire, bool keyShift);
private:
	void sendPacket(const MClient &packet);
private:
	QUdpSocket *_socket;
	QVector <Tank*> _tankList;
	QVector <Wall*> _wallList;
	QVector <Bullet*> _bulletList;
	Buffer *_buffer = new Buffer(this);
};

#include "client.h"

Client::Client(QObject *parent) :
	QObject(parent),
	_socket(new QUdpSocket(this))
{
	QFile file("config.txt");
	file.open(QFile::ReadOnly);
	QString ip = file.readAll();
	_socket->connectToHost(QHostAddress(ip),2000);
	connect(_socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
	MClient message;
	message.set_name("None");
	message.set_type(0);
	sendPacket(message);
}

Client::~Client()
{
	MClient message;
	message.set_type(1);
	sendPacket(message);
}

void Client::paintAll(QPainter *painter)
{
	for (size_t q = 0; q < _tankList.size(); q++) {
		_tankList[q]->paint(painter);
	}
	for (size_t q = 0; q < _wallList.size(); q++) {
		_wallList[q]->paint(painter);
	}
	for (size_t q = 0; q < _bulletList.size(); q++) {
		_bulletList[q]->paint(painter);
	}
}

void Client::dataReceived()
{
	QByteArray data = _socket->readAll();
	MServer server;
	server.ParseFromArray(data.data(),data.size());
	for (size_t q = 0; q <_tankList.size(); q++) {
		delete _tankList[q];
	}
	_tankList.clear();
	for (size_t q = 0; q <server.tankslist_size(); q++) {
		MTank info = server.tankslist(q);
		Tank *tank = new Tank(&info,_buffer,false,this);
		_tankList.append(tank);
	}
	MTank info = server.playertank();
	Tank *tank = new Tank(&info,_buffer,true,this);
	_tankList.append(tank);

	for (size_t q = 0; q <_wallList.size(); q++) {
		delete _wallList[q];
	}
	_wallList.clear();
	for (size_t q = 0; q <server.walllist_size(); q++) {
		MWall info = server.walllist(q);
		Wall *wall = new Wall(&info,_buffer,this);
		_wallList.append(wall);
	}
	for (size_t q = 0; q <_bulletList.size(); q++) {
		delete _bulletList[q];
	}
	_bulletList.clear();
	for (size_t q = 0; q <server.buleltlist_size(); q++) {
		MBullet info = server.buleltlist(q);
		Bullet *bullet = new Bullet(&info,_buffer,this);
		_bulletList.append(bullet);
	}
	emit readyPaint();
}

void Client::createPacket(QVector <bool> keys, bool keyFire, bool keyShift)
{
	MClient packet;
	packet.set_type(0);
	int key = keys.indexOf(true);
	packet.set_key(key);
	packet.set_keyfire(keyFire);
	packet.set_keyshift(keyShift);
	sendPacket(packet);

}

void Client::sendPacket(const MClient &packet)
{
	QByteArray data;
	data.resize(packet.ByteSize());
	packet.SerializeToArray(data.data(),packet.ByteSize());
	_socket->write(data);
}

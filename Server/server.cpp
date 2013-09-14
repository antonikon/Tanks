#include "server.h"

Server::Server(QObject *parent) :
	QObject(parent)
{
	_socket->bind(QHostAddress::Any,2000);
	connect(_socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
	connect(_world, SIGNAL(readySendData()), this, SLOT(sendData()));
}

void Server::dataReceived()
{
	QByteArray data;
	quint64 maxlen = 2000;
	QHostAddress address;
	quint16 port;

	data.resize(_socket->pendingDatagramSize());
	_socket->readDatagram(data.data(),maxlen,&address,&port);
	MClient message;
	message.ParseFromArray(data.data(),data.size());

	int index = -1;
	for (size_t q = 0; q < _playerList.size(); q++) {
		if (_playerList[q]->getAddress() == address & _playerList[q]->getPort() == port) {
			index = q;
			break;
		}
	}
	if (index == -1) {
		Tank *tank = _world->spawnTank();
		Player *player = new Player(address, port, message.name().data(), tank, this);
		connect(player, SIGNAL(connectionLost()), this, SLOT(playerConnectionLost()));
		_playerList.append(player);
		qDebug() << QString("Player %1(%2:%3) connected")
					.arg(player->getName())
					.arg(player->getAddress().toString())
					.arg(player->getPort());
	} else
	{
		if (message.type() == 0) {
					_playerList[index]->update(message);
		} else if (message.type() == 1) {
			qDebug() << QString("Player %1(%2:%3) disconnected")
						.arg(_playerList[index]->getName())
						.arg(_playerList[index]->getAddress().toString())
						.arg(_playerList[index]->getPort());
			delete _playerList[index];
			_playerList.remove(index);
		}
	}
}

void Server::playerConnectionLost()
{
	Player *player = (Player*)sender();
	int index = _playerList.indexOf(player);
	qDebug() << QString("Player %1(%2:%3) connection lost")
				.arg(player->getName())
				.arg(player->getAddress().toString())
				.arg(player->getPort());
	delete player;
	_playerList.remove(index);
}

void Server::sendData()
{
	for (size_t q = 0; q < _playerList.size(); q++) {
		MServer packet = _world->createDataForPlayer(_playerList[q]);
		QByteArray data;
		data.resize(packet.ByteSize());
		packet.SerializeToArray(data.data(),packet.ByteSize());
		_socket->writeDatagram(data,_playerList[q]->getAddress(),_playerList[q]->getPort());
	}
}

#include "player.h"

Player::Player(const QHostAddress &address, quint16 port, const QString &name, Tank *tank, QObject *parent) :
	QObject(parent),
	_address(address),
	_port(port),
	_name(name),
	_tank(tank)
{
	startTimer(1000);
}

void Player::update(const MClient &packet)
{
	emit _tank->tryMove(packet.key(),packet.keyshift());
	if (packet.keyfire()) {
		emit _tank->fire();
	}
	_lastPacketTime = 0;
}

void Player::timerEvent(QTimerEvent *)
{
	if (_lastPacketTime >= 10) {
		emit connectionLost();
	}
	_lastPacketTime++;
}

bool Player::operator ==(const Player *player)
{
	return _address == player->getAddress() & _port == player->getPort() & _name == player->getName();
}

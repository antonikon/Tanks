#include "world.h"

World::World(QObject *parent) :
	QObject(parent)
{
	startTimer(30);
	spawnWall(QPoint(3,3));
	spawnWall(QPoint(4,3));
	spawnWall(QPoint(5,3));
	spawnWall(QPoint(6,3));
	spawnWall(QPoint(3,4));
	spawnWall(QPoint(6,4));
	spawnWall(QPoint(3,5));
	spawnWall(QPoint(6,5));
	spawnWall(QPoint(3,6));
	spawnWall(QPoint(4,6));
	spawnWall(QPoint(5,6));
	spawnWall(QPoint(6,6));
}

Tank *World::spawnTank()
{
	QPoint pos(rand()%10,rand()%10);
	Tank *tank = new Tank(pos,0,this);
	connect(tank, SIGNAL(tryMove(int,bool)), this, SLOT(tankMove(int,bool)));
	connect(tank, SIGNAL(fire()), this, SLOT(tankFire()));
	connect(tank, SIGNAL(destruction()), this, SLOT(tankDestruction()));
	_tankList.append(tank);
	return tank;
}

MServer World::createDataForPlayer(Player *player)
{
	MServer packet;
	for (size_t q = 0; q <_tankList.size(); q++) {
		MTank *tank = new MTank;
		tank->set_posx(_tankList[q]->getPosition().x());
		tank->set_posy(_tankList[q]->getPosition().y());
		tank->set_angle(_tankList[q]->getAngle());
		tank->set_type(_tankList[q]->getType());
		tank->set_team(_tankList[q]->getTeam());
		tank->set_animationprogress(_tankList[q]->getAnimationProgress());
		if (_tankList[q] == player->tank()) {
			packet.set_allocated_playertank(tank);
		} else {
			packet.add_tankslist()->CopyFrom(*tank);
		}
	}
	for (size_t q = 0; q <_wallList.size(); q++) {
		MWall wall;
		wall.set_posx(_wallList[q]->getPosition().x());
		wall.set_posy(_wallList[q]->getPosition().y());
		wall.set_type(_wallList[q]->getType());
		packet.add_walllist()->CopyFrom(wall);
	}
	for (size_t q = 0; q <_bulletList.size(); q++) {
		MBullet bullet;
		bullet.set_posx(_bulletList[q]->getPosition().x());
		bullet.set_posy(_bulletList[q]->getPosition().y());
		bullet.set_angle(_bulletList[q]->getAngle());
		bullet.set_animationprogress(_bulletList[q]->getAnimationProgress());
		packet.add_buleltlist()->CopyFrom(bullet);
	}
	return packet;
}

void World::spawnWall(const QPoint &pos, size_t type)
{
	Wall *wall = new Wall(pos,type);
	connect(wall, SIGNAL(destruction()), this, SLOT(wallDestruction()));
	_wallList.append(wall);
}

void World::spawnBullet(const QPoint &pos, size_t angle)
{
	Bullet *bullet = new Bullet(pos,angle,this);
	connect(bullet, SIGNAL(tryFly()), this, SLOT(bulletFly()));
	_bulletList.append(bullet);
}

void World::timerEvent(QTimerEvent *) {
	for (size_t q = 0; q <_tankList.size(); q++) {
		_tankList[q]->update();
	}
	for (size_t q = 0; q < _bulletList.size(); q++) {
		_bulletList[q]->update();
	}
	emit readySendData();
}

bool World::testForObject(const QPoint &pos, size_t testedAngle)
{
	if (pos.x() >= 0 & pos.x() < 10 & pos.y() >= 0 & pos.y() < 10) {
		for (size_t q = 0; q < _wallList.size(); q++) {
			if (_wallList[q]->getPosition() == pos) {
				return false;
			}
		}
		for (size_t q = 0; q < _tankList.size(); q++) {
			if (_tankList[q]->getPosition() == pos) {
				return false;
			} else if (_tankList[q]->getAnimationProgress() > 0){
				if (testedAngle == 0 || testedAngle == 2) {
					if (_tankList[q]->getPosition().y() == pos.y() & qAbs(_tankList[q]->getPosition().x() - pos.x()) == 1) {
						return false;
					}
				} else {
					if (_tankList[q]->getPosition().x() == pos.x() & qAbs(_tankList[q]->getPosition().y() - pos.y()) == 1) {
						return false;
					}
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

int World::findTank(const QPoint &pos)
{
	for (size_t q = 0; q < _tankList.size(); q++) {
		if (_tankList[q]->getPosition() == pos) {
			return q;
		}
	}
	return -1;
}

int World::findWall(const QPoint &pos)
{
	for (size_t q = 0; q < _wallList.size(); q++) {
		if (_wallList[q]->getPosition() == pos) {
			return q;
		}
	}
	return -1;
}

void World::deleteBullet(Bullet *bullet)
{
	int index = _bulletList.indexOf(bullet);
	delete bullet;
	_bulletList.remove(index);
}


void World::tankMove(int angle, bool keyShift)
{
	Tank *tank = (Tank*)sender();
	if (angle != -1 & tank->getAnimationProgress() == 0)
	{
		QPoint tankPos = tank->getPosition();
		switch (tank->getAngle()) {
			case 0:
			{
				switch (angle) {
					case 0:
					{
						if (testForObject(QPoint(tankPos.x(),tankPos.y()-1),angle) & !keyShift) {
							tank->move(angle);
						}
						break;
					}
					case 1:
					{
						tank->rotate(angle);
						break;
					}
					case 3:
					{
						tank->rotate(angle);
						break;
					}
				}
				break;
			}
			case 1:
			{
				switch (angle) {
					case 1:
					{
						if (testForObject(QPoint(tankPos.x() + 1,tankPos.y()),angle) & !keyShift) {
							tank->move(angle);
						}
						break;
					}
					case 0:
					{
						tank->rotate(angle);
						break;
					}
					case 2:
					{
						tank->rotate(angle);
						break;
					}
				}
				break;
			}
			case 2:
			{
				switch (angle) {
					case 2:
					{
						if (testForObject(QPoint(tankPos.x(),tankPos.y() + 1), angle) & !keyShift) {
							tank->move(angle);
						}
						break;
					}
					case 1:
					{
						tank->rotate(angle);
						break;
					}
					case 3:
					{
						tank->rotate(angle);
						break;
					}
				}
				break;
			}
			case 3:
			{
				switch (angle) {
					case 3:
					{
						if (testForObject(QPoint(tankPos.x() - 1,tankPos.y()), angle) & !keyShift) {
							tank->move(angle);
						}
						break;
					}
					case 0:
					{
						tank->rotate(angle);
						break;
					}
					case 2:
					{
						tank->rotate(angle);
						break;
					}
				}
				break;
			}
		}
	}
}

void World::tankFire()
{
	Tank *tank = (Tank*)sender();
	if (tank->getReload() == 0)
	{
		QPoint bulletPos;
		switch (tank->getAngle()) {
			case 0:
			{
				bulletPos = QPoint(tank->getPosition().x(),tank->getPosition().y() - 1);
				break;
			}
			case 1:
			{
				bulletPos = QPoint(tank->getPosition().x() + 1,tank->getPosition().y());
				break;
			}
			case 2:
			{
				bulletPos = QPoint(tank->getPosition().x(),tank->getPosition().y() + 1);
				break;
			}
			case 3:
			{
				bulletPos = QPoint(tank->getPosition().x() - 1,tank->getPosition().y());
				break;
			}

		}
		if (testForObject(bulletPos,tank->getAngle())) {
			spawnBullet(bulletPos,tank->getAngle());
		} else {
			int wallIndex = findWall(bulletPos);
			if (wallIndex != -1) {
				_wallList[wallIndex]->demage();
			} else {
				int tankIndex = findTank(bulletPos);
				if (tankIndex != -1) {
					_tankList[tankIndex]->demage();
				}
			}
		}
		tank->reloading();
	}
}

void World::tankDestruction()
{
	Tank *tank = (Tank*)sender();
	int index = _tankList.indexOf(tank);
	delete tank;
	_tankList.remove(index);
	tank = spawnTank();
}

void World::wallDestruction()
{
	Wall *wall = (Wall*)sender();
	int index = _wallList.indexOf(wall);
	delete wall;
	_wallList.remove(index);
}

void World::bulletFly()
{
	Bullet *bullet = (Bullet*)sender();
	QPoint bulletPos = bullet->getPosition();
	if (testForObject(bulletPos,bullet->getAngle())) {
		bullet->fly();
	} else {
		int wallIndex = findWall(bulletPos);
		if (wallIndex != -1) {
			_wallList[wallIndex]->demage();
			deleteBullet(bullet);
		} else {
			QPoint mod(0,1);
			if (bullet->getAngle() == 0 || bullet->getAngle() == 1) {
				mod = QPoint(1,0);
			}

			int tankIndex = findTank(bulletPos);
			if (tankIndex != -1) {
				_tankList[tankIndex]->demage();
				deleteBullet(bullet);
			} else {
				deleteBullet(bullet);
			}
		}
	}

}

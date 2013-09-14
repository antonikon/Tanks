#pragma once

#include <QObject>
#include <QtCore>
#include <QTimer>

#include "tank.h"
#include "../Proto/p.pb.h"
#include "player.h"
#include "wall.h"
#include "bullet.h"

class World : public QObject
{
	Q_OBJECT
public:
	explicit World(QObject *parent = 0);
	Tank *spawnTank();
	MServer createDataForPlayer(Player *player);
private:
	void spawnWall(const QPoint &pos, size_t type = 0);
	void spawnBullet(const QPoint &pos, size_t angle);
	void timerEvent(QTimerEvent *);
	bool testForObject(const QPoint &pos, size_t testedAngle);
	int findTank(const QPoint &pos);
	int findWall(const QPoint &pos);
	void deleteBullet(Bullet *bullet);
signals:
	void readySendData();
public slots:
	
private slots:
	void tankMove(int angle, bool keyShift);
	void tankFire();
	void tankDestruction();
	void wallDestruction();
	void bulletFly();
private:
	QVector <Tank*> _tankList;
	QVector <Wall*> _wallList;
	QVector <Bullet*> _bulletList;
	size_t _size = 10;
};

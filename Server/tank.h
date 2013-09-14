#pragma once

#include <QObject>
#include <QtCore>

class Tank : public QObject
{
	Q_OBJECT
public:
	explicit Tank(const QPoint &pos, size_t type, QObject *parent = 0);
	QPoint getPosition() {
		return _pos;
	}
	size_t getAngle() {
		return _angle;
	}
	size_t getType() {
		return _type;
	}
	size_t getTeam() {
		return _team;
	}
	size_t getAnimationProgress() {
		return _animationProgress;
	}
	size_t getReload() {
		return _reload;
	}
	void move(size_t dir);
	void reloading();
	void rotate(size_t angle);
	void update();
	void demage();
signals:
	void tryMove(int angle, bool keyShift);
	void fire();
	void destruction();
public slots:
	
private:
	size_t _type = 0, _angle = 0, _team = 0, _animationProgress = 0, _reload = 0, _hp = 1;
	QPoint _pos = QPoint(0,0);

};

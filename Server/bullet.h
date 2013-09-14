#pragma once

#include <QObject>
#include <QtCore>

class Bullet : public QObject
{
	Q_OBJECT
public:
	Bullet(const QPoint &pos, size_t angle, QObject *parent = 0);
	QPoint getPosition() {
		return _pos;
	}
	size_t getAngle() {
		return _angle;
	}
	size_t getAnimationProgress() {
		return _animationProgress;
	}
	void update();
	void fly();
signals:
	void tryFly();
public slots:
	
private:
	size_t  _angle = 0, _animationProgress = 15;
	QPoint _pos = QPoint(0,0);
};

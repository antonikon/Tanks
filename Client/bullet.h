#pragma once

#include <QObject>
#include <QtCore>
#include <QPainter>

#include "../Proto/p.pb.h"
#include "buffer.h"

class Bullet : public QObject
{
	Q_OBJECT
public:
	Bullet(MBullet *info, Buffer *buffer, QObject *parent = 0);
	QPoint getPosition() {
		return _pos;
	}
	size_t getAngle() {
		return _angle;
	}
	size_t getAnimationProgress() {
		return _animationProgress;
	}
	void paint(QPainter *painter);
public slots:

private:
	size_t  _angle = 0, _animationProgress = 15;
	QPoint _pos = QPoint(0,0);
	QImage *_image;
};

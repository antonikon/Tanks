#pragma once

#include <QObject>
#include <QtCore>
#include <QPainter>
#include <QImage>

#include "buffer.h"
#include "../Proto/p.pb.h"

class Tank : public QObject
{
	Q_OBJECT
public:
	explicit Tank(MTank *info, Buffer *buffer, bool isPlayer, QObject *parent = 0);
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
	void paint(QPainter *painter);
	void setIsPlayer(bool value) {
		_isPlayer = value;
	}
signals:

public slots:

private:
	QImage *_image;
	size_t _type = 0, _angle = 0, _team = 0, _animationProgress = 0;
	QPoint _pos = QPoint(0,0);
	bool _isPlayer = false;

};

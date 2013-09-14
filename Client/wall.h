#pragma once

#include <QObject>
#include <QtCore>
#include <QPainter>

#include "../Proto/p.pb.h"
#include "buffer.h"

class Wall : public QObject
{
	Q_OBJECT
public:
	Wall(MWall *info, Buffer *buffer, QObject *parent = 0);
	QPoint getPosition() {
		return _pos;
	}
	size_t getType() {
		return _type;
	}
	void paint(QPainter *painter);
signals:

public slots:

private:
	QPoint _pos;
	size_t _type = 0;
	QImage *_image;
};

#include "wall.h"

Wall::Wall(const QPoint &pos, size_t type, QObject *parent) :
	QObject(parent),
	_pos(pos)
{
}

void Wall::demage()
{
	_hp--;
	if (_hp == 0) {
		emit destruction();
	}
}

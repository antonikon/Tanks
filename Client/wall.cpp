#include "wall.h"

Wall::Wall(MWall *info, Buffer *buffer, QObject *parent) :
	QObject(parent),
	_pos(QPoint(info->posx(),info->posy())),
	_type(info->type()),
	_image(buffer->getWallImage(_type))
{
}

void Wall::paint(QPainter *painter)
{
	painter->drawImage(_pos.x() * 30, _pos.y() * 30,*_image);
}

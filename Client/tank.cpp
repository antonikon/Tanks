#include "tank.h"

Tank::Tank(MTank *info, Buffer *buffer, bool isPlayer, QObject *parent) :
	QObject(parent),
	_type(info->type()),
	_team(info->team()),
	_angle(info->angle()),
	_animationProgress(info->animationprogress()),
	_pos(QPoint(info->posx(),info->posy())),
	_isPlayer(isPlayer)
{
	if (_team == 0)
	{
		switch (_type) {
			case 0:
			{	if (!_isPlayer) {
					_image = buffer->getTankImage(0);
				} else {
					_image = buffer->getTankImage(1);
				}
				break;
			}
		}
	}
}

void Tank::paint(QPainter *painter)
{
	QTransform transform;
	transform.rotate(90 * _angle);
	QImage image = _image->transformed(transform);
	QPoint pos;
	switch (_angle) {
		case 0:
		{
			pos = QPoint(_pos.x() * 30,_pos.y() * 30 + _animationProgress * 2);
			break;
		}
		case 1:
		{
			pos = QPoint(_pos.x() * 30 - _animationProgress * 2, _pos.y() * 30);
			break;
		}
		case 2:
		{
			pos = QPoint(_pos.x() * 30,_pos.y() * 30 - _animationProgress * 2);
			break;
		}
		case 3:
		{
			pos = QPoint(_pos.x() * 30 + _animationProgress * 2, _pos.y() * 30);
			break;
		}
	}
	painter->drawImage(pos,image);
}

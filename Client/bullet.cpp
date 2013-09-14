#include "bullet.h"

Bullet::Bullet(MBullet *info, Buffer *buffer, QObject *parent) :
	QObject(parent),
	_pos(QPoint(info->posx(),info->posy())),
	_angle(info->angle()),
	_animationProgress(info->animationprogress()),
	_image(buffer->getBulletImage(0))
{
}

void Bullet::paint(QPainter *painter)
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

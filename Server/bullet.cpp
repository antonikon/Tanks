#include "bullet.h"

Bullet::Bullet(const QPoint &pos, size_t angle, QObject *parent) :
	QObject(parent),
	_pos(pos),
	_angle(angle)
{
}

void Bullet::update()
{
	_animationProgress-=2;
	if (_animationProgress <= -7) {
		emit tryFly();
	}
}

void Bullet::fly()
{
	_animationProgress = 7;
	switch (_angle) {
		case 0:
		{
			_pos = QPoint(_pos.x(), _pos.y() - 1);
			break;
		}
		case 1:
		{
			_pos = QPoint(_pos.x() + 1, _pos.y());
			break;
		}
		case 2:
		{
			_pos = QPoint(_pos.x(), _pos.y() + 1);
			break;
		}
		case 3:
		{
			_pos = QPoint(_pos.x() - 1, _pos.y());
			break;
		}
	}
}

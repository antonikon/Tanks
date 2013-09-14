#include "tank.h"

Tank::Tank(const QPoint &pos, size_t type, QObject *parent) :
	QObject(parent),
	_pos(pos),
	_type(type)
{
}

void Tank::move(size_t dir)
{
	switch (dir) {
		case 0:
		{
			_pos = QPoint(_pos.x(), _pos.y() - 1);
			_animationProgress = 15;
			break;
		}
		case 1:
		{
			_pos = QPoint(_pos.x() + 1, _pos.y());
			_animationProgress = 15;
			break;
		}
		case 2:
		{
			_pos = QPoint(_pos.x(), _pos.y() + 1);
			_animationProgress = 15;
			break;
		}
		case 3:
		{
			_pos = QPoint(_pos.x() - 1, _pos.y());
			_animationProgress = 15;
			break;
		}
	}
}

void Tank::reloading()
{
	_reload = 45;
}

void Tank::rotate(size_t angle)
{
	_angle = angle;
}

void Tank::update()
{
	if (_animationProgress > 0) {
		_animationProgress--;
	}
	if (_reload > 0) {
		_reload--;
	}
}

void Tank::demage()
{
	_hp--;
	if (_hp == 0) {
		emit destruction();
	}
}

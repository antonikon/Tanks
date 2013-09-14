#pragma once
#include <QObject>
#include <QtCore>

class Wall : public QObject
{
	Q_OBJECT
public:
	explicit Wall(const QPoint &pos, size_t type = 0, QObject *parent = 0);
	QPoint getPosition() {
		return _pos;
	}
	size_t getType() {
		return _type;
	}
	void demage();
signals:
	void destruction();
public slots:
	
private:
	QPoint _pos;
	size_t _type = 0, _hp = 1;
};

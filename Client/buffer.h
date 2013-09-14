#pragma once

#include <QObject>
#include <QtCore>
#include <QImage>

class Buffer : public QObject
{
	Q_OBJECT
public:
	explicit Buffer(QObject *parent = 0);
	QImage *getTankImage(size_t index) {
		return _imageTankList[index];
	}
	QImage *getWallImage(size_t index) {
		return _imageWallList[index];
	}
	QImage *getBulletImage(size_t index) {
		return _imageBulletList[index];
	}
signals:
	
public slots:

private:
	void loadImages();
private:
	QVector <QImage*> _imageTankList;
	QVector <QImage*> _imageWallList;
	QVector <QImage*> _imageBulletList;
};

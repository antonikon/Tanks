#include "buffer.h"

Buffer::Buffer(QObject *parent) :
	QObject(parent)
{
	loadImages();
}

void Buffer::loadImages()
{
	QImage *image = new QImage("images/greenTank1.png");
	_imageTankList.append(image);
	image = new QImage("images/greenTank1P.png");
	_imageTankList.append(image);

	image = new QImage("images/wall1.png");
	_imageWallList.append(image);

	image = new QImage("images/bullet1.png");
	_imageBulletList.append(image);
}

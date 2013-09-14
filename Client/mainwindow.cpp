#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(&_client, SIGNAL(readyPaint()), this, SLOT(paint()));
	connect(this, SIGNAL(readySendPacket(QVector<bool>,bool,bool)), &_client, SLOT(createPacket(QVector<bool>,bool,bool)));
	_keys.append(false);
	_keys.append(false);
	_keys.append(false);
	_keys.append(false);
	startTimer(30);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *key)
{
	switch (key->key()) {
		case Qt::Key_Up:
		{
			_keys[0] = true;
			_keys[1] = false;
			_keys[2] = false;
			_keys[3] = false;
			break;
		}
		case Qt::Key_Right:
		{
			_keys[1] = true;
			_keys[0] = false;
			_keys[2] = false;
			_keys[3] = false;
			break;
		}
		case Qt::Key_Down:
		{
			_keys[2] = true;
			_keys[0] = false;
			_keys[1] = false;
			_keys[3] = false;
			break;
		}
		case Qt::Key_Left:
		{
			_keys[3] = true;
			_keys[0] = false;
			_keys[1] = false;
			_keys[2] = false;
			break;
		}
		case Qt::Key_Space:
		{
			_keyFire = true;
			break;
		}
		case Qt::Key_Shift:
		{
			_keyShift = true;
			break;
		}
	}

}

void MainWindow::keyReleaseEvent(QKeyEvent *key)
{
	switch (key->key()) {
		case Qt::Key_Up:
		{
			_keys[0] = false;
			break;
		}
		case Qt::Key_Right:
		{
			_keys[1] = false;
			break;
		}
		case Qt::Key_Down:
		{
			_keys[2] = false;
			break;
		}
		case Qt::Key_Left:
		{
			_keys[3] = false;
			break;
		}
		case Qt::Key_Space:
		{
			_keyFire = false;
			break;
		}
		case Qt::Key_Shift:
		{
			_keyShift = false;
			break;
		}
	}
}

void MainWindow::paint()
{
	update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.fillRect(0,0,300,300,Qt::white);
	_client.paintAll(&painter);
}


void MainWindow::timerEvent(QTimerEvent *)
{
	readySendPacket(_keys,_keyFire,_keyShift);
}

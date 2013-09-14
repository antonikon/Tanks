#pragma once
#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>
#include "client.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void keyPressEvent(QKeyEvent *key);
	void keyReleaseEvent(QKeyEvent *key);

private slots:
	void paint();
signals:
	void readySendPacket(QVector <bool> keys, bool keyFire, bool keyShift);
private:
	void paintEvent(QPaintEvent *);
	void keyChanged();
	void timerEvent(QTimerEvent *);
private:
	Ui::MainWindow *ui;
	Client _client;
	QVector <bool> _keys;
	bool _keyFire = false;
	bool _keyShift = false;
};

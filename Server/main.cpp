#include <QCoreApplication>
#include <ctime>

#include "server.h"

int main(int argc, char *argv[])
{
	srand(time(0));
	QCoreApplication a(argc, argv);
	Server server;
	return a.exec();
}


#include "src/global.h"
#include <QtWidgets/QApplication>
#include "DSMmainwindow.h"

BaseCube *BaseCube::cub_instance;
BaseSphere* BaseSphere::sph_instance;
BaseCylinder* BaseCylinder::cyl_instance;

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	QSurfaceFormat format;
	format.setDepthBufferSize(16);
	format.setVersion(4, 1);
	format.setRenderableType(QSurfaceFormat::OpenGL);
	QSurfaceFormat::setDefaultFormat(format);
	MainWindow* w = new MainWindow();
	w->show();

	return a.exec();
}

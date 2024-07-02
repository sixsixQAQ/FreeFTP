// #include "FreeFTP.h"
// #include <QtWidgets/QApplication>
//
// int main(int argc, char *argv[])
//{
//     QApplication a(argc, argv);
//     FreeFTP w;
//     w.show();
//     return a.exec();
// }


#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QTreeView>
#include <QPushButton>
int
main (int argc, char *argv[])
{
	QApplication app (argc, argv);

	QPushButton btn ("Open File");
	btn.show();

	QFileDialog dialog (nullptr, "Open File");

	QObject::connect (&btn, &QPushButton::clicked, &dialog, &QFileDialog::raise);
	dialog.setFileMode (QFileDialog::ExistingFiles);

	dialog.show();

	return app.exec();
}
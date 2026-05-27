#include "mainwindow.h"
#include <QApplication>
#include<QDir>
#include "constants.h"
#include<QIcon>

int main(int argc, char *argv[])
{

    QCoreApplication::setApplicationName("IChingDiviner");
    QCoreApplication::setOrganizationName("Alamahant");
    QCoreApplication::setApplicationVersion("1.0.3");

    QDir().mkpath(Constants::appDirPath);
    QDir().mkpath(Constants::decksDirPath);
    QDir().mkpath(Constants::saveDirPath);
    QDir().mkpath(Constants::journalDirPath);
    QDir().mkpath(Constants::screenshotsDirPath);

    QApplication a(argc, argv);

    MainWindow::loadChineseFont();

    a.setWindowIcon(QIcon(":/io.github.alamahant.IChingDiviner.png"));
    MainWindow w;
    w.show();
    return a.exec();
}

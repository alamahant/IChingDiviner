#include "mainwindow.h"
#include <QApplication>
#include<QDir>
#include "constants.h"
#include<QIcon>
#include<QSettings>

int main(int argc, char *argv[])
{

    QCoreApplication::setApplicationName("IChingDiviner");
    QCoreApplication::setOrganizationName("Alamahant");
    QCoreApplication::setApplicationVersion("1.0.5");

#ifdef Q_OS_WIN
    QSettings::setDefaultFormat(QSettings::IniFormat);
#endif

    QSettings settings;

    double factor = settings.value("ui/scaleFactor", 1.0).toDouble();
    qputenv("QT_SCALE_FACTOR", QByteArray::number(factor));
    Constants::FONTSIZE = settings.value("ui/fontSize", Constants::DEFAULTFONTSIZE).toReal();

    QDir().mkpath(Constants::appDirPath);
    QDir().mkpath(Constants::decksDirPath);
    QDir().mkpath(Constants::saveDirPath);
    QDir().mkpath(Constants::journalDirPath);
    QDir().mkpath(Constants::screenshotsDirPath);

    QApplication a(argc, argv);

#ifdef Q_OS_WIN

    a.setStyle(QStyleFactory::create("Fusion"));

    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, Qt::white);
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, Qt::white);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    lightPalette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    lightPalette.setColor(QPalette::HighlightedText, Qt::white);

    a.setPalette(lightPalette);
    a.setStyleSheet("QLineEdit { placeholder-text-color: #999999; }");
#endif

    MainWindow::loadChineseFont();

    if (Constants::FONTSIZE > 0.0) {
           QFont appFont = a.font();
           appFont.setPointSizeF(Constants::FONTSIZE);
           a.setFont(appFont);
       } else {
           Constants::FONTSIZE = Constants::DEFAULTFONTSIZE;
       }

    a.setWindowIcon(QIcon(":/io.github.alamahant.IChingDiviner.png"));
    MainWindow w;
    w.show();
    return a.exec();
}

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include<QStandardPaths>
#include<QString>

namespace Constants {

    extern const QString appDirPath;
    extern const QString decksDirPath;
    extern const QString saveDirPath;
    extern const QString journalDirPath;
    extern const QString screenshotsDirPath;

    extern int tarotLabelHeight;
    extern int tarotLabelWidth;;
    extern int mandalaLabelHeight;
    extern int mandalaLabelWidth;;

}
extern bool activeModelLoaded;
#endif // CONSTANTS_H

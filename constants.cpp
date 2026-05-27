#include "constants.h"

namespace Constants {

#ifndef FLATPAK_BUILD
const QString appDirPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/IChingDiviner";
#else
const QString appDirPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/IChingDiviner";
#endif

const QString decksDirPath = appDirPath + "/decks";
const QString saveDirPath = appDirPath + "/saved";
const QString journalDirPath = appDirPath + "/journal";
const QString screenshotsDirPath = appDirPath + "/screenshots";


int tarotLabelHeight = 450; // def 450
int tarotLabelWidth = 300;  // def 300
int mandalaLabelHeight = 350; //def 350
int mandalaLabelWidth = 350; // def 350


}
bool activeModelLoaded = false;

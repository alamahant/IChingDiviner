#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QPalette>
#include<QFile>
#include<QGroupBox>
#include<QRandomGenerator>
#include<QPixmap>
#include<QColor>
#include<QRect>
#include<QPainter>
#include<QJsonObject>
#include<QJsonDocument>
#include<QMenu>
#include<QMenuBar>
#include"constants.h"
#include<QDir>
#include<QShortcut>
#include<QGroupBox>
#include<QMessageBox>
#include<QProcess>
#include<QFileDialog>
#include<QDesktopServices>
#include"helpmenudialog.h"
#include"donationdialog.h"
#include<QIcon>
#include<QPixmap>
#include<QtSvg/QSvgRenderer>
#include<QFontDatabase>
#include"journalmanager.h"
#include"socialsharedialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , iching(new IChing(this))
    , aiManager(new MistralAPI(this))
    , modelDialog(new ModelSelectorDialog(this))
    , mouseTimer(new QTimer(this))
    , journalDialog(new JournalDialog(this))
    , m_socialShare(new SocialShare(this))

{
    setWindowTitle("I-Ching Diviner");
    setWindowIcon(QIcon(":/io.github.alamahant.IChingDiviner.png"));

    //resize(800, 600);
    setMinimumSize(800, 600); // Set minimum size
    showMaximized(); // Start maximized


    // Create IChing instance
    //iching = new IChing();

    setupUI();
    setupDarkTheme();
    loadHexagramMeanings();
    // Connect signals and slots
    connect(autoTossButton, &QPushButton::clicked, this, &MainWindow::onAutoTossClicked);
    connect(tossButton, &QPushButton::clicked, this, &MainWindow::onTossClicked);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::onResetClicked);

    isTarotMode = settings.value("istarotmode", false).toBool();

    createMenus();

    coinSound = new QSoundEffect(this);
    coinSound->setSource(QUrl("qrc:/files/coin.wav"));
    coinSound->setVolume(0.8);
    QSettings settings;
    isPlaySounds = settings.value("sounds/isplaysounds", false).toBool();
    playSoundsAction->setChecked(isPlaySounds);
    if(isPlaySounds) coinSound->play();

    setupShareButton();
    connect(journalDialog, &JournalDialog::loadReadingRequested, this, [this](const QString& fileName){
        loadDivinationFromFile(fileName);
    });

}

MainWindow::~MainWindow()
{
    delete iching;
}


void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Main layout with minimal spacing
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Create a dedicated widget for the coin area
    coinDisplayWidget = new QFrame();
    coinDisplayWidget->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    coinDisplayWidget->setAutoFillBackground(false);

    QHBoxLayout *coinsLayout = new QHBoxLayout(coinDisplayWidget);
    coinsLayout->setContentsMargins(10, 10, 10, 10);
    coinsLayout->setSpacing(10);

    coinLabel1 = new QLabel();
    coinLabel2 = new QLabel();
    coinLabel3 = new QLabel();

    coinLabel1->installEventFilter(this);
    coinLabel2->installEventFilter(this);
    coinLabel3->installEventFilter(this);

    resetCoins();

    QFont coinFont;
#ifndef FLATPAK_BUILD
    coinFont.setPointSize(150); // was 120
    coinLabel1->setFont(coinFont);
    coinLabel2->setFont(coinFont);
    coinLabel3->setFont(coinFont);

    coinLabel1->setFixedHeight(180); // was 90
    coinLabel2->setFixedHeight(180);
    coinLabel3->setFixedHeight(180);
#else
    coinFont.setPointSize(100); // was 120
    coinLabel1->setFont(coinFont);
    coinLabel2->setFont(coinFont);
    coinLabel3->setFont(coinFont);

    coinLabel1->setFixedHeight(160); // was 90
    coinLabel2->setFixedHeight(160);
    coinLabel3->setFixedHeight(160);

#endif


    coinLabel1->setAlignment(Qt::AlignCenter);
    coinLabel2->setAlignment(Qt::AlignCenter);
    coinLabel3->setAlignment(Qt::AlignCenter);


    coinsLayout->addWidget(coinLabel1);
    coinsLayout->addWidget(coinLabel2);
    coinsLayout->addWidget(coinLabel3);

    // Buttons area
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    autoTossButton = new QPushButton("Auto Toss");
    tossButton = new QPushButton("Toss");
    resetButton = new QPushButton("Reset");
    buttonsLayout->addWidget(autoTossButton);
    buttonsLayout->addWidget(tossButton);
    buttonsLayout->addWidget(resetButton);

    // Hexagram display area
    QHBoxLayout *hexagramLayout = new QHBoxLayout();

    // Source hexagram
    QHBoxLayout *sourceLayout = new QHBoxLayout();
    QVBoxLayout *sourceLabelLayout = new QVBoxLayout();
    sourceLabelLayout->setSpacing(2);
    sourceHexagramTitleLabel = new QLabel("Source Hexagram");
    sourceHexagramTitleLabel->setAlignment(Qt::AlignCenter);
    sourceHexagramTitleLabel->setWordWrap(true);
    sourceHexagramTitleLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    sourceHexagramDisplayLabel = new QLabel();
    sourceHexagramDisplayLabel->setFixedSize(200, 200);
    sourceHexagramDisplayLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    sourceHexagramDisplayLabel->setAlignment(Qt::AlignCenter);

    sourceLabelLayout->addWidget(sourceHexagramTitleLabel);
    sourceLabelLayout->addWidget(sourceHexagramDisplayLabel);
    sourceLayout->addLayout(sourceLabelLayout);

    sourceHexagramTarotLabel = new QLabel("IChing Card");

    if(isTarotMode){
    sourceHexagramTarotLabel->setFixedSize(Constants::tarotLabelWidth, Constants::tarotLabelHeight);
    }else{
        sourceHexagramTarotLabel->setFixedSize(Constants::mandalaLabelWidth, Constants::mandalaLabelHeight);

    }
    sourceHexagramTarotLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    sourceHexagramTarotLabel->setAlignment(Qt::AlignCenter);
    sourceLayout->addWidget(sourceHexagramTarotLabel);

    // Modified hexagram
    QHBoxLayout *modifiedLayout = new QHBoxLayout();
    QVBoxLayout *modifiedLabelLayout = new QVBoxLayout();
    modifiedLabelLayout->setSpacing(2);
    modifiedHexagramTitleLabel = new QLabel("Modified Hexagram");
    modifiedHexagramTitleLabel->setAlignment(Qt::AlignCenter);
    modifiedHexagramTitleLabel->setWordWrap(true);
    modifiedHexagramTitleLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    modifiedHexagramDisplayLabel = new QLabel();
    modifiedHexagramDisplayLabel->setFixedSize(200, 200);
    modifiedHexagramDisplayLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    modifiedHexagramDisplayLabel->setAlignment(Qt::AlignCenter);

    modifiedLabelLayout->addWidget(modifiedHexagramTitleLabel);
    modifiedLabelLayout->addWidget(modifiedHexagramDisplayLabel);
    modifiedLayout->addLayout(modifiedLabelLayout);

    modifiedHexagramTarotLabel = new QLabel("IChing Card");


    if(isTarotMode){
    modifiedHexagramTarotLabel->setFixedSize(Constants::tarotLabelWidth, Constants::tarotLabelHeight);
    }else{
        modifiedHexagramTarotLabel->setFixedSize(Constants::mandalaLabelWidth, Constants::mandalaLabelHeight);

    }

    modifiedHexagramTarotLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    modifiedHexagramTarotLabel->setAlignment(Qt::AlignCenter);
    modifiedLayout->addWidget(modifiedHexagramTarotLabel);

    hexagramLayout->addLayout(sourceLayout);
    hexagramLayout->addLayout(modifiedLayout);

    // Create top section
    QWidget *topSectionWidget = new QWidget();
    QVBoxLayout *topSectionLayout = new QVBoxLayout(topSectionWidget);
    topSectionLayout->setContentsMargins(0, 0, 0, 0);
    topSectionLayout->setSpacing(5);
    topSectionLayout->addWidget(coinDisplayWidget, 1);
    //topSectionLayout->addSpacing(15);
    topSectionLayout->addLayout(buttonsLayout);

    // Create bottom section
    QWidget *bottomSectionWidget = new QWidget();
    QVBoxLayout *bottomLayout = new QVBoxLayout(bottomSectionWidget);
    bottomLayout->setContentsMargins(0, 0, 0, 0);
    bottomLayout->addLayout(hexagramLayout);

    // Create splitter
    QSplitter *splitter = new QSplitter(Qt::Vertical);
    splitter->addWidget(topSectionWidget);
    splitter->addWidget(bottomSectionWidget);

    QList<int> sizes;
    sizes << 100 << 200;
    splitter->setSizes(sizes);
    splitter->setChildrenCollapsible(false);

    mainLayout->addWidget(splitter);

    meaningDock = new QDockWidget("Controls", this);
    meaningDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    meaningDock->setFeatures(QDockWidget::DockWidgetMovable |
                             QDockWidget::DockWidgetFloatable |
                             QDockWidget::DockWidgetClosable);
    meaningDock->setMinimumSize(0, 0);

    // Create container widget for dock contents
    QWidget *dockContainer = new QWidget();
    QVBoxLayout *dockLayout = new QVBoxLayout(dockContainer);

    // Import Physical Toss button
    importModeButton = new QPushButton("Import Physical Toss", this);
    importModeButton->setToolTip(
        "Toggle to manually flip coins for physical I Ching tosses.\n\n"
        "When ON:\n"
        "- Click on each coin to flip it (heads/tails)\n"
        "- 'Toss' button becomes 'Set Result'\n"
        "- Click 'Set Result' to record the current coin state\n\n"
        "Perfect for importing real physical coin tosses!"
    );
    importModeButton->setCheckable(true);
    importModeButton->setChecked(false);
    connect(importModeButton, &QPushButton::toggled, this, &MainWindow::onImportModeToggled);
    dockLayout->addWidget(importModeButton);

    // Journal button
    openJournalButton = new QPushButton("Journal", this);
    openJournalButton->setToolTip("Open the journal");
    connect(openJournalButton, &QPushButton::clicked, this, [this](){
        journalDialog->refreshForDate(QDate::currentDate());
        journalDialog->show();
        journalDialog->raise();
    });
    dockLayout->addWidget(openJournalButton);

    QLabel* meaningsLabel = new QLabel("Hexagram Meanings");
    meaningsLabel->setToolTip("Ctrl+mouse wheel to zoom in/out");

    dockLayout->addWidget(meaningsLabel);

    // Meaning text edit
    meaningTextEdit = new QTextEdit();
    meaningTextEdit->setAcceptRichText(true);
    meaningTextEdit->setReadOnly(true);
    //meaningTextEdit->setToolTip("Ctrl+mouse wheel to zoom in/out");
    dockLayout->addWidget(meaningTextEdit);

    // Set the container as the dock widget's content
    meaningDock->setWidget(dockContainer);

    addDockWidget(Qt::RightDockWidgetArea, meaningDock);


    // --- LEFT DOCK: Controls & AI Interpretation ---
    controlDock = new QDockWidget("Controls", this);
    controlDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    controlDock->setFeatures(QDockWidget::DockWidgetMovable |
                             QDockWidget::DockWidgetFloatable |
                             QDockWidget::DockWidgetClosable);

    controlDock->setMinimumSize(0, 0);

    QWidget *controlWidget = new QWidget();
    QVBoxLayout *controlLayout = new QVBoxLayout(controlWidget);


    //deck combo
    deckCombo = new QComboBox();
    deckCombo->setToolTip("Your imported IChing decks will appear here.");
    populateDecksComboBox();
    currentDeck = deckCombo->itemText(0);
    deckCombo->setCurrentText(currentDeck);
    controlLayout->addWidget(deckCombo);

    connect(deckCombo, &QComboBox::currentTextChanged, this, [this](const QString &text){
        currentDeck = text.trimmed();

        if (iching->getCurrentLines().size() == 6) {
            HexagramInfo sourceInfo = iching->getSourceHexagram();
            int sourceNum = sourceInfo.number.toInt();
            loadTarotCardImage(sourceHexagramTarotLabel, sourceNum);

            HexagramInfo modifiedInfo = iching->getModifiedHexagram();
            if (!modifiedInfo.number.isEmpty()) {
                int modifiedNum = modifiedInfo.number.toInt();
                loadTarotCardImage(modifiedHexagramTarotLabel, modifiedNum);
            }
        }
    });


    openQuestionDialogButton = new QPushButton("Set a Question", this);

    openQuestionDialogButton->setToolTip("Pose a question to be forwarded to AI");
    connect(openQuestionDialogButton, &QPushButton::clicked, this, &MainWindow::onSetQuestion);
    controlLayout->addWidget(openQuestionDialogButton);

    //shuffle
    shuffleButton = new QPushButton("Enchanted Coins", this);
    shuffleButton->setToolTip("Move the mouse around to gather entropy.\n"
                              "Simulates physically shaking\n"
                              "the coins in your palms before tossing.");
    shuffleButton->setCheckable(true);
    shuffleButton->setChecked(false);
    connect(shuffleButton, &QPushButton::toggled, this, &MainWindow::toggleShuffle);
    controlLayout->addWidget(shuffleButton);

    aiPredictionButton = new QPushButton("Get AI Interpretation");
    aiPredictionButton->setToolTip("Your hexagram data together with your question\n"
                                   "will be forwarded to AI for interpretation");
    connect(aiPredictionButton, &QPushButton::clicked, this, &MainWindow::gatAiInterpretation);
    controlLayout->addWidget(aiPredictionButton);


    // AI Interpretation section
    QLabel *aiLabel = new QLabel("AI Interpretation");
    aiLabel->setAlignment(Qt::AlignCenter);
    QFont aiFont = aiLabel->font();
    aiFont.setBold(true);
    aiFont.setPointSize(8);
    aiLabel->setFont(aiFont);
    aiLabel->setVisible(false);

    aiTextEdit = new QTextEdit();
    aiTextEdit->setAcceptRichText(true);
    aiTextEdit->setPlaceholderText("AI interpretation will appear here after configuring AI settings...");
    aiTextEdit->setReadOnly(true);

    controlLayout->addWidget(aiLabel);
    controlLayout->addWidget(aiTextEdit);

    controlDock->setWidget(controlWidget);
    addDockWidget(Qt::LeftDockWidgetArea, controlDock);
}

void MainWindow::setupDarkTheme()
{
    QPalette darkPalette;
    //darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::Window, QColor(0, 0, 0));        // Pure black
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);


    qApp->setPalette(darkPalette);
    /*
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }"
                        //"QTextEdit { background-color:  #1a1a1a; color: white; }"
                        );
    */
    qApp->setStyleSheet(
        "QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }"

        /* All buttons - consistent height */
        "QPushButton {"
        "    min-height: 24px;"
        "    max-height: 24px;"
        "    padding: 2px 2px;"
        "}"

        /* Hover effect for all buttons */
        "QPushButton:hover {"
        "    background-color: #3a6ea5;"
        "    border: 1px solid #6ea8dc;"
        "}"

        /* Pressed effect */
        "QPushButton:pressed {"
        "    background-color: #1e4a76;"
        "}"

        /* Specific button - Set Question (make it stand out) */
        "QPushButton#openQuestionDialogButton {"
        "    background-color: #2a5f8a;"
        "    font-weight: bold;"
        "}"

        "QPushButton#openQuestionDialogButton:hover {"
        "    background-color: #3a7aaa;"
        "}"

        /* Shuffle/Enchanted Coins button - checkable state */
        "QPushButton#shuffleButton:checked {"
        "    background-color: #1e4a76;"
        "    border: 1px solid #6ea8dc;"
        "}"

        /* AI Interpretation button - special styling */
        "QPushButton#aiPredictionButton {"
        "    background-color: #4a6a3a;"
        "    font-weight: bold;"
        "}"

        "QPushButton#aiPredictionButton:hover {"
        "    background-color: #5a8a4a;"
        "}"

        /* Combo box styling */
        "QComboBox {"
        "    min-height: 26px;"
        "    max-height: 26px;"
        "    padding: 2px 4px;"
        "}"

        "QComboBox:hover {"
        "    border: 1px solid #6ea8dc;"
        "}"

        /* Group box styling */
        "QGroupBox {"
        "    font-weight: bold;"
        "    border: 1px solid #555;"
        "    margin-top: 10px;"
        "    padding-top: 10px;"
        "}"

        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 5px 0 5px;"
        "}"

        /* Splitter handle - make it thicker and visible */
        "QSplitter::handle {"
        //"    background-color: #4a4a4a;"
        "    height: 6px;"
        "    width: 6px;"
        "}"

        "QSplitter::handle:hover {"
        //"    background-color: #6ea8dc;"
        "}"

        "QSplitter::handle:pressed {"
        //"    background-color: #2a6a9a;"
        "}"

        /* Import Physical Toss button - checked state */

        "QPushButton::checked {"
        "    background-color: #6a4e3a;"
        "    border: 2px solid #ffaa66;"
        "    font-weight: bold;"
        "}"
        ""
        "QPushButton::checked:hover {"
        "    background-color: #7a5e4a;"
        "    border: 2px solid #ffcc88;"
        "}"

    );

}

void MainWindow::onAutoTossClicked()
{


    // Perform the divination using IChing
    QList<QList<int>> allCoinTosses = iching->performFullDivination();

    // Display the last set of coins (for visual effect)
    if (!allCoinTosses.isEmpty()) {
        displayCoinResults(allCoinTosses.last());
    }

    // Update the UI with results
    updateHexagramDisplay();

    if(isPlaySounds) coinSound->play();

}



void MainWindow::displayCoinResults(const QList<int> &coinResults)
{
    if (coinResults.size() >= 3) {
        QLabel* coinLabels[] = { coinLabel1, coinLabel2, coinLabel3 };

        for (int i = 0; i < 3; i++) {
            QString svgPath = (coinResults[i] == 1)
                ? ":/files/chinese_coin_heads.svg"
                : ":/files/chinese_coin_tails.svg";

            int size = 170; // just under fixedHeight of 180

            QSvgRenderer renderer(svgPath);
            QPixmap pixmap(size, size);
            pixmap.fill(Qt::transparent);

            QPainter painter(&pixmap);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setRenderHint(QPainter::SmoothPixmapTransform);
            renderer.render(&painter);
            painter.end();

            coinLabels[i]->setPixmap(pixmap);
            coinLabels[i]->setAlignment(Qt::AlignCenter);
        }
    }
}


void MainWindow::onResetClicked()
{

    // Reset coin display
   resetCoins();

    // Reset hexagram displays
    sourceHexagramTitleLabel->setText("Source Hexagram");
    sourceHexagramDisplayLabel->clear();
    sourceHexagramTarotLabel->setText("IChing Card");
    modifiedHexagramTitleLabel->setText("Modified Hexagram");
    modifiedHexagramDisplayLabel->clear();
    modifiedHexagramTarotLabel->setText("IChing Card");
    aiTextEdit->clear();
    // Clear meaning text
    meaningTextEdit->clear();

    // Reset IChing state
    iching->reset();

    // Reset import mode coin states if active
    if (importModeActive) {
        resetCoins();
        for (QLabel* coin : {coinLabel1, coinLabel2, coinLabel3}) {
            coin->setProperty("isHeads", false);
        }
    }
    currentQuestion = QString();
    openQuestionDialogButton->setToolTip(QString("Pose a question to be forwarded to AI"));

}

/*
void MainWindow::loadHexagramMeanings()
{
    QString datasetPath = Constants::appDirPath + "/iching.json";
    //QFile file(":/files/iching.json"); // Path to JSON file
    QFile file(datasetPath); // Path to  JSON file

    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        return;
    }

    QJsonObject root = doc.object();
    hexagramMeanings.clear();

    // Iterate through each hexagram (keys "1", "2", etc.)
    for (const QString &key : root.keys()) {
        QJsonObject hexObj = root[key].toObject();
        int hexNumber = key.toInt();

        QString meaning;

        // Add header with hexagram info
        meaning += QString("%1. %2").arg(hexNumber).arg(hexObj["english"].toString());

        // Add above/below info if available
        if (hexObj.contains("wilhelm_above") && hexObj.contains("wilhelm_below")) {
            QJsonObject above = hexObj["wilhelm_above"].toObject();
            QJsonObject below = hexObj["wilhelm_below"].toObject();
            meaning += QString("\nabove %1 %2 %3\nbelow %4 %5 %6\n\n")
                .arg(above["chinese"].toString())
                .arg(above["symbolic"].toString())
                .arg(above["alchemical"].toString())
                .arg(below["chinese"].toString())
                .arg(below["symbolic"].toString())
                .arg(below["alchemical"].toString());
        }

        // Add wilhelm_symbolic (main description)
        if (hexObj.contains("wilhelm_symbolic")) {
            meaning += hexObj["wilhelm_symbolic"].toString() + "\n\n";
        }

        // Add judgment
        if (hexObj.contains("wilhelm_judgment")) {
            QJsonObject judgment = hexObj["wilhelm_judgment"].toObject();
            meaning += "THE JUDGMENT\n";
            meaning += judgment["text"].toString() + "\n\n";
            meaning += judgment["comments"].toString() + "\n\n";
        }

        // Add image
        if (hexObj.contains("wilhelm_image")) {
            QJsonObject image = hexObj["wilhelm_image"].toObject();
            meaning += "THE IMAGE\n";
            meaning += image["text"].toString() + "\n\n";
            meaning += image["comments"].toString() + "\n\n";
        }

        // Add lines
        if (hexObj.contains("wilhelm_lines")) {
            QJsonObject lines = hexObj["wilhelm_lines"].toObject();
            meaning += "THE LINES\n";
            for (const QString &lineKey : lines.keys()) {
                QJsonObject line = lines[lineKey].toObject();
                meaning += QString("\nLine %1:\n").arg(lineKey);
                meaning += line["text"].toString() + "\n";
                meaning += line["comments"].toString() + "\n";
            }
        }

        hexagramMeanings[hexNumber] = meaning;
    }

}
*/

void MainWindow::loadHexagramMeanings()
{
    QString datasetPath = Constants::appDirPath + "/iching.json";
    QFile file(datasetPath);

    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        return;
    }

    QJsonObject root = doc.object();
    hexagramMeanings.clear();

    for (const QString &key : root.keys()) {
        QJsonObject hexObj = root[key].toObject();
        int hexNumber = key.toInt();

        QString html;

        // MAIN CONTAINER - NO FIXED PIXEL SIZE
        html += QString("<div style='font-family: Georgia, serif; line-height: 1.6; color: #dddddd;'>");

        // Header with hexagram number and name - relative size
        html += QString("<h2 style='color: #ffd700; font-size: 1.8em; margin-bottom: 5px;'>%1. %2</h2>")
                .arg(hexNumber)
                .arg(hexObj["english"].toString());

        // Above/Below info as badges - relative size
        if (hexObj.contains("wilhelm_above") && hexObj.contains("wilhelm_below")) {
            QJsonObject above = hexObj["wilhelm_above"].toObject();
            QJsonObject below = hexObj["wilhelm_below"].toObject();
            html += QString("<div style='background: #2a2a2a; padding: 10px; border-radius: 6px; margin: 10px 0; font-size: 0.85em;'>"
                           "<span style='color: #88ff88;'>☯ above</span> %1 %2 %3 &nbsp;&nbsp;|&nbsp;&nbsp;"
                           "<span style='color: #ff8888;'>☯ below</span> %4 %5 %6"
                           "</div>")
                    .arg(above["chinese"].toString())
                    .arg(above["symbolic"].toString())
                    .arg(above["alchemical"].toString())
                    .arg(below["chinese"].toString())
                    .arg(below["symbolic"].toString())
                    .arg(below["alchemical"].toString());
        }

        // Symbolic description - relative size
        if (hexObj.contains("wilhelm_symbolic")) {
            QString symbolic = hexObj["wilhelm_symbolic"].toString();
            symbolic.replace("\n\n", "</p><p style='margin-bottom: 12px;'>");
            symbolic.replace("\n", "<br>");
            html += QString("<div style='margin: 15px 0;'>"
                           "<p style='margin-bottom: 12px; line-height: 1.6; font-size: 1em;'>%1</p></div>").arg(symbolic);
        }

        // Judgment section - relative size
        if (hexObj.contains("wilhelm_judgment")) {
            QJsonObject judgment = hexObj["wilhelm_judgment"].toObject();
            html += "<div style='background: #1a2a1a; padding: 12px; border-left: 4px solid #88ff88; margin: 15px 0; border-radius: 4px;'>";
            html += "<h3 style='color: #88ff88; font-size: 1.3em; margin-top: 0; margin-bottom: 8px;'>⚖️ THE JUDGMENT</h3>";
            html += QString("<p style='margin-bottom: 8px; font-size: 1em;'><i>%1</i></p>").arg(judgment["text"].toString());
            if (judgment.contains("comments") && !judgment["comments"].toString().isEmpty()) {
                html += QString("<p style='color: #aaaaaa; font-size: 0.85em;'>%1</p>").arg(judgment["comments"].toString());
            }
            html += "</div>";
        }

        // Image section - relative size
        if (hexObj.contains("wilhelm_image")) {
            QJsonObject image = hexObj["wilhelm_image"].toObject();
            html += "<div style='background: #1a1a2a; padding: 12px; border-left: 4px solid #ffaa66; margin: 15px 0; border-radius: 4px;'>";
            html += "<h3 style='color: #ffaa66; font-size: 1.3em; margin-top: 0; margin-bottom: 8px;'>🖼️ THE IMAGE</h3>";
            html += QString("<p style='margin-bottom: 8px; font-size: 1em;'><i>%1</i></p>").arg(image["text"].toString());
            if (image.contains("comments") && !image["comments"].toString().isEmpty()) {
                html += QString("<p style='color: #aaaaaa; font-size: 0.85em;'>%1</p>").arg(image["comments"].toString());
            }
            html += "</div>";
        }

        // Lines section - THIS WILL NOW ZOOM WITH CTRL+WHEEL
        if (hexObj.contains("wilhelm_lines")) {
            QJsonObject lines = hexObj["wilhelm_lines"].toObject();
            html += "<div style='margin: 15px 0;'>";
            html += "<h3 style='color: #88aaff; font-size: 1.3em;'>📜 THE LINES</h3>";
            for (const QString &lineKey : lines.keys()) {
                QJsonObject line = lines[lineKey].toObject();
                html += QString("<div style='background: #1a1a1a; padding: 12px; margin: 10px 0; border-radius: 4px; border-left: 3px solid #88aaff;'>");
                html += QString("<b style='color: #88aaff; font-size: 1.05em;'>Line %1</b><br>").arg(lineKey);
                html += QString("<span style='font-style: italic; font-size: 1em;'>%1</span><br>").arg(line["text"].toString());
                if (line.contains("comments") && !line["comments"].toString().isEmpty()) {
                    html += QString("<span style='color: #aaaaaa; font-size: 0.85em;'>%1</span>").arg(line["comments"].toString());
                }
                html += "</div>";
            }
            html += "</div>";
        }

        html += "</div>";
        hexagramMeanings[hexNumber] = html;
    }
}

/*
void MainWindow::displayHexagramMeanings(int sourceHexNumber, int modifiedHexNumber)
{
    meaningTextEdit->clear();
    QString combinedMeaning;

    // Always try to show source hexagram
    QString sourceMeaning = hexagramMeanings.value(sourceHexNumber);
    if (!sourceMeaning.isEmpty()) {
        combinedMeaning += "SOURCE HEXAGRAM:\n\n";
        combinedMeaning += sourceMeaning;
    } else {
        combinedMeaning += "SOURCE HEXAGRAM:\n\n(No interpretation available)\n";
    }

    // Show resulting hexagram only if it exists and is different
    if (modifiedHexNumber > 0 && modifiedHexNumber != sourceHexNumber) {
        QString modifiedMeaning = hexagramMeanings.value(modifiedHexNumber);
        if (!modifiedMeaning.isEmpty()) {
            combinedMeaning += "\n\nRESULTING HEXAGRAM:\n\n";
            combinedMeaning += modifiedMeaning;
        }
    }

    // Always overwrite previous text
    meaningTextEdit->clear();
    meaningTextEdit->setPlainText(combinedMeaning);
    meaningTextEdit->moveCursor(QTextCursor::Start);

}
*/

void MainWindow::displayHexagramMeanings(int sourceHexNumber, int modifiedHexNumber)
{
    QString html;

    // Source hexagram
    html += "<div style='margin-bottom: 30px;'>";
    html += hexagramMeanings.value(sourceHexNumber, "<p style='color: #ff6666;'>No interpretation available</p>");
    html += "</div>";

    // Resulting hexagram (if different)
    if (modifiedHexNumber > 0 && modifiedHexNumber != sourceHexNumber) {
        html += "<hr style='border-color: #ffd700; margin: 20px 0;'>";
        html += "<div style='margin-top: 20px;'>";
        html += hexagramMeanings.value(modifiedHexNumber);
        html += "</div>";
    }

    meaningTextEdit->setHtml(html);
    meaningTextEdit->moveCursor(QTextCursor::Start);
}


void MainWindow::loadTarotCardImage(QLabel* label, int hexagramNumber)
{
    if(!isTarotMode) {
        // Use IChing map to get char32_t code for the hexagram
                char32_t hexCode = iching->hexNumberToUnicode.value(hexagramNumber, 0x4DC0); // default to ䷀

                int labelSize = Constants::mandalaLabelHeight * 1.20;

                QPixmap pix = paintSevenCirclesWithHex(hexCode, labelSize);



                label->setPixmap(pix);
                label->setAlignment(Qt::AlignCenter);
                label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                return;
    }

    // Format the filename with leading zeros (00.png to 63.png)
    //QString filename = QString("cards/%1.png").arg(hexagramNumber-1, 2, 10, QChar('0'));
    //QString png = QString("cards/%2/%1.png").arg(hexagramNumber-1, 2, 10, QChar('0'));
    //QString jpg = QString("cards/%1.jpg").arg(hexagramNumber-1, 2, 10, QChar('0'));

    QString decksPath = Constants::decksDirPath;
    QString png = QString(decksPath + "/%1/%2.png")
                     .arg(currentDeck)
                     .arg(hexagramNumber-1, 2, 10, QChar('0'));

    QString jpg = QString(decksPath +  "/%1/%2.jpg")
                     .arg(currentDeck)
                     .arg(hexagramNumber-1, 2, 10, QChar('0'));

    QString filename = QFile::exists(png) ? png : jpg;

    QPixmap originalPixmap(filename);

    if (originalPixmap.isNull()) {
        label->setText("IChing card not found");
    } else {
        // Get the size of the label
        QSize labelSize = label->size();

        // Scale the pixmap to fit the label while maintaining aspect ratio
        QPixmap scaledPixmap = originalPixmap.scaled(
            labelSize.width(),
            labelSize.height(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            );

        label->setPixmap(scaledPixmap);
        label->setAlignment(Qt::AlignCenter);

        // Set a size policy to ensure the label resizes with the window
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    }
}


//////////////////


void MainWindow::onTossClicked()
{

    if (importModeActive) {
        importPhysicalToss();
        return;
    }

    // If we don't have 6 lines yet, add one more
    if (iching->getCurrentLines().size() < 6) {
        QList<int> coinToss = iching->performSingleToss();
        displayCoinResults(coinToss);

        int sum = coinToss[0] + coinToss[1] + coinToss[2];
        QString lineType;
        switch (sum) {
        case 0: lineType = "2"; break; // changing yin
        case 1: lineType = "0"; break; // stable yin
        case 2: lineType = "1"; break; // stable yang
        case 3: lineType = "3"; break; // changing yang
        }

        QStringList currentLines = iching->getCurrentLines();

        currentLines.append(lineType);  // First toss becomes line 1 at BOTTOM

        iching->reset();

        for (const QString &line : currentLines) {
            iching->currentLines.append(line);
        }

        // Update display after each toss
        updateHexagramDisplay();
        if(isPlaySounds) coinSound->play();

        // show the full meaning
        if (currentLines.size() == 6) {
            // Get the hexagram numbers
            int sourceNum = 0;
            int modifiedNum = 0;

            // Extract the hexagram numbers
            HexagramInfo sourceInfo = iching->getSourceHexagram();
            HexagramInfo modifiedInfo = iching->getModifiedHexagram();

            if (!sourceInfo.number.isEmpty()) {
                QRegularExpression re("^(\\d+)");
                QRegularExpressionMatch match = re.match(sourceInfo.number);
                if (match.hasMatch()) {
                    sourceNum = match.captured(1).toInt();
                }
            }

            if (!modifiedInfo.number.isEmpty()) {
                QRegularExpression re("^(\\d+)");
                QRegularExpressionMatch match = re.match(modifiedInfo.number);
                if (match.hasMatch()) {
                    modifiedNum = match.captured(1).toInt();
                }
            }

            // Display the full meanings
            displayHexagramMeanings(sourceNum, modifiedNum);


        } else {
            // For incomplete hexagrams, show a progress message
            QString progressMessage = "Line " + QString::number(currentLines.size()) +
                                      " of 6 added. Continue tossing.";

            meaningTextEdit->setText(progressMessage);
        }
    } else {
        meaningTextEdit->setText("Hexagram is complete. Press Reset to start a new divination.");
    }

}


void MainWindow::updateHexagramDisplay()
{
    meaningTextEdit->clear();
    // Get current lines
    QStringList currentLines = iching->getCurrentLines();

    // Always draw the source hexagram, even if incomplete
    if (!currentLines.isEmpty()) {
        drawHexagram(sourceHexagramDisplayLabel, currentLines);
    } else {
        sourceHexagramDisplayLabel->clear();
    }

    // Get source hexagram info
    HexagramInfo sourceInfo = iching->getSourceHexagram();
    int sourceNum = 0;
    if (!sourceInfo.number.isEmpty()) {
        QRegularExpression re("^(\\d+)");
        QRegularExpressionMatch match = re.match(sourceInfo.number);
        if (match.hasMatch()) {
            sourceNum = match.captured(1).toInt();
        }
    }

    // Update source hexagram title
    QString sourceTitle;
    if (currentLines.size() < 6) {
        sourceTitle = "Building Hexagram: Line " + QString::number(currentLines.size()) + " of 6";
    } else {
        sourceTitle = sourceInfo.number + " " + sourceInfo.name;
        if (!sourceInfo.description.isEmpty())
            sourceTitle += " (" + sourceInfo.description + ")";
        sourceTitle += "\n" + sourceInfo.chineseName + " " + sourceInfo.pinyin;
    }
    sourceHexagramTitleLabel->setText(sourceTitle);

    // Load tarot card for source if complete
    if (currentLines.size() == 6) {
        loadTarotCardImage(sourceHexagramTarotLabel, sourceNum);
    } else {
        sourceHexagramTarotLabel->setText("Complete the hexagram\nto see the IChing card");
    }

    // Get modified hexagram info
    HexagramInfo modifiedInfo = iching->getModifiedHexagram();
    int modifiedNum = 0;
    if (!modifiedInfo.number.isEmpty()) {
        QRegularExpression re("^(\\d+)");
        QRegularExpressionMatch match = re.match(modifiedInfo.number);
        if (match.hasMatch()) {
            modifiedNum = match.captured(1).toInt();
        }
    }

    // Draw modified hexagram and title only if lines actually changed
    if (!modifiedInfo.number.isEmpty()) {
        drawHexagram(modifiedHexagramDisplayLabel, iching->getModifiedLines());

        QString modifiedTitle = modifiedInfo.number + " " + modifiedInfo.name;
        if (!modifiedInfo.description.isEmpty())
            modifiedTitle += " (" + modifiedInfo.description + ")";
        modifiedTitle += "\n" + modifiedInfo.chineseName + " " + modifiedInfo.pinyin;
        modifiedHexagramTitleLabel->setText(modifiedTitle);

        // Load tarot card
        loadTarotCardImage(modifiedHexagramTarotLabel, modifiedNum);
    } else {
        // Clear display if no modified hexagram
        modifiedHexagramDisplayLabel->clear();
        modifiedHexagramTitleLabel->setText("Modified Hexagram\n(will appear if lines change)");
        modifiedHexagramTarotLabel->clear();
    }

    // Always display meanings for source; include modified only if it exists
    if (currentLines.size() == 6) {
        displayHexagramMeanings(sourceNum, modifiedNum);
    }

    // Ensure dock widget is visible
    meaningDock->show();
}

void MainWindow::drawHexagram(QLabel *label, const QStringList &lines)
{

    if (lines.isEmpty()) {
        label->clear();
        return;
    }

    // Create a pixmap to draw on
    QPixmap pixmap(150, 150);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set up pen with vibrant golden color
    QColor vibrantGold(255, 215, 0);
    QColor changingLineRed(255, 0, 0);
    QColor fadedGold(255, 215, 0, 100); // Semi-transparent for missing lines

    QPen pen(vibrantGold);
    pen.setWidth(6);
    painter.setPen(pen);

    // Calculate line spacing and length
    int lineLength = 100;
    int lineSpacing = 20;
    int startY = 20;  // Top position
    int startX = (pixmap.width() - lineLength) / 2;


    // Draw all 6 positions from BOTTOM to TOP
    // need to draw line 6 (top) first at the highest Y,
    // then work my way down to line 1 (bottom) at the lowest Y


    for (int i = 0; i < 6; i++) {
        // Calculate Y position from TOP to BOTTOM
        // i=0 (top line/line 6) gets smallest Y
        // i=5 (bottom line/line 1) gets largest Y
        int y = startY + i * lineSpacing;

        // The line at position i from the TOP corresponds to line number (6-i) from the BOTTOM
        int lineIndexFromBottom = 5 - i; // Convert to 0-based index from bottom

        if (lineIndexFromBottom < lines.size()) {
            // We have a real line to draw



            int lineType = lines[lineIndexFromBottom].toInt();


            // Set color based on whether this is a changing line
            if (lineType == 2 || lineType == 3) {
                pen.setColor(changingLineRed);
            } else {
                pen.setColor(vibrantGold);
            }
            painter.setPen(pen);

            if (lineType == 1 || lineType == 3) {
                // Yang line (solid)
                painter.drawLine(startX, y, startX + lineLength, y);
            } else {
                // Yin line (broken) with greater gap
                int gap = 20;
                int halfLength = (lineLength - gap) / 2;
                painter.drawLine(startX, y, startX + halfLength, y);
                painter.drawLine(startX + halfLength + gap, y, startX + lineLength, y);
            }
        } else {
            // This position doesn't have a line yet - draw a faint placeholder

            pen.setColor(fadedGold);
            pen.setStyle(Qt::DotLine);
            painter.setPen(pen);

            // Draw a faint dotted line as placeholder
            painter.drawLine(startX, y, startX + lineLength, y);

            // Reset pen style for next iteration
            pen.setStyle(Qt::SolidLine);
        }
    }

    label->setPixmap(pixmap);
}

//////////////////
QIcon MainWindow::generateHexagramMandala(int hexagramNumber, int size)
{
    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);

    QPainter p(&pixmap);
    p.setRenderHint(QPainter::Antialiasing);

    int cx = size / 2;
    int cy = size / 2;

    // Seeded random generator for deterministic output
    QRandomGenerator rng(hexagramNumber);

    // Generate base hue from hexagram number
    int baseHue = (hexagramNumber * 59) % 360;

    QColor color1, color2, color3;
    color1.setHsv(baseHue, 200, 220);
    color2.setHsv((baseHue + 30) % 360, 200, 200);
    color3.setHsv((baseHue + 60) % 360, 180, 240);

    // Loop over the 6 hexagram lines (bottom=0 to top=5)
    for(int line = 0; line < 6; line++)
    {
        bool yang = hexagramNumber & (1 << line); // bit determines yang/yin
        int radius = 12 + line * 15;               // each line gets its own ring
        int petals = 6 + line * 2;                 // number of shapes per ring

        for(int i = 0; i < petals; i++)
        {
            double angle = (2 * M_PI * i) / petals;
            int x = cx + radius * cos(angle);
            int y = cy + radius * sin(angle);

            // Color selection
            int choice = rng.bounded(3);
            QColor c = (choice == 0) ? color1 : (choice == 1 ? color2 : color3);

            p.setBrush(c);
            p.setPen(Qt::NoPen);

            if(yang)
            {
                p.drawEllipse(QPoint(x, y), 4 + line/2, 4 + line/2);
            }
            else
            {
                QPolygon poly;
                poly << QPoint(x, y-4)
                     << QPoint(x+4, y)
                     << QPoint(x, y+4)
                     << QPoint(x-4, y);
                p.drawPolygon(poly);
            }
        }
    }

    // Center circle
    p.setBrush(QColor(240, 240, 240));
    p.drawEllipse(QPoint(cx, cy), 6, 6);

    return QIcon(pixmap);
}

QPixmap MainWindow::paintSevenCirclesWithHex(char32_t hexagramCode, int size = 128)
{
    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);
    //pixmap.fill(Qt::black);
    QPainter p(&pixmap);
    p.setRenderHint(QPainter::Antialiasing);

    int cx = size / 2;
    int cy = size / 2;

    // Colors for six outer rings (bottom → top)
    QColor colors[6] = {
        QColor(0, 0, 255),      // blue
        QColor(0, 255, 0),      // green
        QColor(255, 255, 255),  // white
        QColor(255, 0, 0),      // red
        QColor(255, 255, 0),    // yellow
        QColor(75, 0, 130)     // indigo
    };

    int maxRadius = size / 2;


    int centerRadius = maxRadius / 2;           // bigger black center
    int coloredRingThickness = (maxRadius - centerRadius) / 12; // thinner rings

    // Draw six concentric colored rings (outermost first)
    for(int i = 5; i >= 0; i--)
    {
        int outerRadius = centerRadius + coloredRingThickness * (i + 1);
        int innerRadius = centerRadius + coloredRingThickness * i;

        p.setPen(Qt::NoPen);
        p.setBrush(colors[i]);
        p.drawEllipse(QPoint(cx, cy), outerRadius, outerRadius);

        // Cut out inner circle
        p.setBrush(Qt::transparent);
        p.setCompositionMode(QPainter::CompositionMode_Clear);
        p.drawEllipse(QPoint(cx, cy), innerRadius, innerRadius);
        p.setCompositionMode(QPainter::CompositionMode_SourceOver);
    }

    // Draw center circle (black)
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawEllipse(QPoint(cx, cy), centerRadius, centerRadius);

    // Draw Hexagram 1 unicode inside center
    p.setPen(Qt::white);
    QFont font = p.font();
    font.setBold(true);
    font.setPointSize(centerRadius); // scale with center
    p.setFont(font);

    char32_t code[1] = { hexagramCode };
    QString hexagram = QString::fromUcs4(code, 1);

    QRect centerRect(cx - centerRadius, cy - centerRadius,
                     centerRadius*2, centerRadius*2);
    p.drawText(centerRect, Qt::AlignCenter, hexagram);

    return pixmap;
}


void MainWindow::createMenus()
{

    // Create menu bar
    QMenuBar *menuBar = this->menuBar();

    // File Menu
    QMenu *fileMenu = menuBar->addMenu("&File");
    downloadDatasetAction = new QAction("Download Meanings",this);
    connect(downloadDatasetAction, &QAction::triggered, this, &MainWindow::downloadDataset);
    fileMenu->addAction(downloadDatasetAction);
    fileMenu->addSeparator();

    // Save divination action
    QAction* saveDivinationAction = new QAction("Save Divination", this);
    saveDivinationAction->setShortcut(QKeySequence::Save);
    connect(saveDivinationAction, &QAction::triggered, this, &MainWindow::saveDivination);

    fileMenu->addAction(saveDivinationAction);

    // Load divination action
    QAction* loadDivinationAction = new QAction("Load Divination", this);
    loadDivinationAction->setShortcut(QKeySequence::Open);
    connect(loadDivinationAction, &QAction::triggered, this, &MainWindow::loadDivination);
    fileMenu->addAction(loadDivinationAction);

    fileMenu->addSeparator();
    QAction* openFolderAction = new QAction("Open Data Folder      Ctrl+F", this);

    connect(openFolderAction, &QAction::triggered, this, [this](){
        QDesktopServices::openUrl(QUrl().fromLocalFile(Constants::appDirPath));
    });
    fileMenu->addAction(openFolderAction);

    //
    QAction* opendecksAction = new QAction("Open Decks Folder      Ctrl+G", this);

    connect(opendecksAction, &QAction::triggered, this, [this](){
        QDesktopServices::openUrl(QUrl().fromLocalFile(Constants::decksDirPath));
    });
    fileMenu->addAction(opendecksAction);

    QShortcut *openDecksFolderShortcut = new QShortcut(QKeySequence("Ctrl+G"), this);
    connect(openDecksFolderShortcut, &QShortcut::activated, this, [this, opendecksAction]() {
          opendecksAction->trigger();
    });

    //

    QShortcut *openDataFolderShortcut = new QShortcut(QKeySequence("Ctrl+F"), this);
    connect(openDataFolderShortcut, &QShortcut::activated, this, [this, openFolderAction]() {
          openFolderAction->trigger();
    });

    // Settings Menu
    QMenu *settingsMenu = menuBar->addMenu("&Settings");

    //
    aiModelsAction = settingsMenu->addAction("Configure AI &Models...", this, &MainWindow::configureAIModels);



    QAction *checkModelAction = settingsMenu->addAction("Check AI Model &Status", this, [this]() {
        if (!activeModelLoaded) {
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("AI Model Not Configured");
            msgBox.setText("No active AI model found. You need to configure a model to get chart interpretations.");
            msgBox.setInformativeText("Would you like to configure one now?\n\n"
                                      "Note: If you've been using Mistral, you can add it as a provider with your API key.");

            QPushButton *configureButton = msgBox.addButton("Configure Models", QMessageBox::ActionRole);
            QPushButton *closeButton = msgBox.addButton(QMessageBox::Close);

            msgBox.exec();

            if (msgBox.clickedButton() == configureButton) {
                configureAIModels();
            }
        } else {
            // Load the active model settings

            settings.beginGroup("Models");
            QString activeModelName = settings.value("ActiveModel").toString();
            settings.beginGroup(activeModelName);

            QString provider = settings.value("provider").toString();
            QString endpoint = settings.value("endpoint").toString();
            QString modelName = settings.value("modelName").toString();
            QString apiKey = settings.value("apiKey").toString();
            double temperature = settings.value("temperature", 0.7).toDouble();
            int maxTokens = settings.value("maxTokens", 8192).toInt();

            settings.endGroup();
            settings.endGroup();

            // Build status message
            QString statusMessage = QString(
                "<b>Active Model:</b> %1<br><br>"
                "<b>Provider:</b> %2<br>"
                "<b>Model:</b> %3<br>"
                "<b>Endpoint:</b> %4<br>"
                "<b>Temperature:</b> %5<br>"
                "<b>Max Tokens:</b> %6<br>"
                "<b>API Key:</b> %7"
            ).arg(activeModelName)
             .arg(provider)
             .arg(modelName)
             .arg(endpoint)
             .arg(temperature)
             .arg(maxTokens)
             .arg(apiKey.isEmpty() ? "<font color='red'><b>MISSING</b></font>" : "<font color='green'><b>Configured</b></font>");

            // Check if API key is missing for cloud providers (not local)
            if (apiKey.isEmpty() && !endpoint.contains("localhost") && !endpoint.contains("127.0.0.1")) {
                statusMessage += "<br><br><font color='red'><b>WARNING:</b> This appears to be a cloud provider but no API key is set. Interpretations will fail.</font>";
            }

            QMessageBox::information(this, "AI Model Status", statusMessage);
        }
    });
    checkModelAction->setIcon(QIcon::fromTheme("dialog-information"));
    //
    settingsMenu->addSeparator();
    //

    shouldFreezeUI = settings.value("freezeUI", false).toBool(); // Default to false

    QAction *freezeUIAction = new QAction("Freeze UI during AI processing", this);
    freezeUIAction->setCheckable(true);
    freezeUIAction->setChecked(shouldFreezeUI);
    settingsMenu->addAction(freezeUIAction);

    connect(freezeUIAction, &QAction::toggled, this, [this](bool checked) {

        settings.setValue("freezeUI", checked);
        shouldFreezeUI = checked;
        QString status = checked ? "enabled" : "disabled";
        qDebug() << "UI freeze during AI processing" << status;


    });
    //
    settingsMenu->addSeparator();
    playSoundsAction = new QAction("Play Sounds", this);
    playSoundsAction->setCheckable(true);

    connect(playSoundsAction, &QAction::triggered, this, [this](bool checked){
        isPlaySounds = checked;
        QSettings settings;
        settings.setValue("sounds/isplaysounds", checked);
        settings.sync();

    });
    settingsMenu->addAction(playSoundsAction);

    // Tools Menu
    QMenu *toolsMenu = menuBar->addMenu("&Tools");
    QAction* factoryResetAction = new QAction("Factory Reset", this);
    connect(factoryResetAction, &QAction::triggered, this, [this](){

        // Ask for confirmation first
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Factory Reset",
                                       "This will reset all settings to defaults.\n"
                                       "Your saved divinations will NOT be affected.\n\n"
                                       "Are you sure?",
                                       QMessageBox::Yes | QMessageBox::No);

        if (reply != QMessageBox::Yes) {
            return;
        }


        QString settingFilePath = settings.fileName();
        QFile settingsFile(settingFilePath);

        if(settingsFile.exists()){
            if(settingsFile.remove()) {
                QMessageBox::information(this, "Factory Reset",
                    "Settings have been reset to defaults.\n"
                    "The application will now exit.\n\n"
                    "Please restart the app.");

                // Force settings to reload
                settings.clear();
                settings.sync();

                // Exit the application
                QApplication::quit();
            } else {
                QMessageBox::warning(this, "Error",
                    "Failed to reset settings.\n"
                    "Please check file permissions.");
            }
        } else {
            QMessageBox::information(this, "Factory Reset",
                "No settings file found.\n"
                "Settings are already at defaults.");
        }
    });
    toolsMenu->addAction(factoryResetAction);
    toolsMenu->addSeparator();
    //import decks
    QAction* importDeckAction = new QAction("How to Import Decks...", this);
    connect(importDeckAction, &QAction::triggered, this, &MainWindow::showDeckImportGuide);
    toolsMenu->addAction(importDeckAction);
    //
    toolsMenu->addSeparator();
    QAction* datasetGuideAction = new QAction("How to Download Hexagram Meanings...", this);
    connect(datasetGuideAction, &QAction::triggered, this, &MainWindow::showDatasetGuide);
    toolsMenu->addAction(datasetGuideAction);
    toolsMenu->addSeparator();
    //
    QAction* aiConfigGuideAction = new QAction("How to Configure AI Models...", this);
    connect(aiConfigGuideAction, &QAction::triggered, this, &MainWindow::showAIConfigGuide);
    toolsMenu->addAction(aiConfigGuideAction);
    //

    // View Menu
    QMenu *viewMenu = menuBar->addMenu("&View");

    // Load saved state

    bool showCardActionChecked = settings.value("istarotmode", false).toBool();

    showCardsAction = new QAction("Display Cards", this);
    showCardsAction->setCheckable(true);
    showCardsAction->setChecked(showCardActionChecked);
    //isTarotMode = showCardActionChecked; // Sync the member variable

    // Set initial sizes based on saved state
    if (isTarotMode) {
        sourceHexagramTarotLabel->setFixedSize(Constants::tarotLabelWidth, Constants::tarotLabelHeight);  // rectangular for tarot cards
        modifiedHexagramTarotLabel->setFixedSize(Constants::tarotLabelWidth, Constants::tarotLabelHeight);
    } else {
        sourceHexagramTarotLabel->setFixedSize(Constants::mandalaLabelWidth, Constants::mandalaLabelHeight);  // square for mandalas
        modifiedHexagramTarotLabel->setFixedSize(Constants::mandalaLabelWidth, Constants::mandalaLabelHeight);
    }

    connect(showCardsAction, &QAction::toggled, this, [this](bool checked){
        isTarotMode = checked;

        // Save state

        settings.setValue("istarotmode", checked);

        if(checked){
            // Tarot card mode - rectangular
            sourceHexagramTarotLabel->setFixedSize(Constants::tarotLabelWidth, Constants::tarotLabelHeight);
            modifiedHexagramTarotLabel->setFixedSize(Constants::tarotLabelWidth, Constants::tarotLabelHeight);
        } else {
            // Mandala mode - square
            sourceHexagramTarotLabel->setFixedSize(Constants::mandalaLabelWidth, Constants::mandalaLabelHeight);
            modifiedHexagramTarotLabel->setFixedSize(Constants::mandalaLabelWidth, Constants::mandalaLabelHeight);
        }

        // Refresh displays if hexagram is complete
        if (iching->getCurrentLines().size() == 6) {
            HexagramInfo sourceInfo = iching->getSourceHexagram();
            int sourceNum = sourceInfo.number.toInt();
            loadTarotCardImage(sourceHexagramTarotLabel, sourceNum);

            HexagramInfo modifiedInfo = iching->getModifiedHexagram();
            if (!modifiedInfo.number.isEmpty()) {
                int modifiedNum = modifiedInfo.number.toInt();
                loadTarotCardImage(modifiedHexagramTarotLabel, modifiedNum);
            }
        }

        this->repaint();
    });

    viewMenu->addAction(showCardsAction);
    viewMenu->addSeparator();
    // show hide labels
    hideLabelsAction = new QAction("Hide Hexagram Labels", this);
    hideLabelsAction->setCheckable(true);
    hideLabelsAction->setChecked(false);
    connect(hideLabelsAction, &QAction::toggled, this, [this](bool checked){
       sourceHexagramDisplayLabel->setVisible(!checked);
       modifiedHexagramDisplayLabel->setVisible(!checked);

    });

    viewMenu->addAction(hideLabelsAction);

    showCardsAction->setShortcut(QKeySequence("Ctrl+D"));
    hideLabelsAction->setShortcutVisibleInContextMenu(true);

    hideLabelsAction->setShortcut(QKeySequence("Ctrl+Alt+S"));
    hideLabelsAction->setShortcutVisibleInContextMenu(true);

    // I can also add it to the menu with visible shortcut
    //showCardsAction->setShortcut(QKeySequence("Ctrl+Shift+D"));
    //showCardsAction->setShortcutVisibleInContextMenu(true);

    viewMenu->addSeparator();
    // Help Menu
    QMenu *helpMenu = menuBar->addMenu("&Help");
    QAction *aboutAction = helpMenu->addAction("About IChingDiviner");
        connect(aboutAction, &QAction::triggered, [this]() {
            HelpMenuDialog dialog(HelpType::About, this);
            dialog.exec();
        });
        helpMenu->addAction(aboutAction);

        // Features
        QAction *featuresAction = helpMenu->addAction("Features");
        connect(featuresAction, &QAction::triggered, [this]() {
            HelpMenuDialog dialog(HelpType::Features, this);
            dialog.exec();
        });
        helpMenu->addAction(featuresAction);

        // Instructions
        QAction *instructionsAction = helpMenu->addAction("Instructions");
        connect(instructionsAction, &QAction::triggered, [this]() {
            HelpMenuDialog dialog(HelpType::Instructions, this);
            dialog.exec();
        });

        helpMenu->addAction(featuresAction);

        // whatsnew
        QAction *whatsNewAction = helpMenu->addAction("What's New");
        connect(whatsNewAction, &QAction::triggered, [this]() {
            HelpMenuDialog dialog(HelpType::WhatsNew, this);
            dialog.exec();
        });
        helpMenu->addAction(whatsNewAction);

        QAction *supportusAction = helpMenu->addAction("Support Us");
            connect(supportusAction, &QAction::triggered, [this]() {
                DonationDialog dialog(this);
                dialog.exec();
            });
            helpMenu->addAction(supportusAction);
}



void MainWindow::populateDecksComboBox()
{

    QDir cardsDir(Constants::decksDirPath);
    QStringList deckFolders;

    if (cardsDir.exists()) {
        deckFolders = cardsDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    }

    if (deckFolders.isEmpty()) {
        // Fallback defaults
        deckFolders = {"Add Deck"};
    }

    deckCombo->clear();
    deckCombo->addItems(deckFolders);


    deckCombo->setCurrentIndex(0);
    currentDeck = deckCombo->currentText();
}


void MainWindow::onSetQuestion() {
    // Create dialog and widgets only once
    if (!questionDialog) {
        questionDialog = new QDialog(this);
        questionDialog->setWindowTitle("Set Your Question");
        questionDialog->resize(500, 300);

        QVBoxLayout *mainLayout = new QVBoxLayout(questionDialog);

        // Question group
        QGroupBox *questionGroup = new QGroupBox("Your Question", questionDialog);
        QVBoxLayout *questionLayout = new QVBoxLayout(questionGroup);

        // Create question input
        questionInput = new QTextEdit(questionDialog);
        questionInput->setToolTip("Your question will be forwarded to the AI");
        questionInput->setPlaceholderText("Enter your question for the reading...");
        questionInput->setMaximumHeight(100);

        // Create buttons
        QPushButton *setQuestionButton = new QPushButton("Set Question", questionDialog);
        QPushButton* clearQuestionButton = new QPushButton("Clear", questionDialog);

        // Connect buttons
        connect(setQuestionButton, &QPushButton::clicked, this, [this, setQuestionButton]() {
            QString question = questionInput->toPlainText().trimmed();
            if(!question.isEmpty()){
            currentQuestion = question;
            QMessageBox::information(this, "Question Set",
                "Your question has been saved and will be used for AI interpretation.");

            openQuestionDialogButton->setToolTip(QString("Pose a question to be forwarded to AI\n\n"
                                                 "Current question:\n"
                                                 "%1").arg(question));
            }
            //questionDialog->hide();
        });

        connect(clearQuestionButton, &QPushButton::clicked, this, [this]() {
            questionInput->clear();
            currentQuestion.clear();
        });

        QPushButton* closeQuestionDialogButton = new QPushButton("Close", questionDialog);
        connect(closeQuestionDialogButton, &QPushButton::clicked, this, [this](){
            questionDialog->hide();
        });

        // Create horizontal layout for buttons
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(setQuestionButton);
        buttonLayout->addWidget(clearQuestionButton);

        questionLayout->addWidget(questionInput);
        questionLayout->addLayout(buttonLayout);

        mainLayout->addWidget(questionGroup);
        mainLayout->addWidget(closeQuestionDialogButton);

    }

    // Update with existing question if any
    if (!currentQuestion.isEmpty()) {
        questionInput->setText(currentQuestion);
    } else {
        questionInput->clear();
    }

    questionDialog->show();
}

void MainWindow::configureAIModels()
{
    ModelSelectorDialog dlg(this);

    // Connect to activeModelChanged signal
       connect(&dlg, &ModelSelectorDialog::activeModelChanged, this, [this](const QString &modelName) {
           // When active model changes, reload it in aiManager
           // This will update GlobalFlags::activeModelLoaded internally
           aiManager->loadActiveModel();

           // Optional: Show status message
           //statusBar()->showMessage(tr("Active model changed to: %1").arg(modelName), 3000);
       });

       dlg.exec();  // Just show the dialog, no need to process results

        aiManager->loadActiveModel();

       // The dialog saves changes to QSettings automatically
       // The aiManager class will read the active model from QSettings when needed
}

void MainWindow::gatAiInterpretation()
{
    if (iching->getCurrentLines().size() < 6) {
            aiTextEdit->setText("Complete the hexagram first before requesting an AI interpretation.");
            return;
        }

    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "AI Interpretation",
                                       "Proceed with interpretation?",
                                       QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::No) {
            return;
        }


// Freeze UI with wait cursor
    if(shouldFreezeUI){
    QApplication::setOverrideCursor(Qt::WaitCursor);
    this->setEnabled(false); // Disable entire window
    QCoreApplication::processEvents(); // Force UI updat
    }
    // Clear previous AI text
    aiTextEdit->clear();

    // Check if AI model is configured
    if (!aiManager->loadActiveModel()) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("AI Model Not Configured");
        msgBox.setText("No active AI model found.");
        msgBox.setInformativeText("Please configure an AI model in Settings → Configure AI Models before generating interpretations.\n\n"
                                  "You can use Mistral (get your free key at mistral.ai), OpenAI, Groq, or local models like Ollama.");

        QPushButton *openSettingsButton = msgBox.addButton("Open Settings", QMessageBox::ActionRole);
        QPushButton *closeButton = msgBox.addButton(QMessageBox::Close);

        msgBox.exec();

        if (msgBox.clickedButton() == openSettingsButton) {
            // ModelSelectorDialog dlg(this);
            // dlg.exec();

            // Reload model after dialog closes
            aiManager->loadActiveModel();

            // If still not loaded, show error
            if (!aiManager->loadActiveModel()) {
                aiTextEdit->setText("No AI model configured. Please configure one and try again.");
            }
        } else {
            aiTextEdit->setText("AI model configuration is required to generate interpretations.");
        }
        return;
    }

    // Get hexagram info
    HexagramInfo sourceInfo = iching->getSourceHexagram();
    HexagramInfo modifiedInfo = iching->getModifiedHexagram();

    // Build the prompt
    QString prompt = "I-Ching Divination:\n";
    prompt += QString("Source Hexagram: %1 - %2\n")
        .arg(sourceInfo.number).arg(sourceInfo.name);

    if (!modifiedInfo.number.isEmpty() && modifiedInfo.number != sourceInfo.number) {
        prompt += QString("Resulting Hexagram: %1 - %2\n")
            .arg(modifiedInfo.number).arg(modifiedInfo.name);
    }

    // Add changing lines if any
    QList<int> changingLines = iching->getChangingLinePositions();
    if (!changingLines.isEmpty()) {
        QStringList lineStrings;
        for (int line : changingLines) {
            lineStrings << QString::number(line);
        }
        prompt += "Changing Lines: " + lineStrings.join(", ") + "\n";
    }

    if (!currentQuestion.isEmpty()) {
        prompt += "Question: " + currentQuestion + "\n";
    }

    prompt += "\nPlease provide an I-Ching interpretation based on this divination.";

    // Set the query (question) for the API
    aiManager->setQuery(currentQuestion);

    // Show loading message
    aiTextEdit->setText("Generating AI interpretation...");

    // Generate the reading
    aiManager->generateReading(prompt);

    // Connect the response handler if not already connected
    // You might want to do this once in the constructor instead
    static bool connected = false;
    if (!connected) {
        connect(aiManager, &MistralAPI::readingReady, this, [this](const QString& reading) {
            QString htmlReading = markdownToHtml(reading);
            aiTextEdit->setText(htmlReading);

            // Unfreeze UI
            if(shouldFreezeUI){
            this->setEnabled(true);
            QApplication::restoreOverrideCursor();
            }
        });
        connect(aiManager, &MistralAPI::errorOccurred, this, [this](const QString& error) {
            aiTextEdit->setText("Error: " + error);
            // Unfreeze UI
            if(shouldFreezeUI){
            this->setEnabled(true);
            QApplication::restoreOverrideCursor();
            }

        });
        connected = true;
    }
}


QString MainWindow::markdownToHtml(const QString &markdown)
{
    QString html = markdown;

    // Convert headers
    html.replace(QRegularExpression("^###### (.*)$", QRegularExpression::MultilineOption), "<h6>\\1</h6>");
    html.replace(QRegularExpression("^##### (.*)$", QRegularExpression::MultilineOption), "<h5>\\1</h5>");
    html.replace(QRegularExpression("^#### (.*)$", QRegularExpression::MultilineOption), "<h4>\\1</h4>");
    html.replace(QRegularExpression("^### (.*)$", QRegularExpression::MultilineOption), "<h3>\\1</h3>");
    html.replace(QRegularExpression("^## (.*)$", QRegularExpression::MultilineOption), "<h2>\\1</h2>");
    html.replace(QRegularExpression("^# (.*)$", QRegularExpression::MultilineOption), "<h1>\\1</h1>");

    // Convert bold (**text**)
    html.replace(QRegularExpression("\\*\\*(.*?)\\*\\*"), "<b>\\1</b>");

    // Convert italic (*text*)
    html.replace(QRegularExpression("\\*(.*?)\\*"), "<i>\\1</i>");

    // Convert bullet points
    //html.replace(QRegularExpression("^\\- (.*)$", QRegularExpression::MultilineOption), "• \\1<br>");
    //html.replace(QRegularExpression("^\\- (.*)$", QRegularExpression::MultilineOption), "• \\1<br>");

    // Handle • bullets (with optional whitespace)
    html.replace(QRegularExpression("^[\\s]*\\•[\\s]+(.*)$", QRegularExpression::MultilineOption), "• \\1<br>");

    // Handle - bullets (with optional whitespace)
    html.replace(QRegularExpression("^[\\s]*\\-[\\s]+(.*)$", QRegularExpression::MultilineOption), "• \\1<br>");

    // Handle * bullets (with optional whitespace)
    html.replace(QRegularExpression("^[\\s]*\\*[\\s]+(.*)$", QRegularExpression::MultilineOption), "• \\1<br>");

    // Convert horizontal rules (---, ***, ___) with optional spaces
    html.replace(QRegularExpression("^\\s*(---|\\*\\*\\*|___)\\s*$", QRegularExpression::MultilineOption), "<hr>");

    html.replace("\n", "<br>");

    //return "<html><body>" + html + "</body></html>";
    return html;
}

void MainWindow::toggleShuffle(bool checked) {

    if (checked) {
        // Start shuffling
        iching->entropyData.clear();
        mouseTimer->start();
        shuffleButton->setText("Stop Enchanting");
        isShuffling = true;

        // Change cursor to crosshair (+)
        QApplication::setOverrideCursor(Qt::CrossCursor);

    } else {
        // Stop shuffling
        mouseTimer->stop();
        iching->generateSeed();
        shuffleButton->setText("Start Enchanting");
        isShuffling = false;

        // Restore default cursor
        QApplication::restoreOverrideCursor();
    }
}

bool MainWindow::downloadDataset()
{
    QString tempPath = Constants::appDirPath + "/iching_temp.js";
    QString finalPath = Constants::appDirPath + "/iching.json";

    // Check if file already exists
    if (QFile::exists(finalPath)) {
        QMessageBox::information(this, "File Exists",
            "Dataset already exists at:\n" + finalPath +
            "\n\nTo download a fresh copy, please delete the existing file first.");
        return false;
    }

    QMessageBox msgBox(this);
        msgBox.setWindowTitle("Download I-Ching Dataset");
        msgBox.setText("This will download the Wilhelm translation dataset from:");
        msgBox.setInformativeText(
            "https://github.com/adamblvck/iching-wilhelm-dataset\n\n"
            "The dataset is provided under MIT License by Adam Blvck.\n"
            "The underlying Wilhelm/Baynes translation text is used in accordance with applicable copyright laws.\n\n"
            "See also 'CREDITS.txt' file for full attribution.\n\n"
            "Proceed with download?"
        );

        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);

        if (msgBox.exec() == QMessageBox::No) {
            return false;
        }


    // Ensure directory exists
    QDir dir(Constants::appDirPath);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            QMessageBox::warning(this, "Error", "Failed to create directory");
            return false;
        }
    }

    // Step 1: Download with wget
    int wgetExit = QProcess::execute("wget", QStringList()
        << "-q" << "-O" << tempPath
        << "https://raw.githubusercontent.com/adamblvck/iching-wilhelm-dataset/master/data/iching_wilhelm_translation.js");

    if (wgetExit != 0) {
        QMessageBox::warning(this, "Download Failed",
            "Failed to download dataset. Please check your internet connection.");
        return false;
    }

    // Step 2: Remove "export default" with sed
    int sedExit = QProcess::execute("sed", QStringList()
        << "-i" << "s/^\\s*export\\s*default\\s*//" << tempPath);

    if (sedExit != 0) {
        QMessageBox::warning(this, "Processing Failed",
            "Failed to process the downloaded file.");
        return false;
    }

    // Step 3: Rename to final
    if (!QFile::rename(tempPath, finalPath)) {
        QMessageBox::warning(this, "File Error",
            "Failed to save the final file.");
        return false;
    }

    // Success!
    QMessageBox::information(this, "Success",
        "Dataset downloaded and installed successfully.");

    // Reload meanings
    loadHexagramMeanings();

    return true;
}

//save-load
/*
void MainWindow::saveDivination()
{
    if (iching->getCurrentLines().size() < 6) {
        QMessageBox::warning(this, "Cannot Save", "Complete the hexagram first.");
        return;
    }

    // Ensure save directory exists
    QDir dir(Constants::saveDirPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString filePath = QFileDialog::getSaveFileName(this,
        "Save Divination",
        Constants::saveDirPath + "/divination_" +
            QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".json",
        "JSON Files (*.json)");

    if (filePath.isEmpty()) return;

    QJsonObject root;

    // Basic info
    root["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    root["question"] = currentQuestion;
    root["aiInterpretation"] = aiTextEdit->toPlainText();
    root["deckName"] = currentDeck;

    // Lines data
    QStringList lines = iching->getCurrentLines();
    QJsonArray linesArray;
    for (const QString &line : lines) {
        linesArray.append(line.toInt());
    }
    root["lines"] = linesArray;

    // Hexagram numbers
    HexagramInfo source = iching->getSourceHexagram();
    root["sourceHexagram"] = source.number.toInt();

    HexagramInfo modified = iching->getModifiedHexagram();
    if (!modified.number.isEmpty()) {
        root["modifiedHexagram"] = modified.number.toInt();
    }

    // Write to file
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
        file.close();
        QMessageBox::information(this, "Success", "Divination saved successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save divination.");
    }

    // ========== ADD JOURNAL ENTRY ==========
    // Get source and modified hexagram numbers
    int sourceNum = 0;
    int modifiedNum = 0;

    HexagramInfo sourceInfo = iching->getSourceHexagram();
    HexagramInfo modifiedInfo = iching->getModifiedHexagram();

    if (!sourceInfo.number.isEmpty()) {
        QRegularExpression re("^(\\d+)");
        QRegularExpressionMatch match = re.match(sourceInfo.number);
        if (match.hasMatch()) {
            sourceNum = match.captured(1).toInt();
        }
    }

    if (!modifiedInfo.number.isEmpty()) {
        QRegularExpression re("^(\\d+)");
        QRegularExpressionMatch match = re.match(modifiedInfo.number);
        if (match.hasMatch()) {
            modifiedNum = match.captured(1).toInt();
        }
    }

    // Add entry to journal (empty notes, just the reading)
    JournalManager::instance().addEntry(sourceNum, modifiedNum, currentDeck, filePath, "");
}
*/

void MainWindow::saveDivination()
{
    if (iching->getCurrentLines().size() < 6) {
        QMessageBox::warning(this, "Cannot Save", "Complete the hexagram first.");
        return;
    }

    // Ensure save directory exists
    QDir dir(Constants::saveDirPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString filePath = QFileDialog::getSaveFileName(this,
        "Save Divination",
        Constants::saveDirPath + "/divination_" +
            QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".json",
        "JSON Files (*.json)");

    if (filePath.isEmpty()) return;

    QJsonObject root;

    // Basic info
    root["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    root["question"] = currentQuestion;
    root["aiInterpretation"] = aiTextEdit->toPlainText();
    root["deckName"] = currentDeck;

    // Lines data
    QStringList lines = iching->getCurrentLines();
    QJsonArray linesArray;
    for (const QString &line : lines) {
        linesArray.append(line.toInt());
    }
    root["lines"] = linesArray;

    // Hexagram numbers
    HexagramInfo source = iching->getSourceHexagram();
    int sourceNum = source.number.toInt();
    root["sourceHexagram"] = sourceNum;

    HexagramInfo modified = iching->getModifiedHexagram();
    int modifiedNum = 0;
    if (!modified.number.isEmpty()) {
        modifiedNum = modified.number.toInt();
        root["modifiedHexagram"] = modifiedNum;
    }

    // Write to file
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
        file.close();
        QMessageBox::information(this, "Success", "Divination saved successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save divination.");
        return;  // Don't add journal entry if save failed
    }

    // ========== ADD JOURNAL ENTRY ==========
    JournalManager::instance().addEntry(sourceNum, modifiedNum, currentDeck, filePath, "");
}

void MainWindow::loadDivination()
{
    QString filePath = QFileDialog::getOpenFileName(this,
        "Load Divination",
        Constants::saveDirPath,
        "JSON Files (*.json)");

    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Failed to open file.");
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isObject()) {
        QMessageBox::warning(this, "Error", "Invalid JSON file.");
        return;
    }

    QJsonObject root = doc.object();

    // Restore question
    currentQuestion = root["question"].toString();
    openQuestionDialogButton->setToolTip(QString("Pose a question to be forwarded to AI\n\n"
                                         "Current question:\n"
                                         "%1").arg(currentQuestion));


    // Restore AI interpretation
    aiTextEdit->setText(root["aiInterpretation"].toString());

    // Restore deck
    currentDeck = root["deckName"].toString();
    int deckIndex = deckCombo->findText(currentDeck);
    if (deckIndex >= 0) {
        deckCombo->setCurrentIndex(deckIndex);
    }

    // Restore lines
    QJsonArray linesArray = root["lines"].toArray();
    QStringList lines;
    for (const QJsonValue &val : linesArray) {
        lines.append(QString::number(val.toInt()));
    }

    // Reset and set lines in IChing
    iching->reset();
    for (const QString &line : lines) {
        iching->currentLines.append(line);
    }

    // Update display
    updateHexagramDisplay();

    QMessageBox::information(this, "Success", "Divination loaded successfully.");
}


void MainWindow::loadDivinationFromFile(const QString& filePath)
{
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Failed to open file: " + filePath);
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isObject()) {
        QMessageBox::warning(this, "Error", "Invalid JSON file.");
        return;
    }

    QJsonObject root = doc.object();

    // Restore question
    currentQuestion = root["question"].toString();
    openQuestionDialogButton->setToolTip(QString("Pose a question to be forwarded to AI\n\n"
                                         "Current question:\n"
                                         "%1").arg(currentQuestion));
    // Restore AI interpretation
    aiTextEdit->setText(root["aiInterpretation"].toString());

    // Restore deck
    currentDeck = root["deckName"].toString();
    int deckIndex = deckCombo->findText(currentDeck);
    if (deckIndex >= 0) {
        deckCombo->setCurrentIndex(deckIndex);
    }

    // Restore lines
    QJsonArray linesArray = root["lines"].toArray();
    QStringList lines;
    for (const QJsonValue &val : linesArray) {
        lines.append(QString::number(val.toInt()));
    }

    // Reset and set lines in IChing
    iching->reset();
    for (const QString &line : lines) {
        iching->currentLines.append(line);
    }

    // Update display
    updateHexagramDisplay();

    QMessageBox::information(this, "Success", "Divination loaded successfully.");
}

void MainWindow::showDeckImportGuide()
{
    QString guide =
        "<h2>Importing Your Own Decks</h2>"
        "<p>You can use digital copies of your physical I-Ching decks in this app.</p>"

        "<h3>How to Create a Digital Deck:</h3>"
        "<ol>"
        "<li><b>Scan or photograph</b> each card from your physical deck"
        "<ul>"
        "<li>Use a scanner (300 DPI recommended) or well-lit photos</li>"
        "<li>Crop each image to show just the card</li>"
        "<li>Save as PNG for best quality, JPG for smaller files</li>"
        "</ul>"
        "</li>"

        "<li><b>Name the files</b> following this pattern:"
        "<br><code>00.png</code> (Hexagram 1 - The Creative)"
        "<br><code>01.png</code> (Hexagram 2 - The Receptive)"
        "<br><code>02.png</code> (Hexagram 3 - Difficulty at the Beginning)"
        "<br>... up to <code>63.png</code> (Hexagram 64 - Before Completion)"
        "</li>"

        "<li><b>Create a deck folder</b> in the app's decks directory:"
        "<br><code>" + Constants::decksDirPath + "/YourDeckName/</code>"
        "<br>For example: <code>/decks/deck-name/</code> or <code>/decks/other-deck-name/</code>"
        "</li>"

        "<li><b>Place all your images</b> in this folder</li>"

        "<li><b>Select your deck</b> from the dropdown menu in the app's Controls panel</li>"
        "</ol>"

        "<h3>Quick Start:</h3>"
        "<ul>"
        "<li>Use <b>Files → Open Decks Folder</b> to access the decks directory</li>"
        "<li>Create a new folder inside with your deck name</li>"
        "<li>Copy your numbered images there</li>"
        "</ul>"

        "<h3 style='color: #ff6b6b;'>Important Legal Notice</h3>"
        "<p>This feature is for your <b>personal use only</b>. You may only create digital copies of decks you physically own. "
        "Format-shifting for personal use is permitted under copyright law in many jurisdictions, but:</p>"
        "<ul>"
        "<li>Do NOT share or distribute your digital copies</li>"
        "<li>Do NOT upload them to the internet</li>"
        "<li>Keep them for your own private use only</li>"
        "</ul>"

        "<h3>Need More Help?</h3>"
        "<p>Visit the app documentation or GitHub repository for detailed guides on scanning and preparing your images.</p>";

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Import Decks Guide");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(guide);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}


void MainWindow::showDatasetGuide()
{
    QString guide =
        "<h2>Downloading Hexagram Meanings Dataset</h2>"

        "<p>The Wilhelm translation of the I-Ching provides the rich interpretations "
        "you see in the Hexagram Meaning panel. This dataset may be downloaded"
        " by the user.</p>"

        "<h3>To Download the Dataset:</h3>"
        "<ol>"
        "<li><b>Go to <span style='color: #4CAF50;'>File → Download Meanings</span></b></li>"
        "<li>Review the source and license information</li>"
        "<li>Click 'Yes' to proceed with download</li>"
        "<li>The app will automatically download and install the dataset</li>"
        "</ol>"

        "<h3>What Gets Downloaded:</h3>"
        "<ul>"
        "<li><b>Source:</b> github.com/adamblvck/iching-wilhelm-dataset</li>"
        "<li><b>License:</b> MIT (dataset compilation)</li>"
        "<li><b>Content:</b> Complete Wilhelm/Baynes translation of all 64 hexagrams</li>"
        "</ul>"

        "<h3>After Download:</h3>"
        "<p>The meanings will automatically appear in the right dock. "
        "You only need to download once - the file is saved locally.</p>"

        "<h3>Manual Download (if needed):</h3>"
        "<p>You can also download the JSON file manually from:<br>"
        "<a href='https://raw.githubusercontent.com/adamblvck/iching-wilhelm-dataset/master/data/iching_wilhelm_translation.js'>"
        "https://github.com/adamblvck/iching-wilhelm-dataset</a></p>"
        "<p>Save it as <code>iching.json</code> in:<br>"
        "<code>" + Constants::appDirPath + "</code></p>";

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Download Hexagram Meanings");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(guide);

    // Add button to trigger download directly
    QPushButton *downloadNowButton = msgBox.addButton("Download Now", QMessageBox::ActionRole);
    msgBox.addButton(QMessageBox::Close);

    msgBox.exec();

    if (msgBox.clickedButton() == downloadNowButton) {
        // Find and trigger the download action
        QAction *downloadAction = findChild<QAction*>("downloadDatasetAction");
        if (downloadAction) {
            downloadAction->trigger();
        } else {
            // Fallback: call download directly
            downloadDataset();
        }
    }
}

void MainWindow::showAIConfigGuide()
{
    QDialog dialog(this);
    dialog.setWindowTitle("AI Interpretation Guide");
    dialog.resize(600, 500);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QTextEdit *textEdit = new QTextEdit(&dialog);
    textEdit->setReadOnly(true);
    textEdit->setHtml(
        "<h2>AI-Powered I-Ching Interpretations</h2>"

        "<p>The app can use AI models to provide rich, contextual interpretations of your divinations. "
        "You can connect to various AI providers by configuring them in the Model Selector.</p>"

        "<h3>Getting Started:</h3>"
        "<ol>"
        "<li><b>Open AI Model Selector:</b> Tools → AI Model Selector</li>"
        "<li><b>Add a new model:</b> Click 'Add' and fill in the details</li>"
        "<li><b>Set as active:</b> Select the model and click 'Set Active'</li>"
        "<li><b>Get interpretations:</b> Complete a hexagram and click 'Get AI Interpretation'</li>"
        "</ol>"

        "<h3>Compatible Providers (OpenAI-compatible API format):</h3>"
        "<table width='100%' border='1' cellpadding='5'>"
        "<tr><th>Provider</th><th>Endpoint</th><th>Example Model</th><th>API Key</th></tr>"

        "<tr><td><b>Groq</b></td>"
        "<td><code>https://api.groq.com/openai/v1/chat/completions</code></td>"
        "<td><code>llama-3.3-70b-versatile</code></td>"
        "<td>gsk_... (free tier)</td></tr>"

        "<tr><td><b>Mistral</b></td>"
        "<td><code>https://api.mistral.ai/v1/chat/completions</code></td>"
        "<td><code>mistral-medium</code></td>"
        "<td>Free trial</td></tr>"

        "<tr><td><b>OpenAI</b></td>"
        "<td><code>https://api.openai.com/v1/chat/completions</code></td>"
        "<td><code>gpt-4</code> or <code>gpt-3.5-turbo</code></td>"
        "<td>Paid access</td></tr>"

        "<tr><td><b>Ollama (local)</b></td>"
        "<td><code>http://localhost:11434/v1/chat/completions</code></td>"
        "<td><code>llama3</code> or <code>mistral</code></td>"
        "<td><i>None</i></td></tr>"

        "<tr><td><b>Together AI</b></td>"
        "<td><code>https://api.together.xyz/v1/chat/completions</code></td>"
        "<td><code>mistralai/Mixtral-8x7B-Instruct</code></td>"
        "<td>Required</td></tr>"

        "<tr><td><b>DeepSeek</b></td>"
        "<td><code>https://api.deepseek.com/v1/chat/completions</code></td>"
        "<td><code>deepseek-chat</code></td>"
        "<td>Required</td></tr>"
        "</table>"

        "<h3>Configuration Tips:</h3>"
        "<ul>"
        "<li><b>Friendly Name:</b> Any name to identify this config (e.g., 'My Groq Llama')</li>"
        "<li><b>Provider:</b> Just for reference (e.g., 'Groq', 'OpenAI')</li>"
        "<li><b>Endpoint URL:</b> The full API URL from the table above</li>"
        "<li><b>API Key:</b> Get from provider's website (except Ollama)</li>"
        "<li><b>Model Name:</b> The specific model identifier from the provider</li>"
        "<li><b>Temperature:</b> Keep at 0.7 for balanced interpretations</li>"
        "<li><b>Max Tokens:</b> 4096 is usually sufficient</li>"
        "</ul>"

        "<h3>Finding Model Names and Endpoints:</h3>"
        "<p>If you're unsure about which model to use or need the exact endpoint URL:</p>"
        "<ul>"
        "<li><b>Ask AI assistants</b> like ChatGPT, Claude: "
        "\"What's the API endpoint and available models for [Provider]?\"</li>"
        "<li><b>Check provider documentation</b> - most have clear API reference pages</li>"
        "<li><b>Search online:</b> '[Provider] API documentation'</li>"
        "</ul>"

        "<h3>Recommended Settings by Provider:</h3>"
        "<ul>"
        "<li><b>Groq:</b> <code>llama-3.3-70b-versatile</code> for best quality</li>"
        "<li><b>Mistral:</b> <code>mistral-medium</code> works well</li>"
        "<li><b>OpenAI:</b> <code>gpt-4</code> best results, <code>gpt-3.5-turbo</code> faster/cheaper</li>"
        "<li><b>Ollama:</b> Install Ollama first, then pull <code>llama3</code> or <code>mistral</code></li>"
        "</ul>"

        "<h3 style='color: #ff6b6b;'>Important Notes:</h3>"
        "<ul>"
        "<li><b>API keys are stored locally</b> in your system's secure settings</li>"
        "<li><b>Not compatible:</b> Claude (Anthropic), Gemini (Google) - different API formats</li>"
        "<li><b>Restart app</b> after configuring your first model</li>"
        "<li><b>Hexagram data and question</b> are sent to the configured AI service</li>"
        "</ul>"
    );

    layout->addWidget(textEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *openConfigButton = new QPushButton("Open Model Selector", &dialog);
    QPushButton *closeButton = new QPushButton("Close", &dialog);

    buttonLayout->addStretch();
    buttonLayout->addWidget(openConfigButton);
    buttonLayout->addWidget(closeButton);

    layout->addLayout(buttonLayout);

    connect(openConfigButton, &QPushButton::clicked, &dialog, [this, &dialog]() {
        dialog.accept();
        ModelSelectorDialog dlg(this);
        dlg.exec();
        aiManager->loadActiveModel();
    });

    connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

bool MainWindow::loadChineseFont()
{
    QStringList fontPaths;

    // 1. Next to binary (local builds)
    fontPaths << QCoreApplication::applicationDirPath() + "/NotoSerifTC-Black.ttf";

    // 2. Flatpak install
    fontPaths << "/app/share/" + QCoreApplication::applicationName() + "/fonts/NotoSerifTC-Black.ttf";

    for (const QString& path : fontPaths) {
        if (QFile::exists(path)) {
            int fontId = QFontDatabase::addApplicationFont(path);
            if (fontId != -1) {
                qDebug() << "Loaded Chinese font from:" << path;
                return true;
            }
        }
    }

    qDebug() << "Chinese font not found";
    return false;
}

void MainWindow::resetCoins()
{
    QLabel* coinLabels[] = { coinLabel1, coinLabel2, coinLabel3 };
    for (int i = 0; i < 3; i++) {
        QSvgRenderer renderer(QString(":/files/chinese_coin_tails.svg"));
        QPixmap pixmap(170, 170);
        pixmap.fill(Qt::transparent);

        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        //painter.setOpacity(0.3);
        renderer.render(&painter);
        painter.end();

        coinLabels[i]->setPixmap(pixmap);
        coinLabels[i]->setAlignment(Qt::AlignCenter);
    }
}


bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (importModeActive && event->type() == QEvent::MouseButtonPress) {
        if (obj == coinLabel1 || obj == coinLabel2 || obj == coinLabel3) {
            // Flip this coin
            QLabel* coin = qobject_cast<QLabel*>(obj);
            if (coin) {
                // Get current coin state (we'll track manually or read from pixmap)
                // For simplicity, add a property to track state
                bool isHeads = coin->property("isHeads").toBool();
                isHeads = !isHeads;
                coin->setProperty("isHeads", isHeads);

                // Update the displayed coin
                QString svgPath = isHeads ? ":/files/chinese_coin_heads.svg" : ":/files/chinese_coin_tails.svg";
                QSvgRenderer renderer(svgPath);
                QPixmap pixmap(170, 170);
                pixmap.fill(Qt::transparent);
                QPainter painter(&pixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                renderer.render(&painter);
                painter.end();
                coin->setPixmap(pixmap);
            }
            return true; // Event consumed
        }
    }
    return QMainWindow::eventFilter(obj, event);
}


void MainWindow::onImportModeToggled(bool checked)
{
    importModeActive = checked;

    if (checked) {
        autoTossButton->setEnabled(false);
        autoTossButton->setToolTip("Auto toss is disabled in physical mode");
        // Enable import mode
        tossButton->setText("Set Result");
        tossButton->setToolTip("Record current coin state as a hexagram line");

        // Reset coins to default state
        resetCoins();

        // Initialize coin states
        for (QLabel* coin : {coinLabel1, coinLabel2, coinLabel3}) {
            coin->setProperty("isHeads", false); // Start all tails
        }

        meaningTextEdit->setText("Import Mode ON\n\n"
                                 "Click on each coin to flip it to match your physical toss.\n"
                                 "Then click 'Set Result' to record the line.\n\n"
                                 "Repeat 6 times to build your hexagram.");
    } else {
        // Disable import mode
        autoTossButton->setEnabled(true);
        autoTossButton->setToolTip(QString());
        tossButton->setText("Toss");
        tossButton->setToolTip("Perform a random coin toss");
    }
}

void MainWindow::importPhysicalToss()
{
    if (!importModeActive) return;

    if (iching->getCurrentLines().size() >= 6) {
        meaningTextEdit->setText("Hexagram is complete. Press Reset to start a new divination.");
        return;
    }

    // Read current coin states (heads = 1, tails = 0)
    QList<int> coinResults;
    for (QLabel* coin : {coinLabel1, coinLabel2, coinLabel3}) {
        bool isHeads = coin->property("isHeads").toBool();
        coinResults.append(isHeads ? 1 : 0);
    }

    // Calculate sum (0,1,2,3)
    int sum = coinResults[0] + coinResults[1] + coinResults[2];
    QString lineType;
    switch (sum) {
    case 0: lineType = "2"; break; // changing yin
    case 1: lineType = "0"; break; // stable yin
    case 2: lineType = "1"; break; // stable yang
    case 3: lineType = "3"; break; // changing yang
    }

    // Add to current lines
    QStringList currentLines = iching->getCurrentLines();
    currentLines.append(lineType);
    iching->reset();
    for (const QString& line : currentLines) {
        iching->currentLines.append(line);
    }

    // Play sound
    if (isPlaySounds) coinSound->play();

    // Update display
    updateHexagramDisplay();

    // Show meaning when complete
    if (currentLines.size() == 6) {
        int sourceNum = 0;
        int modifiedNum = 0;

        HexagramInfo sourceInfo = iching->getSourceHexagram();
        HexagramInfo modifiedInfo = iching->getModifiedHexagram();

        if (!sourceInfo.number.isEmpty()) {
            QRegularExpression re("^(\\d+)");
            QRegularExpressionMatch match = re.match(sourceInfo.number);
            if (match.hasMatch()) sourceNum = match.captured(1).toInt();
        }

        if (!modifiedInfo.number.isEmpty()) {
            QRegularExpression re("^(\\d+)");
            QRegularExpressionMatch match = re.match(modifiedInfo.number);
            if (match.hasMatch()) modifiedNum = match.captured(1).toInt();
        }

        displayHexagramMeanings(sourceNum, modifiedNum);
        meaningTextEdit->append("\n\n--- Import Mode Complete ---");
    } else {
        QString progressMessage = "Line " + QString::number(currentLines.size()) +
                                  " of 6 added. Flip coins and click 'Set Result' again.";
        meaningTextEdit->setText(progressMessage);
    }

    // Reset coin display for next toss
    resetCoins();
    for (QLabel* coin : {coinLabel1, coinLabel2, coinLabel3}) {
        coin->setProperty("isHeads", false);
    }
}

// social and journal

void MainWindow::setupShareButton()
{
    // Create the share button
    QPushButton *shareButton = new QPushButton(this);
    shareButton->setIcon(QIcon(":/files/share-2.svg"));
    shareButton->setToolTip("Share this spread");
    shareButton->setFlat(true);
    shareButton->setFixedSize(32, 32);

    /*
    shareButton->setStyleSheet(R"(
        QPushButton {
            border: none;
            border-radius: 4px;
        }
        QPushButton:hover {
            background-color: rgba(255, 255, 255, 0.2);
        }
        QPushButton:pressed {
            background-color: rgba(255, 255, 255, 0.3);
        }
    )");
    */

    // Add to menubar corner
    QMenuBar *menuBar = this->menuBar();
    if (menuBar) {
        menuBar->setCornerWidget(shareButton, Qt::TopRightCorner);
    }

    connect(shareButton, &QPushButton::clicked, this, &MainWindow::onShareClicked);
}

void MainWindow::onShareClicked()
{
    // Check if we have a completed hexagram to share
    if (iching->getCurrentLines().size() < 6) {
        QMessageBox::information(this, "Cannot Share",
            "Complete a hexagram first before sharing.");
        return;
    }

    // Capture the central widget (coins + hexagrams)
    QPixmap screenshot(centralWidget->size());
    centralWidget->render(&screenshot);

    // Add watermark
    QPainter painter(&screenshot);
    painter.setPen(QPen(QColor(255, 255, 255, 180), 2));
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(screenshot.rect(), Qt::AlignBottom | Qt::AlignRight,
                     "  IChingDiviner  ");
    painter.end();

    // Build share text
    QString shareText = "My I Ching reading from IChingDiviner\n\nThe ancient wisdom of the I Ching guides us through life's changes.";

    // Copy to clipboard
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setImage(screenshot.toImage());

    // Create and show dialog
    SocialShareDialog *dialog = new SocialShareDialog(shareText, screenshot, m_socialShare, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setModal(false);
    dialog->show();
}
